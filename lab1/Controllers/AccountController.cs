using System.Security.Claims;
using lab1.DataBase;
using lab1.Entities.Roles;
using lab1.Models.Account;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace lab1.Controllers;

public class AccountController : Controller
{
    private ApplicationContext _context;
    public AccountController(ApplicationContext context)
    {
        _context = context;
    }
    
    [HttpGet]
    public IActionResult Register()
    {
        return View(new RegisterModel
        {
            Roles = _context.Roles.ToList()
        });
    }
    
    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Register(RegisterModel model)
    {
        if (ModelState.IsValid)
        {
            User user = await _context.Users.FirstOrDefaultAsync(u => u.Email == model.Email);
            if (user == null)
            {
                // добавляем пользователя в бд
                user = new User
                {
                    Email = model.Email, 
                    Password = model.Password,
                    
                    FirstName = model.FirstName,
                    Surname = model.Surname,
                    Patronymic = model.Patronymic,
                    
                    PhoneNumber = model.PhoneNumber
                };
                var userRole = await _context.Roles.FirstOrDefaultAsync(r => r.Id == model.RoleId);
                if (userRole != null) user.Role = userRole;

                _context.Users.Add(user);
                await _context.SaveChangesAsync();

                await Authenticate(user); // аутентификация

                return RedirectToAction("Profile", "Account");
            }
            else
                ModelState.AddModelError("", "Некорректные логин и(или) пароль");
        }
        return View(model);
    }
    
    [HttpGet]
    public IActionResult Login()
    {
        return View();
    }
    
    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Login(LoginModel model)
    {
        if (ModelState.IsValid)
        {
            User user = await _context.Users
                .Include(u => u.Role)
                .FirstOrDefaultAsync(u => u.Email == model.Email && u.Password == model.Password);
            if (user != null)
            {
                await Authenticate(user); // аутентификация

                return RedirectToAction("Profile", "Account");
            }
            ModelState.AddModelError("", "Некорректные логин и(или) пароль");
        }
        return View(model);
    }
    
    private async Task Authenticate(User user)
    {
        var claims = new List<Claim>
        {
            new(ClaimsIdentity.DefaultNameClaimType, user.Email),
            new(ClaimsIdentity.DefaultRoleClaimType, user.Role?.Name)
        };
        var id = new ClaimsIdentity(claims, "ApplicationCookie", ClaimsIdentity.DefaultNameClaimType,
            ClaimsIdentity.DefaultRoleClaimType);
        await HttpContext.SignInAsync(CookieAuthenticationDefaults.AuthenticationScheme, new ClaimsPrincipal(id));
    }
    
    public async Task<IActionResult> Logout()
    {
        await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
        return RedirectToAction("Login", "Account");
    }

    [Authorize]
    public IActionResult Profile()
    {
        var user = _context.Users.FirstOrDefaultAsync(u => u.Email.Equals(User.Identity.Name)).Result;
        var client = _context.Clients.FirstOrDefaultAsync(c => c.Email.Equals(User.Identity.Name)).Result;
        var bankOperator = _context.Operators.FirstOrDefaultAsync(c => c.Email.Equals(User.Identity.Name)).Result;
        var manager = _context.Managers.FirstOrDefaultAsync(c => c.Email.Equals(User.Identity.Name)).Result;
        var specialist = _context.Specialists.FirstOrDefaultAsync(c => c.Email.Equals(User.Identity.Name)).Result;
        switch (user.RoleId)
        {
            case 1: //client role
                if (client == null)
                {
                    return RedirectToAction("ClientRegistration", "Client");
                }

                else
                {
                    return RedirectToAction("ClientProfile", "Client");
                }

            case 2: //operator role
                if (bankOperator == null)
                {
                    return RedirectToAction("OperatorRegistration", "Operator");
                }

                else
                {
                    return RedirectToAction("OperatorProfile", "Operator");
                }

            case 3: //manager role
                if (manager == null)
                {
                    return RedirectToAction("ManagerRegistration", "Manager");
                }

                else
                {
                    return RedirectToAction("ManagerProfile", "Manager");
                }

            case 4: //specialist role
                if (specialist == null)
                {
                    return RedirectToAction("SpecialistRegistration", "Specialist");
                }

                else
                {
                    return RedirectToAction("SpecialistProfile", "Specialist");
                }

            case 5: //admin role
                break;
        }

        return RedirectToAction("Register", "Account");
    }
}