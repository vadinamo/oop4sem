using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lab1.Entities.Roles;

[Table("Users")]
public class User
{
    [Key] public int? Id { get; set; }
    public string? Email { get; set; }
    public string? Password { get; set; }

    public string? Surname { get; set; }
    public string? FirstName { get; set; }
    public string? Patronymic { get; set; }
    
    public string? PhoneNumber { get; set; }
    public Role? Role { get; set; }
    public int? RoleId { get; set; }
}