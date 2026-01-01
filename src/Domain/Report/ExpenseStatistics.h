// src/Domain/Report/ExpenseStatistics.h
#pragma once

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct BuildingExpense {
    int buildingId;
    double totalExpenses;
    int expenseCount;
    double averageExpenseAmount;

    BuildingExpense(int id, double total, int count)
        : buildingId(id), totalExpenses(total), expenseCount(count),
        averageExpenseAmount(count > 0 ? (total / count) : 0.0) {
    }
};

class ExpenseStatistics {
private:
    std::string periodDescription_;
    std::vector<BuildingExpense> buildingData_;
    std::map<std::string, double> expensesByCategory_;

    double totalExpenses_;
    double averageExpensePerBuilding_;
    double highestBuildingExpense_;
    double lowestBuildingExpense_;
    int totalExpenseCount_;

    void calculateStatistics() {
        totalExpenses_ = 0.0;
        totalExpenseCount_ = 0;
        highestBuildingExpense_ = 0.0;
        lowestBuildingExpense_ = buildingData_.empty() ? 0.0 : buildingData_[0].totalExpenses;

        for (const auto& building : buildingData_) {
            totalExpenses_ += building.totalExpenses;
            totalExpenseCount_ += building.expenseCount;

            if (building.totalExpenses > highestBuildingExpense_) {
                highestBuildingExpense_ = building.totalExpenses;
            }
            if (building.totalExpenses < lowestBuildingExpense_) {
                lowestBuildingExpense_ = building.totalExpenses;
            }
        }

        averageExpensePerBuilding_ = !buildingData_.empty() ?
            (totalExpenses_ / buildingData_.size()) : 0.0;
    }

public:
    ExpenseStatistics(const std::string& period)
        : periodDescription_(period), totalExpenses_(0.0), averageExpensePerBuilding_(0.0),
        highestBuildingExpense_(0.0), lowestBuildingExpense_(0.0), totalExpenseCount_(0) {
    }

    void addBuildingData(int buildingId, double expenses, int count) {
        buildingData_.emplace_back(buildingId, expenses, count);
        calculateStatistics();
    }

    void addExpenseByCategory(const std::string& category, double amount) {
        expensesByCategory_[category] += amount;
    }

    std::string getPeriodDescription() const { return periodDescription_; }
    double getTotalExpenses() const { return totalExpenses_; }
    double getAverageExpensePerBuilding() const { return averageExpensePerBuilding_; }
    double getHighestBuildingExpense() const { return highestBuildingExpense_; }
    double getLowestBuildingExpense() const { return lowestBuildingExpense_; }
    int getTotalExpenseCount() const { return totalExpenseCount_; }
    const std::vector<BuildingExpense>& getBuildingData() const { return buildingData_; }
    const std::map<std::string, double>& getExpensesByCategory() const { return expensesByCategory_; }

    std::string generateReport() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);

        oss << "\n==================================================================\n";
        oss << "  EXPENSE ANALYSIS REPORT\n";
        oss << "  " << periodDescription_ << "\n";
        oss << "==================================================================\n";
        oss << "  EXPENSE SUMMARY\n";
        oss << "==================================================================\n";
        oss << "  Total Expenses:             $" << totalExpenses_ << "\n";
        oss << "  Average Expense/Building:   $" << averageExpensePerBuilding_ << "\n";
        oss << "  Highest Building Expense:   $" << highestBuildingExpense_ << "\n";
        oss << "  Lowest Building Expense:    $" << lowestBuildingExpense_ << "\n";
        oss << "  Total Number of Expenses:   " << totalExpenseCount_ << "\n";

        if (!expensesByCategory_.empty()) {
            oss << "==================================================================\n";
            oss << "  EXPENSES BY CATEGORY\n";
            oss << "==================================================================\n";

            std::vector<std::pair<std::string, double>> sortedCategories(
                expensesByCategory_.begin(), expensesByCategory_.end());
            std::sort(sortedCategories.begin(), sortedCategories.end(),
                [](const auto& a, const auto& b) { return a.second > b.second; });

            for (const auto& [category, amount] : sortedCategories) {
                double percentage = totalExpenses_ > 0 ? (amount / totalExpenses_ * 100.0) : 0.0;
                oss << "  " << std::setw(25) << std::left << category
                    << " $" << std::setw(12) << std::right << amount
                    << " (" << std::setw(5) << percentage << "%)\n";
            }
        }

        if (!buildingData_.empty()) {
            oss << "==================================================================\n";
            oss << "  HIGHEST EXPENSE BUILDINGS\n";
            oss << "==================================================================\n";

            auto sortedBuildings = buildingData_;
            std::sort(sortedBuildings.begin(), sortedBuildings.end(),
                [](const BuildingExpense& a, const BuildingExpense& b) {
                    return a.totalExpenses > b.totalExpenses;
                });

            int count = (std::min)(5, static_cast<int>(sortedBuildings.size()));
            for (int i = 0; i < count; ++i) {
                const auto& building = sortedBuildings[i];
                oss << "  #" << (i + 1) << " Building " << building.buildingId
                    << " - Expenses: $" << building.totalExpenses
                    << " (" << building.expenseCount << " items)\n";
            }
        }

        oss << "==================================================================\n";
        return oss.str();
    }
};
