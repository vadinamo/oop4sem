using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class NewBankAccountModel
{
    public string AccountName { get; set; }
    public int BankId { get; set; }
    public int Money { get; set; }
    public List<Bank>? Banks { get; set; }
}