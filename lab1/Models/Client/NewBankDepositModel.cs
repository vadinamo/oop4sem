using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewBankDepositModel
{
    [Required(ErrorMessage = "Не указано имя вклада")]
    public string DepositName { get; set; }
    
    [Required(ErrorMessage = "Не указана сумма вклада")]
    [Range(0,int.MaxValue,ErrorMessage="Неверное количество денег")]
    public int Money { get; set; }
    
    [Required(ErrorMessage = "Не указан процент вклада")]
    [Range(1,100,ErrorMessage="Неверно указан процент")]
    public int Percent { get; set; }
    
    public int AccountId { get; set; }
    
    [Required(ErrorMessage = "Не указана дата снятия")]
    [DataType(DataType.Date)]
    public DateTime WithdrawDate { get; set; }

    public List<BankAccount>? BankAccounts { get; set; }
}