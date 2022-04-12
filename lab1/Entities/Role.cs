using System.ComponentModel.DataAnnotations;
using lab1.Entities.Roles;

namespace lab1.Entities;

public class Role
{
    [Key]public int? Id { get; set; }
    public string? Name { get; set; }
    public List<User> Users { get; set; }
}