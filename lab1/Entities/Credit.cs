using System.ComponentModel.DataAnnotations;

namespace lab1.Entities;

public class Credit
{
    [Key]public int? Id { get; set; }
    public BankAccount? BankAccount { get; set; }
    
    public int Money { get; set; }
    public int Percent { get; set; }
    
    public DateTime DepositDate { get; set; }
    public DateTime WithdrawDate { get; set; }
}