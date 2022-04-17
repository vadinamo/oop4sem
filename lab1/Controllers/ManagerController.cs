using lab1.DataBase;
using lab1.Entities;
using lab1.Entities.Roles;
using lab1.Models.Manager;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace lab1.Controllers;

public class ManagerController : Controller
{
    private ApplicationContext _context;
    public ManagerController(ApplicationContext context)
    {
        _context = context;
    }
    
    [HttpGet]
    [Authorize]
    public IActionResult ManagerRegistration()
    {
        return View(new ManagerRegistrationModel
        {
            Banks = _context.Banks.ToList()
        });
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> ManagerRegistration(ManagerRegistrationModel model)
    {
        if (ModelState.IsValid)
        {
            var user = _context.Users.FirstOrDefaultAsync(u => u.Email.Equals(User.Identity.Name)).Result;
            var manager = new Manager
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
                Bank = _context.Banks.FirstOrDefaultAsync(b => b.Id == model.BankId).Result,
                
                Transfers = new List<Transfer>(),
                BankAccounts = new List<BankAccount>(),
                ClientsToApprove = new List<Client>(),
                CreditsToApprove = new List<Credit>(),
                InstallmentPlansToApprove = new List<InstallmentPlan>(),
                SalaryProjects = new List<SalaryProject>()
            };

            if (manager != null)
            {
                _context.Users.Remove(user);
                _context.Managers.Add(manager);
                await _context.SaveChangesAsync();

                return RedirectToAction("ManagerProfile", "Manager");
            }
        }
        
        return View(model);
    }
    
    public Manager ManagerInfo()
    {
        var manager = _context.Managers.Include(m => m.Transfers)
            .Include(m => m.BankAccounts)
            .Include(m => m.Bank)
            .Include(m => m.Role)
            .Include(m => m.ClientsToApprove)
            .Include(m => m.CreditsToApprove)
            .ThenInclude(c => c.BankAccount)
            .ThenInclude(b => b.Bank)
            .Include(m => m.InstallmentPlansToApprove)
            .ThenInclude(i => i.BankAccount)
            .ThenInclude(b => b.Bank)
            .Include(o => o.SalaryProjects)
            .FirstAsync(m => m.Email.Equals(User.Identity.Name)).Result;
        return manager;
    }

    public BankAccount AccountInfo(int id)
    {
        var account = _context.BankAccounts
            .Include(a => a.Bank)
            .Include(a => a.Client)
            .FirstAsync(a => a.Id == id).Result;
        return account;
    }
    
    [Authorize]
    public async Task<IActionResult> ManagerProfile()
    {
        var manager = ManagerInfo();
        var transfersList = _context.Transfers.ToList();
        manager.Transfers.Clear();
        foreach (var transfer in transfersList)
        {
            if (transfer.BankId == manager.Bank.Id)
            {
                manager.Transfers.Add(transfer);
            }
        }
        
        var accountsList = _context.BankAccounts.ToList();
        manager.BankAccounts.Clear();
        foreach (var account in accountsList)
        {
            var currentAccount = AccountInfo(account.Id);
            if (currentAccount.Bank.Id == manager.Bank.Id)
            {
                manager.BankAccounts.Add(currentAccount);
            }
        }

        var clientsToApprove = _context.Clients.ToList();
        manager.ClientsToApprove.Clear();
        foreach (var client in clientsToApprove)
        {
            if (!client.IsApproved)
            {
                manager.ClientsToApprove.Add(client);
            }
        }

        var creditsList = _context.Credits.ToList();
        manager.CreditsToApprove.Clear();
        foreach (var credit in creditsList)
        {
            if (credit.BankAccount.Bank.Id == manager.Bank.Id && !credit.IsApproved)
            {
                manager.CreditsToApprove.Add(credit);
            }
        }
        
        var installmentPlansList = _context.InstallmentPlans.ToList();
        manager.InstallmentPlansToApprove.Clear();
        foreach (var installmentPlan in installmentPlansList)
        {
            if (installmentPlan.BankAccount.Bank.Id == manager.Bank.Id && !installmentPlan.IsApproved)
            {
                manager.InstallmentPlansToApprove.Add(installmentPlan);
            }
        }
        
        manager.SalaryProjects.Clear();
        var salaryProjects = _context.SalaryProjects
            .Include(s => s.BankAccount)
            .ThenInclude(a => a.Client)
            .ToList();
        foreach (var project in salaryProjects)
        {
            if (project.BankAccount.Bank == manager.Bank 
                && project.ApprovedByOperator == false
                && project.ApprovedByCompany == true)
            {
                manager.SalaryProjects.Add(project);
            }
        }
        
        _context.Managers.Update(manager);
        await _context.SaveChangesAsync();
        
        return View(new ManagerProfileModel
        {
            Manager = manager
        });
    }

    [Authorize]
    public async Task<IActionResult> ChangeFreezeStatus (int id)
    {
        if (ModelState.IsValid)
        {
            var account = _context.BankAccounts.FirstOrDefault(c => c.Id == id);
            if (account.IsFrozen == true)
            {
                account.IsFrozen = false;
            }
            else
            {
                account.IsFrozen = true;
            }
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();
        }
        
        return RedirectToAction("ManagerProfile", "Manager");
    }
    
    [Authorize]
    public async Task<IActionResult> ChangeBlockStatus (int id)
    {
        if (ModelState.IsValid)
        {
            var account = _context.BankAccounts.FirstOrDefault(a => a.Id == id);
            if (account.IsBlocked == true)
            {
                account.IsBlocked = false;
            }
            else
            {
                account.IsBlocked = true;
            }
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();
        }
        
        return RedirectToAction("ManagerProfile", "Manager");
    }

    [Authorize]
    public async Task<IActionResult> RegistrationApprove(int id)
    {
        if (ModelState.IsValid)
        {
            var client = _context.Clients.FirstOrDefault(c => c.Id == id);
            client.IsApproved = true;
            _context.Clients.Update(client);
            await _context.SaveChangesAsync();
        }
        
        return RedirectToAction("ManagerProfile", "Manager");
    }
    
    public Credit CreditInfo(int id)
    {
        var credit = _context.Credits
            .Include(c => c.BankAccount)
            .FirstAsync(a => a.Id == id).Result;
        return credit;
    }
    
    [Authorize]
    public async Task<IActionResult> CreditApprove(int id)
    {
        if (ModelState.IsValid)
        {
            var credit = CreditInfo(id);
            credit.IsApproved = true;
            credit.DepositDate = DateTime.Today;

            var account = credit.BankAccount;
            account.Money += credit.Money;
            
            _context.Credits.Update(credit);
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();
        }
        
        return RedirectToAction("ManagerProfile", "Manager");
    }

    public InstallmentPlan InstallmentPlanInfo(int id)
    {
        var installmentPlan = _context.InstallmentPlans
            .Include(c => c.BankAccount)
            .FirstAsync(a => a.Id == id).Result;
        return installmentPlan;
    }
    
    [Authorize]
    public async Task<IActionResult> InstallmentPlanApprove(int id)
    {
        if (ModelState.IsValid)
        {
            var installmentPlab = InstallmentPlanInfo(id);
            installmentPlab.IsApproved = true;
            installmentPlab.DepositDate = DateTime.Today;

            var account = installmentPlab.BankAccount;
            account.Money += installmentPlab.Money;
            
            _context.InstallmentPlans.Update(installmentPlab);
            _context.BankAccounts.Update(account);
            await _context.SaveChangesAsync();
        }
        
        return RedirectToAction("ManagerProfile", "Manager");
    }
}