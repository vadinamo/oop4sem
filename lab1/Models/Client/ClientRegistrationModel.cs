using System.ComponentModel.DataAnnotations;

namespace lab1.Models.Client;

public class ClientRegistrationModel
{
    [Required(ErrorMessage = "Не указана серия и/или номер паспорта")]
    [DataType(DataType.Text)]
    public string PassportSeriesAndNumber { get; set; }
    
    [Required(ErrorMessage = "Не указан идентификационный номер паспорта")]
    [DataType(DataType.Text)]
    public string IdentificationNumber { get; set; }
}