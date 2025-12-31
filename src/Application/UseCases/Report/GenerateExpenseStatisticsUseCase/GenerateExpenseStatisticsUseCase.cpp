// src/Application/UseCases/Report/GenerateExpenseStatisticsUseCase/GenerateExpenseStatisticsUseCase.cpp
#include "GenerateExpenseStatisticsUseCase.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"
#include "Domain/Report/Exceptions/ReportGenerationFailedException.h"
#include <sstream>
#include <map>

// Helper function to convert ExpenseCategory enum to string
std::string expenseCategoryToString(ExpenseCategory category) {
    switch (category) {
    case ExpenseCategory::Electricity: return "Electricity";
    case ExpenseCategory::Cleaning: return "Cleaning";
    case ExpenseCategory::Plumbing: return "Plumbing";
    case ExpenseCategory::Security: return "Security";
    case ExpenseCategory::Other: return "Other";
    default: return "Unknown";
    }
}

GenerateExpenseStatisticsUseCase::GenerateExpenseStatisticsUseCase(
    shared_ptr<IBuildingRepository> buildingRepo,
    shared_ptr<IExpenseRepository> expenseRepo
)
    : buildingRepo_(buildingRepo),
    expenseRepo_(expenseRepo) {
    UseCaseName = "GenerateExpenseStatistics";
}

any GenerateExpenseStatisticsUseCase::execute(const any& params) {
    auto p = any_cast<GenerateExpenseStatsParams>(params);
    return execute(p.year, p.month);
}

ExpenseStatistics GenerateExpenseStatisticsUseCase::execute(int year, int month) {
    // Validate month (1-12)
    if (month < 1 || month > 12) {
        throw InvalidMonthException(month);
    }

    // Validate year
    if (year < 2000 || year > 2100) {
        throw InvalidYearException(year);
    }

    std::ostringstream period;
    period << "Expense Analysis for " << month << "/" << year;

    ExpenseStatistics statistics(period.str());

    auto buildings = buildingRepo_->getAll();

    if (buildings.empty()) {
        throw ReportGenerationFailedException("No buildings found in the system");
    }

    std::map<std::string, double> categoryTotals;

    for (const auto& building : buildings) {
        int buildingId = building.getId();
        auto expenses = expenseRepo_->getByBuildingAndMonth(buildingId, year, month);

        double totalExpenses = 0.0;
        for (const auto& expense : expenses) {
            totalExpenses += expense.getAmount();

            // Aggregate by category - convert enum to string
            std::string category = expenseCategoryToString(expense.getCategory());
            categoryTotals[category] += expense.getAmount();
        }

        statistics.addBuildingData(buildingId, totalExpenses, expenses.size());
    }

    // Add category breakdowns
    for (const auto& [category, amount] : categoryTotals) {
        statistics.addExpenseByCategory(category, amount);
    }

    return statistics;
}
