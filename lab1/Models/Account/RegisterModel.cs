using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Account;

public class RegisterModel
{
    [Required(ErrorMessage ="Не указан Email")]
    [DataType(DataType.EmailAddress)]
    [RegularExpression (@"[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}", ErrorMessage = "Некорректный адрес")]
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
    [RegularExpression(@"^[+][3][7][5][0-9]{9}", ErrorMessage = "Неверно указан номер телефона")]
    public string? PhoneNumber { get; set; }

    public int? RoleId { get; set; }
    public List<Role>? Roles { get; set; }
}