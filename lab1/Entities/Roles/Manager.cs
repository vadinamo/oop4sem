using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities.Roles;

[Table("Managers")]
public class Manager : User
{
    public Bank? Bank { get; set; }
    public List<Transfer>? Transfers { get; set; }
    public List<BankAccount>? BankAccounts { get; set; }
    public List<Client>? ClientsToApprove { get; set; }
}