using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewBankDepositModel
{
    [Required(ErrorMessage = "Не указано имя вклада")]
    public string DepositName { get; set; }
    
    [Required(ErrorMessage = "Не указана сумма вклада")]
    public int Money { get; set; }
    
    [Required(ErrorMessage = "Не указан процент вклада")]
    public int Percent { get; set; }
    
    public int AccountId { get; set; }
    
    [Required]
    [DataType(DataType.Date)]
    public DateTime WithdrawDate { get; set; }

    public List<BankAccount>? BankAccounts { get; set; }
}