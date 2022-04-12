using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Account;

public class RegisterModel
{
    [Required(ErrorMessage ="Не указан Email")]
    [DataType(DataType.EmailAddress)]
    public string Email { get; set; }
         
    [Required(ErrorMessage = "Не указан пароль")]
    [DataType(DataType.Password)]
    public string Password { get; set; }
         
    [DataType(DataType.Password)]
    [Compare("Password", ErrorMessage = "Пароль введен неверно")]
    public string ConfirmPassword { get; set; }
    
    [Required(ErrorMessage = "Не указана фамилия")]
    [DataType(DataType.Text)]
    public string? Surname { get; set; }
    
    [Required(ErrorMessage = "Не указано имя")]
    [DataType(DataType.Text)]
    public string? FirstName { get; set; }
    
    [Required(ErrorMessage = "Не указано отчество")]
    [DataType(DataType.Text)]
    public string? Patronymic { get; set; }
    
    [Required(ErrorMessage = "Не указан номер телефона")]
    [DataType(DataType.PhoneNumber)]
    public string? PhoneNumber { get; set; }

    public int? RoleId { get; set; }
    public List<Role>? Roles { get; set; }
}