using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewInstallmentPlanModel
{
    public int AccountId { get; set; }
    
    [Required(ErrorMessage = "Не указан срок выплаты рассрочки")]
    [Range(1,100,ErrorMessage="Неверно указано количество месяцев")]
    public int Months { get; set; }
    
    [Required(ErrorMessage = "Не указана сумма рассрочки")]
    [Range(1,int.MaxValue,ErrorMessage="Неверно указана сумма рассрочки")]
    public int Money { get; set; }
    
    public List<BankAccount>? BankAccounts { get; set; }
}