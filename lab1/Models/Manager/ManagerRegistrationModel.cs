using lab1.Entities;

namespace lab1.Models.Manager;

public class ManagerRegistrationModel
{
    public int BankId { get; set; }
    public List<Bank>? Banks { get; set; }
}