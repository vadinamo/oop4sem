using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities.Roles;

[Table("Specialists")]
public class Specialist : User
{
    public Company? Company { get; set; }
    public List<SalaryProject>? SalaryProjects { get; set; }
}