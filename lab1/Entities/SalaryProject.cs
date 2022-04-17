using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities;

[Table("SalaryProjects")]
public class SalaryProject
{
    [Key]public int? Id { get; set; }
    public int? Salary { get; set; }
    public BankAccount? BankAccount { get; set; }
    public Company? Company { get; set; }
    public bool? IsApproved { get; set; }
}