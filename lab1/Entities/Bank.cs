using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using lab1.Entities.Roles;

namespace lab1.Entities;

[Table("Banks")]
public class Bank
{
    [Key] public int? Id { get; set; }
    public string? LegalName { get; set; }
    public string? BankIdentificationNumber { get; set; }
    public string? LegalAddress { get; set; }
    public string? Type { get; set;  }
}