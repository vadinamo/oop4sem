using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities;

[Table("Transfers")]
public class Transfer
{
    [Key] public int? Id { get; set; }
    public int? FromAccountId { get; set; }
    public int? BankId { get; set; }
    public int? ToAccountId { get; set; }
    public int? TransferAmount { get; set; }
}