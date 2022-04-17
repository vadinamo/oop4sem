using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities;

[Table("SalaryTransfers")]
public class SalaryTransfer
{
    [Key] public int? Id { get; set; }
    public int? BankId { get; set; }
    public string? CompanyName { get; set; }
    public int? ToAccountId { get; set; }
    public int? TransferAmount { get; set; }
    public bool? IsApproved { get; set; }
}