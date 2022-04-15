using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities;


[Table("Companies")]
public class Company
{
    [Key] public int? Id { get; set; }
    public string? LegalName { get; set; }
    public int? PayerAccountNumber { get; set; }
    public string? Type { get; set; }
    public string? LegalAddress { get; set; }
    public string BankId { get; set; }
}