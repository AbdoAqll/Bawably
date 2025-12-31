// src/Domain/Reports/GlobalBuildingReport.cpp
#include "GlobalBuildingReport.h"

GlobalBuildingReport::GlobalBuildingReport(const std::string& date)
    : generationDate_(date), totalBuildings_(0), totalApartments_(0), totalRented_(0), totalVacant_(0),
    totalIncome_(0.0), totalExpenses_(0.0), netProfit_(0.0),
    overallOccupancyRate_(0.0), averageIncomePerBuilding_(0.0), averageExpensePerBuilding_(0.0) {
}

std::string GlobalBuildingReport::getGenerationDate() const { return generationDate_; }
int GlobalBuildingReport::getTotalBuildings() const { return totalBuildings_; }
int GlobalBuildingReport::getTotalApartments() const { return totalApartments_; }
int GlobalBuildingReport::getTotalRented() const { return totalRented_; }
int GlobalBuildingReport::getTotalVacant() const { return totalVacant_; }
double GlobalBuildingReport::getTotalIncome() const { return totalIncome_; }
double GlobalBuildingReport::getTotalExpenses() const { return totalExpenses_; }
double GlobalBuildingReport::getNetProfit() const { return netProfit_; }
double GlobalBuildingReport::getOverallOccupancyRate() const { return overallOccupancyRate_; }
double GlobalBuildingReport::getAverageIncomePerBuilding() const { return averageIncomePerBuilding_; }
double GlobalBuildingReport::getAverageExpensePerBuilding() const { return averageExpensePerBuilding_; }
const std::vector<MonthlyBuildingReport>& GlobalBuildingReport::getReports() const { return reports_; }

void GlobalBuildingReport::addReport(const MonthlyBuildingReport& report) {
    reports_.push_back(report);
    totalBuildings_++;
    totalApartments_ += report.getTotalApartments();
    totalRented_ += report.getRentedApartments();
    totalIncome_ += report.getTotalRentIncome();
    totalExpenses_ += report.getTotalExpenses();
    updateCalculatedFields();
}

std::string GlobalBuildingReport::generateReport() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    oss << "\n======================================================================\n";
    oss << "  GLOBAL PROPERTY REPORT\n";
    oss << "  " << generationDate_ << "\n";
    oss << "======================================================================\n";
    oss << "  PORTFOLIO OVERVIEW\n";
    oss << "======================================================================\n";
    oss << "  Total Buildings:              " << totalBuildings_ << "\n";
    oss << "  Total Apartments:             " << totalApartments_ << "\n";
    oss << "  Total Rented:                 " << totalRented_ << "\n";
    oss << "  Total Vacant:                 " << totalVacant_ << "\n";
    oss << "  Overall Occupancy Rate:       " << overallOccupancyRate_ << "%\n";
    oss << "======================================================================\n";
    oss << "  FINANCIAL PERFORMANCE\n";
    oss << "======================================================================\n";
    oss << "  Total Rent Income:            $" << totalIncome_ << "\n";
    oss << "  Total Expenses:               $" << totalExpenses_ << "\n";
    oss << "  Net Profit/Loss:              $" << netProfit_ << "\n";
    oss << "  Avg Income/Building:          $" << averageIncomePerBuilding_ << "\n";
    oss << "  Avg Expense/Building:         $" << averageExpensePerBuilding_ << "\n";

    if (!reports_.empty()) {
        oss << "======================================================================\n";
        oss << "  BUILDING BREAKDOWN (" << reports_.size() << " buildings)\n";
        oss << "======================================================================\n";
        for (const auto& report : reports_) {
            oss << "  Building " << report.getBuildingId()
                << " | Occ: " << report.getOccupancyRate() << "% | Profit: $"
                << report.getNetProfit() << "\n";
        }
    }

    oss << "======================================================================\n";
    return oss.str();
}