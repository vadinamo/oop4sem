using System.ComponentModel.DataAnnotations;
using lab1.Entities;

namespace lab1.Models.Client;

public class TransferModel
{
    [Required]
    [DataType(DataType.Text)]
    public int FromAccountId { get; set; }
    
    [Required(ErrorMessage = "Не указан номер счета получателя")]
    [DataType(DataType.Text)]
    public int ToAccountId { get; set; }
    
    [Required(ErrorMessage = "Не указана сумма перевода")]
    [DataType(DataType.Text)]
    public int TransferAmount { get; set; }
    public List<BankAccount>? ClientAccounts { get; set; }
}