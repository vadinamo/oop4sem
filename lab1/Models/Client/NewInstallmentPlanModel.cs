using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewInstallmentPlanModel
{
    public int AccountId { get; set; }
    
    [Required(ErrorMessage = "Не указан срок выплаты рассрочки")]
    public int Months { get; set; }
    
    [Required(ErrorMessage = "Не указана сумма рассрочки")]
    public int Money { get; set; }
    
    public List<BankAccount>? BankAccounts { get; set; }
}