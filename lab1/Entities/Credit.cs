using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities;

[Table("Credits")]
public class Credit
{
    [Key] public int? Id { get; set; }
    public BankAccount? BankAccount { get; set; }

    public int Money { get; set; }
    public int Percent { get; set; }
    public DateTime DepositDate { get; set; }
    public int MonthCount { get; set; }
    public int PaidMonthCount { get; set; }
    public bool IsApproved { get; set; }
}