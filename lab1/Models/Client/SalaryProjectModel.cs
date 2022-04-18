using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class SalaryProjectModel
{
    [Required(ErrorMessage = "Не указана зарплата")]
    [Range(1,int.MaxValue,ErrorMessage="Неверно указана зарплата")]
    public int Salary { get; set; }
    
    public List<BankAccount>? BankAccounts { get; set; }
    public int AccountId { get; set; }
}