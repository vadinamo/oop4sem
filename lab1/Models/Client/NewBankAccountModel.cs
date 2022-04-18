using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewBankAccountModel
{
    [Required]
    [DataType(DataType.Text)]
    public string AccountName { get; set; }
    public int BankId { get; set; }
    
    [Required]
    [DataType(DataType.Text)]
    [Range(0,int.MaxValue,ErrorMessage="Неверное количество денег")]
    public int Money { get; set; }
    public List<Bank>? Banks { get; set; }
}