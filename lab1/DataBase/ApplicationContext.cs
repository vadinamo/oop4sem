using lab1.Entities;
using lab1.Entities.Roles;
using Microsoft.EntityFrameworkCore;

namespace lab1.DataBase;

public class ApplicationContext : DbContext
{
    public DbSet<User> Users { get; set; }
    public DbSet<Client> Clients { get; set; }
    public DbSet<Operator> Operators { get; set; }
    public DbSet<Bank> Banks { get; set; }
    public DbSet<Role> Roles { get; set; }
    public DbSet<Transfer> Transfers { get; set; }
    public DbSet<BankAccount> BankAccounts { get; set; }
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
        
        var firstBank = new Bank
        {
            Id = 4,
            LegalName = "AlphaBank",
            BankIdentificationNumber = "ALFABY2X",
            LegalAddress = "Ул. Сурганова, 43-47, Минск, Республика Беларусь",
            Type = "ЗАО"
        };
        
        var secondBank = new Bank
        {
            Id = 5,
            LegalName = "Sberbank",
            BankIdentificationNumber = "BPSBBY2X",
            LegalAddress = "бульвар Мулявина, 6, Минск, Республика Беларусь",
            Type = "ОАО"
        };
        
        var thirdBank = new Bank
        {
            Id = 6,
            LegalName = "Tinkoff",
            BankIdentificationNumber = "44525974",
            LegalAddress = "1-й Волоколамс пр-д, 10, Москва, Российская Федерация",
            Type = "АО"
        };
        /*
        var managerRole = new Role { Name = "manager", Id = 3 };
        var companySpecialistRole = new Role { Name = "companySpecialist", Id = 4 };
        var adminRole = new Role { Name = "admin", Id = 5 };
        */
        var roles = new List<Role>();
        roles.Add(userRole);
        roles.Add(clientRole);
        roles.Add(operatorRole);
        
        var banks = new List<Bank>();
        banks.Add(firstBank);
        banks.Add(secondBank);
        banks.Add(thirdBank);
        
        modelBuilder.Entity<Role>().HasData(roles);
        //User adminUser = new User { Id = 1, Email = "admin@gmail.com", Password = "adminpassword", RoleId = adminRole.Id };
        modelBuilder.Entity<Bank>().HasData(banks);
        modelBuilder.Entity<BankAccount>().ToTable("BankAccounts");
        modelBuilder.Entity<Bank>().ToTable("Banks");
        modelBuilder.Entity<User>().ToTable("Users");
        modelBuilder.Entity<Client>().ToTable("Clients");
        modelBuilder.Entity<Operator>().ToTable("Operators");
        modelBuilder.Entity<Transfer>().ToTable("Transfers");
        base.OnModelCreating(modelBuilder);
    }
}