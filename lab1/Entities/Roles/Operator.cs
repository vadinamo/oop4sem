using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities.Roles;

[Table("Operators")]
public class Operator : User
{
    public Bank? Bank { get; set; }
    public List<Transfer>? Transfers { get; set; }
    public List<SalaryProject>? SalaryProjects { get; set; }
}