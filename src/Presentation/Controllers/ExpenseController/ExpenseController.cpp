// src/Presentation/Cli/ExpenseController.cpp
#include "ExpenseController.h"
#include <iomanip>
#include <limits>

ExpenseController::ExpenseController(
    CreateExpenseUseCase& create,
    GetExpensesByBuildingUseCase& list,
    GetTotalExpensesByBuildingAndMonthUseCase& total
)
    : createUseCase(create), listUseCase(list), totalUseCase(total)
{
}

void ExpenseController::showMenu() const
{
    std::cout << "\n=== Expense management system ===\n";
    std::cout << "1. Add Expense \n";
    std::cout << "2.Get Expense By Building\n";
    std::cout << "3.Get By Building And Month\n";
    std::cout << "0. Exit\n";
    std::cout << "Your Choice: ";
}

void ExpenseController::handleAddExpense()
{
    int buildingId, cat;
    double amount;
    std::string date, desc;

    std::cout << "; Building Number: "; std::cin >> buildingId;
    std::cout << "التصنيف (0=Electricity, 1=Cleaning, 2=Plumbing, 3=Security, 4=Other): "; std::cin >> cat;
    std::cout << "Amount: "; std::cin >> amount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Date (YYYY-MM-DD): "; std::getline(std::cin, date);
    std::cout << "Description: "; std::getline(std::cin, desc);

    try {
        createUseCase.execute(buildingId, static_cast<ExpenseCategory>(cat), amount, date, desc);
        std::cout << "Expense Added Successfully ✓\n";
    } catch (const std::exception& e) {
        std::cout << "Wrong: " << e.what() << "\n";
    }
}

void ExpenseController::handleViewExpenses()
{
    int buildingId;
    std::cout << "Building Number: "; std::cin >> buildingId;

    auto expenses = listUseCase.execute(buildingId);

    if (expenses.empty()) {
        std::cout << "There is no Expense for this building \n";
        return;
    }

    std::cout << "\nBuilding Expense " << buildingId << ":\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(12) << "Amount"
              << std::setw(12) << "Date"
              << "Description\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& e : expenses) {
        std::cout << std::left << std::setw(10) << e.getExpenseId()
                  << std::setw(12) << e.getAmount()
                  << std::setw(12) << e.getExpenseDate()
                  << e.getDescription() << "\n";
    }
}

void ExpenseController::handleCalculateTotal()
{
    int buildingId, year, month;
    std::cout << "Building Expense: "; std::cin >> buildingId;
    std::cout << "Year: "; std::cin >> year;
    std::cout << "Month (1-12): "; std::cin >> month;

    double total = totalUseCase.execute(buildingId, year, month);
    std::cout << "Total Expense " << buildingId
              << " in " << month << "/" << year << ": " << total << " pound\n";
}