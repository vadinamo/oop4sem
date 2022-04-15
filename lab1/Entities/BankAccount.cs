using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using lab1.Entities.Roles;

namespace lab1.Entities;

[Table("BankAccounts")]
public class BankAccount
{
    [Key]public int Id { get; set; }
    public string? Name { get; set; }
    public int? Money { get; set; }
    public Bank? Bank { get; set; }
    public Client? Client { get; set; }
    public bool? IsBlocked { get; set; }
    public bool? IsFrozen { get; set; }
}