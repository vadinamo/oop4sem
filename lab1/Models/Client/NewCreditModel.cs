using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewCreditModel
{
    public int AccountId { get; set; }
    
    [Required(ErrorMessage = "Не указан срок выплаты кредита")]
    [Range(1,100,ErrorMessage="Неверно указано количество месяцев")]
    public int Months { get; set; }
    
    [Required(ErrorMessage = "Не указана сумма кредита")]
    [Range(1,int.MaxValue,ErrorMessage="Неверно указана сумма кредита")]
    public int Money { get; set; }
    
    [Required(ErrorMessage = "Не указан процент")]
    [Range(1,100,ErrorMessage="Неверно указан процент кредита")]
    public int Percent { get; set; }
    
    public List<BankAccount>? BankAccounts { get; set; }
}