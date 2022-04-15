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
                BankAccounts = new List<BankAccount>()
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
        
        _context.Managers.Update(manager);
        await _context.SaveChangesAsync();
        
        return View(new ManagerProfileModel
        {
            Manager = manager
        });
    }

    [Authorize]
    public async Task<IActionResult> TransferCancel(int id)
    {
        if (ModelState.IsValid)
        {
            var transfer = _context.Transfers.FirstOrDefault(t => t.Id == id);
            var fromAccount = _context.BankAccounts.FirstOrDefault(c => c.Id == transfer.FromAccountId);
            var toAccount = _context.BankAccounts.FirstOrDefault(c => c.Id == transfer.ToAccountId);

            if (toAccount.Money >= transfer.TransferAmount)
            {
                fromAccount.Money += transfer.TransferAmount;
                toAccount.Money -= transfer.TransferAmount;
                
                var manager = ManagerInfo();
                manager.Transfers.Remove(transfer);

                _context.BankAccounts.Update(fromAccount);
                _context.BankAccounts.Update(toAccount);
                _context.Managers.Update(manager);
                _context.Transfers.Remove(transfer);
                await _context.SaveChangesAsync();
            }
        }

        return RedirectToAction("ManagerProfile", "Manager");
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
            var account = _context.BankAccounts.FirstOrDefault(c => c.Id == id);
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
}