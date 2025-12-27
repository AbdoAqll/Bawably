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
    std::cout << "\n=== نظام إدارة المصروفات ===\n";
    std::cout << "1. إضافة مصروف جديد\n";
    std::cout << "2. عرض مصروفات مبنى\n";
    std::cout << "3. حساب إجمالي مصروفات مبنى في شهر\n";
    std::cout << "0. خروج\n";
    std::cout << "اختيارك: ";
}

void ExpenseController::handleAddExpense()
{
    int buildingId, cat;
    double amount;
    std::string date, desc;

    std::cout << "رقم المبنى: "; std::cin >> buildingId;
    std::cout << "التصنيف (0=Electricity, 1=Cleaning, 2=Plumbing, 3=Security, 4=Other): "; std::cin >> cat;
    std::cout << "المبلغ: "; std::cin >> amount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "التاريخ (YYYY-MM-DD): "; std::getline(std::cin, date);
    std::cout << "الوصف: "; std::getline(std::cin, desc);

    try {
        createUseCase.execute(buildingId, static_cast<ExpenseCategory>(cat), amount, date, desc);
        std::cout << "تم إضافة المصروف بنجاح ✓\n";
    } catch (const std::exception& e) {
        std::cout << "خطأ: " << e.what() << "\n";
    }
}

void ExpenseController::handleViewExpenses()
{
    int buildingId;
    std::cout << "رقم المبنى: "; std::cin >> buildingId;

    auto expenses = listUseCase.execute(buildingId);

    if (expenses.empty()) {
        std::cout << "لا يوجد مصروفات لهذا المبنى\n";
        return;
    }

    std::cout << "\nمصروفات المبنى " << buildingId << ":\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(12) << "المبلغ"
              << std::setw(12) << "التاريخ"
              << "الوصف\n";
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
    std::cout << "رقم المبنى: "; std::cin >> buildingId;
    std::cout << "السنة: "; std::cin >> year;
    std::cout << "الشهر (1-12): "; std::cin >> month;

    double total = totalUseCase.execute(buildingId, year, month);
    std::cout << "إجمالي المصروفات للمبنى " << buildingId
              << " في " << month << "/" << year << ": " << total << " جنيه\n";
}