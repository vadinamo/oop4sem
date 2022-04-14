using lab1.Entities;

namespace lab1.Models.Operator;

public class OperatorRegistrationModel
{
    public int BankId { get; set; }
    public List<Bank>? Banks { get; set; }
}