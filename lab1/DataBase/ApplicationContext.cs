using lab1.Entities;
using lab1.Entities.Roles;
using Microsoft.EntityFrameworkCore;

namespace lab1.DataBase;

public class ApplicationContext : DbContext
{
    public DbSet<User> Users { get; set; }
    public DbSet<Client> Clients { get; set; }
    public DbSet<Operator> Operators { get; set; }
    public DbSet<Manager> Managers { get; set; }
    public DbSet<Specialist> Specialists { get; set; }

    public DbSet<Bank> Banks { get; set; }
    public DbSet<Role> Roles { get; set; }
    public DbSet<Company> Companies { get; set; }

    public DbSet<Transfer> Transfers { get; set; }
    public DbSet<SalaryTransfer> SalaryTransfers { get; set; }
    public DbSet<BankAccount> BankAccounts { get; set; }
    public DbSet<Credit> Credits { get; set; }
    public DbSet<InstallmentPlan> InstallmentPlans { get; set; }
    public DbSet<SalaryProject> SalaryProjects { get; set; }

    public ApplicationContext(DbContextOptions<ApplicationContext> options)
        : base(options)
    {
        Database.EnsureCreated();
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        var userRole = new Role { Name = "user", Id = 0 };
        var clientRole = new Role { Name = "client", Id = 1 };
        var operatorRole = new Role { Name = "operator", Id = 2 };
        var managerRole = new Role { Name = "manager", Id = 3 };
        var specialistRole = new Role { Name = "specialist", Id = 4 };
        
        var firstBank = new Bank
        {
            Id = 5,
            LegalName = "AlphaBank",
            BankIdentificationNumber = "ALFABY2X",
            LegalAddress = "Ул. Сурганова, 43-47, Минск, Республика Беларусь",
            Type = "ЗАО"
        };
        
        var secondBank = new Bank
        {
            Id = 6,
            LegalName = "Sberbank",
            BankIdentificationNumber = "BPSBBY2X",
            LegalAddress = "бульвар Мулявина, 6, Минск, Республика Беларусь",
            Type = "ОАО"
        };
        
        var thirdBank = new Bank
        {
            Id = 7,
            LegalName = "Tinkoff",
            BankIdentificationNumber = "44525974",
            LegalAddress = "1-й Волоколамс пр-д, 10, Москва, Российская Федерация",
            Type = "АО"
        };

        var firstCompany = new Company
        {
            Id = 8,
            BankId = firstBank.BankIdentificationNumber,
            LegalAddress = "ул. Немига, 36, Минск, Республика Беларусь",
            LegalName = "Лукойл Белоруссия",
            PayerAccountNumber = 100126124,
            Type = "ИООО"
        };
        
        var secondCompany = new Company
        {
            Id = 9,
            BankId = secondBank.BankIdentificationNumber,
            LegalAddress = "набережная Софийская, 26/1, Москва, Российская Федерация",
            LegalName = "Роснефть",
            PayerAccountNumber = 190050244,
            Type = "ПАО"
        };
        
        var thirdCompany = new Company
        {
            Id = 10,
            BankId = thirdBank.BankIdentificationNumber,
            LegalAddress = "ул. Солнечная, 15/5, Краснодар, Российская Федерация",
            LegalName = "Магнит",
            PayerAccountNumber = 100074592,
            Type = "ООО"
        };

        var roles = new List<Role>();
        roles.Add(userRole);
        roles.Add(clientRole);
        roles.Add(operatorRole);
        roles.Add(managerRole);
        roles.Add(specialistRole);
        
        var banks = new List<Bank>();
        banks.Add(firstBank);
        banks.Add(secondBank);
        banks.Add(thirdBank);

        var companies = new List<Company>();
        companies.Add(firstCompany);
        companies.Add(secondCompany);
        companies.Add(thirdCompany);
        
        modelBuilder.Entity<Role>().HasData(roles);
        modelBuilder.Entity<Bank>().HasData(banks);
        modelBuilder.Entity<Company>().HasData(companies);

        modelBuilder.Entity<Credit>().ToTable("Credits");
        modelBuilder.Entity<InstallmentPlan>().ToTable("InstallmentPlans");
        modelBuilder.Entity<SalaryProject>().ToTable("SalaryProjects");
        
        modelBuilder.Entity<BankAccount>().ToTable("BankAccounts");
        modelBuilder.Entity<Bank>().ToTable("Banks");
        modelBuilder.Entity<Company>().ToTable("Companies");
        modelBuilder.Entity<User>().ToTable("Users");
        
        modelBuilder.Entity<Client>().ToTable("Clients");
        modelBuilder.Entity<Operator>().ToTable("Operators");
        modelBuilder.Entity<Manager>().ToTable("Managers");
        modelBuilder.Entity<Specialist>().ToTable("Specialists");
        modelBuilder.Entity<Transfer>().ToTable("Transfers");
        modelBuilder.Entity<SalaryTransfer>().ToTable("SalaryTransfers");
        base.OnModelCreating(modelBuilder);
    }
}
