// src/Domain/Reports/GlobalBuildingReport.h
#pragma once

#include "MonthlyBuildingReport.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class GlobalBuildingReport {
private:
    std::string generationDate_;
    int totalBuildings_;
    int totalApartments_;
    int totalRented_;
    int totalVacant_;
    double totalIncome_;
    double totalExpenses_;
    double netProfit_;
    double overallOccupancyRate_;
    double averageIncomePerBuilding_;
    double averageExpensePerBuilding_;

    std::vector<MonthlyBuildingReport> reports_;

    void updateNetProfit() {
        netProfit_ = totalIncome_ - totalExpenses_;
    }

    void updateCalculatedFields() {
        totalVacant_ = totalApartments_ - totalRented_;
        overallOccupancyRate_ = totalApartments_ > 0 ? (static_cast<double>(totalRented_) / totalApartments_ * 100.0) : 0.0;
        averageIncomePerBuilding_ = totalBuildings_ > 0 ? (totalIncome_ / totalBuildings_) : 0.0;
        averageExpensePerBuilding_ = totalBuildings_ > 0 ? (totalExpenses_ / totalBuildings_) : 0.0;
        updateNetProfit();
    }

public:
    GlobalBuildingReport(const std::string& date = "Auto-generated");

    std::string getGenerationDate() const;
    int getTotalBuildings() const;
    int getTotalApartments() const;
    int getTotalRented() const;
    int getTotalVacant() const;
    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getNetProfit() const;
    double getOverallOccupancyRate() const;
    double getAverageIncomePerBuilding() const;
    double getAverageExpensePerBuilding() const;
    const std::vector<MonthlyBuildingReport>& getReports() const;

    void addReport(const MonthlyBuildingReport& report);

    std::string generateReport() const;
};