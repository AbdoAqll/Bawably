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
    double totalIncome_;
    double totalExpenses_;
    double netProfit_;

    std::vector<MonthlyBuildingReport> reports_;

    void updateNetProfit() {
        netProfit_ = totalIncome_ - totalExpenses_;
    }

public:
    GlobalBuildingReport(const std::string& date = "Auto-generated");

    std::string getGenerationDate() const;
    int getTotalBuildings() const;
    int getTotalApartments() const;
    int getTotalRented() const;
    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getNetProfit() const;
    const std::vector<MonthlyBuildingReport>& getReports() const;

    void addReport(const MonthlyBuildingReport& report);

    std::string generateReport() const;
};