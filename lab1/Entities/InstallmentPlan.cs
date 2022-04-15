using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities;

public class InstallmentPlan
{
    [Key] public int? Id { get; set; }
    public BankAccount? BankAccount { get; set; }

    public int Money { get; set; }
    public DateTime DepositDate { get; set; }
    public int MonthCount { get; set; }
    public int PaidMonthCount { get; set; }
}