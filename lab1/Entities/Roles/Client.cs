using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities.Roles;

[Table("Clients")]
public class Client : User
{
    public string? PassportSeriesAndNumber { get; set; }
    public string? IdentificationNumber { get; set; }
    public List<Bank>? Banks { get; set; }
    public List<BankAccount>? BankAccounts { get; set; }
    public List<BankDeposit>? BankDeposits { get; set; }
    public List<Credit>? Credits { get; set; }
    public List<InstallmentPlan> InstallmentPlans { get; set; }
    public bool IsApproved { get; set; }
}