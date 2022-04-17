using lab1.DataBase;
using lab1.Entities;
using lab1.Entities.Roles;
using lab1.Models.Specialist;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace lab1.Controllers;

public class SpecialistController : Controller
{
    private ApplicationContext _context;
    public SpecialistController(ApplicationContext context)
    {
        _context = context;
    }

    [HttpGet]
    [Authorize]
    public IActionResult SpecialistRegistration()
    {
        return View(new SpecialistRegistrationModel
        {
            Companies = _context.Companies.ToList()
        });
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> SpecialistRegistration(SpecialistRegistrationModel model)
    {
        if (ModelState.IsValid)
        {
            var user = _context.Users.FirstOrDefaultAsync(u => u.Email.Equals(User.Identity.Name)).Result;
            var specialist = new Specialist
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

                Company = _context.Companies.FirstOrDefault(c => c.Id == model.CompanyId),
                SalaryProjects = new List<SalaryProject>()
            };
            
            if (specialist != null)
            {
                _context.Users.Remove(user);
                _context.Specialists.Add(specialist);
                await _context.SaveChangesAsync();

                return RedirectToAction("Profile", "Account");
            }
        }

        return View(model);
    }

    public Specialist SpecialistInfo()
    {
        var specialist = _context.Specialists.Include(s => s.SalaryProjects)
            .ThenInclude(s => s.BankAccount)
            .ThenInclude(a => a.Client)
            .Include(s => s.Company)
            .Include(s => s.Role)
            .FirstAsync(s => s.Email.Equals(User.Identity.Name)).Result;

        return specialist;
    }

    [Authorize]
    public async Task<IActionResult> SpecialistProfile()
    {
        var specialist = SpecialistInfo();
        specialist.SalaryProjects.Clear();

        var salaryProjects = _context.SalaryProjects
            .Include(s => s.BankAccount)
            .ThenInclude(a => a.Client)
            .ToList();
        foreach (var project in salaryProjects)
        {
            if (project.Company == specialist.Company)
            {
                specialist.SalaryProjects.Add(project);
            }
        }
        
        return View(new SpecialistProfileModel
        {
            Specialist = specialist
        });
    }

    public SalaryProject SalaryProjectInfo(int id)
    {
        var salaryProject = _context.SalaryProjects
            .Include(p => p.BankAccount)
            .ThenInclude(a => a.Bank)
            .Include(p => p.Company)
            .FirstAsync(p => p.Id == id).Result;
        return salaryProject;
    }
    
    [Authorize]
    public async Task<IActionResult> SalaryProjectApprove(int id)
    {
        if (ModelState.IsValid)
        {
            var salaryProject = SalaryProjectInfo(id);
            salaryProject.ApprovedByCompany = true;
            _context.SalaryProjects.Update(salaryProject);
            await _context.SaveChangesAsync();
        }

        return RedirectToAction("Profile", "Account");
    }
    
    [Authorize]
    public async Task<IActionResult> SalaryProjectDecline(int id)
    {
        if (ModelState.IsValid)
        {
            var salaryProject = SalaryProjectInfo(id);
            salaryProject.BankAccount.IsSalary = false;
            
            _context.SalaryProjects.Remove(salaryProject);
            await _context.SaveChangesAsync();
        }

        return RedirectToAction("Profile", "Account");
    }

    [Authorize]
    public async Task<IActionResult> PaySalary(int id)
    {
        if (ModelState.IsValid)
        {
            var salaryProject = SalaryProjectInfo(id);

            var salaryTransfer = new SalaryTransfer
            {
                BankId = salaryProject.BankAccount.Bank.Id,
                CompanyName = salaryProject.Company.LegalName,
                IsApproved = false,
                ToAccountId = salaryProject.BankAccount.Id,
                TransferAmount = salaryProject.Salary
            };

            _context.SalaryTransfers.Add(salaryTransfer);
            await _context.SaveChangesAsync();
        }

        return RedirectToAction("Profile", "Account");
    }
}