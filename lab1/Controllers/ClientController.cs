using lab1.DataBase;
using lab1.Entities;
using lab1.Entities.Roles;
using lab1.Models.Client;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace lab1.Controllers;

public class ClientController : Controller
{
    private ApplicationContext _context;
    public ClientController(ApplicationContext context)
    {
        _context = context;
    }

    [HttpGet]
    [Authorize]
    public IActionResult ClientRegistration()
    {
        return View();
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> ClientRegistration(ClientRegistrationModel model)
    {
        if (ModelState.IsValid)
        {
            var user = _context.Users.FirstOrDefaultAsync(u => u.Email.Equals(User.Identity.Name)).Result;
            var client = new Client
            {
                Id = user.Id,
                Email = user.Email,
                Password = user.Password,

                Surname = user.Surname,
                FirstName = user.FirstName,
                Patronymic = user.Patronymic,

                PhoneNumber = user.PhoneNumber,
                Role = user.Role,
                RoleId = user.RoleId,

                PassportSeriesAndNumber = model.PassportSeriesAndNumber,
                IdentificationNumber = model.IdentificationNumber,
                
                BankAccounts = new List<BankAccount>(),
                BankDeposits = new List<BankDeposit>(),
                Credits = new List<Credit>(),
                InstallmentPlans = new List<InstallmentPlan>()
            };

            if (client != null)
            {
                _context.Users.Remove(user);
                _context.Clients.Add(client);
                await _context.SaveChangesAsync();

                return RedirectToAction("ClientProfile", "Client");
            }
        }
        
        return View(model);
    }

    public Client ClientInfo()
    {
        var client = _context.Clients.Include(c => c.BankAccounts)!
            .ThenInclude(b => b.Bank)
            .Include(c => c.Role)
            .Include(c => c.BankDeposits)
            .ThenInclude(b => b.BankAccount)
            .Include(c => c.Credits)
            .ThenInclude(c => c.BankAccount)
            .Include(c => c.InstallmentPlans)
            .ThenInclude(i => i.BankAccount)
            .FirstAsync(u => u.Email.Equals(User.Identity.Name)).Result;
        return client;
    }

    [HttpGet]
    [Authorize]
    public IActionResult ClientProfile()
    {
        return View(new ClientProfileModel
        {
            Client = ClientInfo()
        });
    }
    
    [HttpGet]
    [Authorize]
    public IActionResult NewBankAccount()
    {
        return View(new NewBankAccountModel
        {
            Banks = _context.Banks.ToList()
        });
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> NewBankAccount(NewBankAccountModel model)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var bankAccount = new BankAccount
            {
                Bank = await _context.Banks.FirstOrDefaultAsync(b => b.Id == model.BankId),
                Money = model.Money,
                Name = model.AccountName,
                IsBlocked = false,
                IsFrozen = false
            };
            
            client.BankAccounts?.Add(bankAccount);
            bankAccount.Client = client;
            _context.Clients.Update(client);
            _context.BankAccounts.Add(bankAccount);
            
            await _context.SaveChangesAsync();
            return RedirectToAction("ClientProfile", "Client");
        }

        return View(model);
    }

    [HttpGet]
    [Authorize]
    public IActionResult BankTransfer()
    {
        return View(new TransferModel
        {
            ClientAccounts = ClientInfo().BankAccounts
        });
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> BankTransfer(TransferModel model)
    {
        if (ModelState.IsValid)
        {
            var toAccount = _context.BankAccounts.FirstOrDefaultAsync(b => b.Id.Equals(model.ToAccountId)).Result;
            if (toAccount != null && toAccount.IsBlocked == false)
            {
                var client = ClientInfo();
                var clientAccount = client.BankAccounts.Find(acc => acc.Id == model.FromAccountId);

                if (clientAccount.Money >= model.TransferAmount 
                    && clientAccount.IsBlocked == false
                    && clientAccount.IsFrozen == false)
                {
                    clientAccount.Money -= model.TransferAmount;
                    toAccount.Money += model.TransferAmount;
                    
                    _context.Clients.Update(client);
                    _context.BankAccounts.Update(clientAccount);
                    _context.BankAccounts.Update(toAccount);
                    _context.Transfers.Add(new Transfer
                    {
                        FromAccountId = model.FromAccountId,
                        ToAccountId = model.ToAccountId,
                        TransferAmount = model.TransferAmount,
                        BankId = clientAccount.Bank.Id
                    });
            
                    await _context.SaveChangesAsync();
                }
                
                return RedirectToAction("ClientProfile", "Client");
            }
        }
        
        return View(model);
    }
    
    [HttpGet]
    [Authorize]
    public IActionResult NewBankDeposit()
    {
        return View(new NewBankDepositModel
        {
            BankAccounts = ClientInfo().BankAccounts
        });
    }
    
    [HttpPost]
    [Authorize]
    public async Task<IActionResult> NewBankDeposit(NewBankDepositModel model)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var clientAccount = client.BankAccounts.Find(acc => acc.Id == model.AccountId);
            if (clientAccount.IsBlocked == true || clientAccount.IsFrozen == true)
            {
                return RedirectToAction("ClientProfile", "Client");
            }
            
            clientAccount.Money -= model.Money;
            var deposit = DateTime.Today;
            var withdraw = model.WithdrawDate;
            if (withdraw < deposit)
            {
                var buffer = deposit - withdraw;
                withdraw = deposit + buffer;
            }
            
            var bankDeposit = new BankDeposit
            {
                Name = model.DepositName,
                BankAccount = clientAccount,
                DepositDate = deposit,
                WithdrawDate = withdraw,
                Money = model.Money,
                Percent = model.Percent,
            };
            
            client.BankDeposits.Add(bankDeposit);
            _context.Clients.Update(client);
            _context.BankAccounts.Update(clientAccount);
            await _context.SaveChangesAsync();
            
            return RedirectToAction("ClientProfile", "Client");
        }
        
        return View(model);
    }
    
    
    [Authorize]
    public async Task<IActionResult> CloseBankAccount(int id)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var deposit = client.BankDeposits.Find(d => d.BankAccount.Id == id);
            var credit = client.Credits.Find(c => c.BankAccount.Id == id);
            var instellmentPlan = client.InstallmentPlans.Find(i => i.BankAccount.Id == id);
            var account = client.BankAccounts.Find(a => a.Id == id);
            if (deposit == null && credit == null && instellmentPlan == null &&
                account.IsBlocked == false  && account.IsFrozen == false)
            {
                client.BankAccounts.Remove(account);
                account = await _context.BankAccounts.FirstOrDefaultAsync(a => a.Id == id);
                
                _context.BankAccounts.Remove(account);
                _context.Clients.Update(client);
                await _context.SaveChangesAsync();
            }
        }

        return RedirectToAction("ClientProfile", "Client");
    }


    [Authorize]
    public async Task<IActionResult> CloseBankDeposit(int id)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var deposit = client.BankDeposits.Find(d => d.Id == id);
            var withdrawDate = DateTime.Today;

            if (deposit.WithdrawDate < withdrawDate)
            {
                withdrawDate = deposit.WithdrawDate;
            }

            int months = withdrawDate.Month - deposit.DepositDate.Month;
            int currentMoney = deposit.Money + (deposit.Money * (deposit.Percent) / 100 * months) / 12;
            
            var account = client.BankAccounts.Find(b => b.Id == deposit.BankAccount.Id);
            if (account.IsBlocked == false)
            {
                account.Money += currentMoney;
                client.BankDeposits.Remove(deposit);
            
                _context.Clients.Update(client);
                _context.BankAccounts.Update(account);
                await _context.SaveChangesAsync();
            }
        }

        return RedirectToAction("ClientProfile", "Client");
    }

    [HttpGet]
    [Authorize]
    public IActionResult NewCredit()
    {
        return View(new NewCreditModel
        {
            BankAccounts = ClientInfo().BankAccounts
        });
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> NewCredit(NewCreditModel model)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var account = client.BankAccounts.Find(acc => acc.Id == model.AccountId);
            if (account.IsBlocked == true || account.IsFrozen == true)
            {
                return RedirectToAction("ClientProfile", "Client");
            }
            
            var credit = new Credit
            {
                BankAccount = account,
                DepositDate = DateTime.Today,
                Money = model.Money,
                Percent = model.Percent,
                MonthCount = model.Months,
                PaidMonthCount = 0
            };
            account.Money += model.Money;
            
            client.Credits.Add(credit);
            _context.Clients.Update(client);
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();

            return RedirectToAction("ClientProfile", "Client");
        }

        return View(model);
    }
    
    [HttpGet]
    [Authorize]
    public IActionResult NewInstallmentPlan()
    {
        return View(new NewInstallmentPlanModel
        {
            BankAccounts = ClientInfo().BankAccounts
        });
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> NewInstallmentPlan(NewInstallmentPlanModel model)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var account = client.BankAccounts.Find(acc => acc.Id == model.AccountId);
            if (account.IsBlocked == true || account.IsFrozen == true)
            {
                return RedirectToAction("ClientProfile", "Client");
            }
            
            var installmentPlan = new InstallmentPlan
            {
                BankAccount = account,
                DepositDate = DateTime.Today,
                Money = model.Money,
                MonthCount = model.Months,
                PaidMonthCount = 0
            };
            account.Money += model.Money;
            
            client.InstallmentPlans.Add(installmentPlan);
            _context.Clients.Update(client);
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();

            return RedirectToAction("ClientProfile", "Client");
        }

        return View(model);
    }

    [Authorize]
    public async Task<IActionResult> PayForCredit(int id)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var credit = client.Credits.Find(c => c.Id == id);

            var account = credit.BankAccount;
            if (account.IsBlocked == true || account.IsFrozen == true)
            {
                return RedirectToAction("ClientProfile", "Client");
            }
            
            account.Money -= credit.Money * (100 + credit.Percent) / credit.MonthCount;
            credit.PaidMonthCount++;

            if (credit.MonthCount == credit.PaidMonthCount)
            {
                client.Credits.Remove(credit);
            }
            
            _context.Clients.Update(client);
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();
        }
        
        return RedirectToAction("ClientProfile", "Client");
    }
    
    [Authorize]
    public async Task<IActionResult> PayForInstallmentPlan(int id)
    {
        if (ModelState.IsValid)
        {
            var client = ClientInfo();
            var installmentPlan = client.InstallmentPlans.Find(c => c.Id == id);

            var account = installmentPlan.BankAccount;
            if (account.IsBlocked == true || account.IsFrozen == true)
            {
                return RedirectToAction("ClientProfile", "Client");
            }
            
            account.Money -= installmentPlan.Money / installmentPlan.MonthCount;
            installmentPlan.PaidMonthCount++;

            if (installmentPlan.MonthCount == installmentPlan.PaidMonthCount)
            {
                client.InstallmentPlans.Remove(installmentPlan);
            }
            
            _context.Clients.Update(client);
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();
        }
        
        return RedirectToAction("ClientProfile", "Client");
    }
}