using lab1.Entities;

namespace lab1.Models.Specialist;

public class SpecialistRegistrationModel
{
    public int? CompanyId { get; set; }
    public List<Company>? Companies { get; set; }
}