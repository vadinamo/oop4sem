using lab1.DataBase;
using lab1.Entities;
using lab1.Entities.Roles;
using lab1.Models.Operator;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace lab1.Controllers;

public class OperatorController : Controller
{
    private ApplicationContext _context;
    public OperatorController(ApplicationContext context)
    {
        _context = context;
    }
    
    [HttpGet]
    [Authorize]
    public IActionResult OperatorRegistration()
    {
        return View(new OperatorRegistrationModel
        {
            Banks = _context.Banks.ToList()
        });
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> OperatorRegistration(OperatorRegistrationModel model)
    {
        if (ModelState.IsValid)
        {
            var user = _context.Users.FirstOrDefaultAsync(u => u.Email.Equals(User.Identity.Name)).Result;
            var bankOperator = new Operator
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
                SalaryProjects = new List<SalaryProject>()
            };

            if (bankOperator != null)
            {
                _context.Users.Remove(user);
                _context.Operators.Add(bankOperator);
                await _context.SaveChangesAsync();

                return RedirectToAction("OperatorProfile", "Operator");
            }
        }
        
        return View(model);
    }
    
    public Operator OperatorInfo()
    {
        var bankOperator = _context.Operators.Include(o => o.Transfers)
            .Include(o => o.Bank)
            .Include(o => o.Role)
            .Include(o => o.SalaryProjects)
            .FirstAsync(o => o.Email.Equals(User.Identity.Name)).Result;
        return bankOperator;
    }
    
    [Authorize]
    public async Task<IActionResult> OperatorProfile()
    {
        var bankOperator = OperatorInfo();
        var transfersList = _context.Transfers.ToList();
        bankOperator.Transfers.Clear();
        foreach (var transfer in transfersList)
        {
            if (transfer.BankId == bankOperator.Bank.Id)
            {
                bankOperator.Transfers.Add(transfer);
            }
        }
        
        bankOperator.SalaryProjects.Clear();
        var salaryProjects = _context.SalaryProjects
            .Include(s => s.BankAccount)
            .ThenInclude(a => a.Client)
            .ToList();
        foreach (var project in salaryProjects)
        {
            if (project.BankAccount.Bank == bankOperator.Bank 
                && project.ApprovedByOperator == false
                && project.ApprovedByCompany == true)
            {
                bankOperator.SalaryProjects.Add(project);
            }
        }

        _context.Operators.Update(bankOperator);
        await _context.SaveChangesAsync();
        
        return View(new OperatorProfileModel
        {
            Operator = bankOperator
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
                
                _context.BankAccounts.Update(fromAccount);
                _context.BankAccounts.Update(toAccount);
                _context.Transfers.Remove(transfer);
                await _context.SaveChangesAsync();
            }
        }

        return RedirectToAction("Profile", "Account");
    }
    
    public SalaryProject SalaryProjectInfo(int id)
    {
        var salaryProject = _context.SalaryProjects
            .Include(p => p.BankAccount)
            .FirstAsync(p => p.Id == id).Result;
        
        return salaryProject;
    }
    
    [Authorize]
    public async Task<IActionResult> SalaryProjectApprove(int id)
    {
        if (ModelState.IsValid)
        {
            var salaryProject = SalaryProjectInfo(id);
            salaryProject.ApprovedByOperator = true;
            _context.SalaryProjects.Update(salaryProject);
            await _context.SaveChangesAsync();
        }

        return RedirectToAction("Profile", "Account");
    }
}