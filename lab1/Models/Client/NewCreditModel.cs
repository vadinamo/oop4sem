using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewCreditModel
{
    public int AccountId { get; set; }
    
    [Required(ErrorMessage = "Не указан срок выплаты кредита")]
    public int Months { get; set; }
    
    [Required(ErrorMessage = "Не указана сумма кредита")]
    public int Money { get; set; }
    
    [Required(ErrorMessage = "Не указан процент")]
    public int Percent { get; set; }
    
    public List<BankAccount>? BankAccounts { get; set; }
}