// src/Domain/Reports/GlobalBuildingReport.cpp
#include "GlobalBuildingReport.h"

GlobalBuildingReport::GlobalBuildingReport(const std::string& date)
    : generationDate_(date), totalBuildings_(0), totalApartments_(0), totalRented_(0),
      totalIncome_(0.0), totalExpenses_(0.0), netProfit_(0.0) {}

std::string GlobalBuildingReport::getGenerationDate() const { return generationDate_; }
int GlobalBuildingReport::getTotalBuildings() const { return totalBuildings_; }
int GlobalBuildingReport::getTotalApartments() const { return totalApartments_; }
int GlobalBuildingReport::getTotalRented() const { return totalRented_; }
double GlobalBuildingReport::getTotalIncome() const { return totalIncome_; }
double GlobalBuildingReport::getTotalExpenses() const { return totalExpenses_; }
double GlobalBuildingReport::getNetProfit() const { return netProfit_; }
const std::vector<MonthlyBuildingReport>& GlobalBuildingReport::getReports() const { return reports_; }

void GlobalBuildingReport::addReport(const MonthlyBuildingReport& report) {
    reports_.push_back(report);
    totalBuildings_++;
    totalApartments_ += report.getTotalApartments();
    totalRented_ += report.getRentedApartments();
    totalIncome_ += report.getTotalRentIncome();
    totalExpenses_ += report.getTotalExpenses();
    updateNetProfit();
}

std::string GlobalBuildingReport::generateReport() const {
    std::ostringstream oss;
    oss << "Global Property Report\n";
    oss << "======================\n";
    oss << "Generated: " << generationDate_ << "\n\n";

    oss << "Portfolio Summary:\n";
    oss << "  Total Buildings: " << totalBuildings_ << "\n";
    oss << "  Total Apartments: " << totalApartments_ << "\n";
    oss << "  Total Rented Apartments: " << totalRented_ << "\n";
    oss << "  Occupancy Rate: "
        << (totalApartments_ > 0 ? (static_cast<double>(totalRented_) / totalApartments_ * 100) : 0) << "%\n\n";

    oss << "Financial Summary:\n";
    oss << "  Total Rent Income: $" << std::fixed << std::setprecision(2) << totalIncome_ << "\n";
    oss << "  Total Expenses: $" << std::fixed << std::setprecision(2) << totalExpenses_ << "\n";
    oss << "  Net Profit: $" << std::fixed << std::setprecision(2) << netProfit_ << "\n";

    return oss.str();
}