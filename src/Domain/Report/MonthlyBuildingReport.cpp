// src/Domain/Reports/MonthlyBuildingReport.cpp
#include "MonthlyBuildingReport.h"

MonthlyBuildingReport::MonthlyBuildingReport(int buildingId, int year, int month)
    : buildingId_(buildingId), year_(year), month_(month),
    totalApartments_(0), rentedApartments_(0), vacantApartments_(0),
    totalRentIncome_(0.0), totalExpenses_(0.0), netProfit_(0.0),
    occupancyRate_(0.0), averageRentPerApartment_(0.0) {
    if (month < 1 || month > 12) throw std::invalid_argument("Month must be 1-12");
    if (year < 2000) throw std::invalid_argument("Year must be reasonable");
}

int MonthlyBuildingReport::getBuildingId() const { return buildingId_; }
int MonthlyBuildingReport::getYear() const { return year_; }
int MonthlyBuildingReport::getMonth() const { return month_; }
int MonthlyBuildingReport::getTotalApartments() const { return totalApartments_; }
int MonthlyBuildingReport::getRentedApartments() const { return rentedApartments_; }
int MonthlyBuildingReport::getVacantApartments() const { return vacantApartments_; }
double MonthlyBuildingReport::getTotalRentIncome() const { return totalRentIncome_; }
double MonthlyBuildingReport::getTotalExpenses() const { return totalExpenses_; }
double MonthlyBuildingReport::getNetProfit() const { return netProfit_; }
double MonthlyBuildingReport::getOccupancyRate() const { return occupancyRate_; }
double MonthlyBuildingReport::getAverageRentPerApartment() const { return averageRentPerApartment_; }

void MonthlyBuildingReport::setTotalApartments(int count) {
    if (count < 0) throw std::invalid_argument("Total apartments cannot be negative");
    totalApartments_ = count;
    updateCalculatedFields();
}

void MonthlyBuildingReport::setRentedApartments(int count) {
    if (count < 0 || count > totalApartments_) throw std::invalid_argument("Invalid rented count");
    rentedApartments_ = count;
    updateCalculatedFields();
}

void MonthlyBuildingReport::setTotalRentIncome(double income) {
    if (income < 0) throw std::invalid_argument("Rent income cannot be negative");
    totalRentIncome_ = income;
    updateCalculatedFields();
}

void MonthlyBuildingReport::setTotalExpenses(double expenses) {
    if (expenses < 0) throw std::invalid_argument("Expenses cannot be negative");
    totalExpenses_ = expenses;
    updateCalculatedFields();
}

std::string MonthlyBuildingReport::generateReport() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    oss << "\n============================================================\n";
    oss << "  Monthly Building Report - " << std::setw(2) << std::setfill('0') << month_
        << "/" << year_ << "\n";
    oss << "  Building ID: " << buildingId_ << "\n";
    oss << "============================================================\n";
    oss << "  OCCUPANCY STATISTICS\n";
    oss << "============================================================\n";
    oss << "  Total Apartments:        " << totalApartments_ << "\n";
    oss << "  Rented Apartments:       " << rentedApartments_ << "\n";
    oss << "  Vacant Apartments:       " << vacantApartments_ << "\n";
    oss << "  Occupancy Rate:          " << occupancyRate_ << "%\n";
    oss << "============================================================\n";
    oss << "  FINANCIAL SUMMARY\n";
    oss << "============================================================\n";
    oss << "  Total Rent Income:       $" << totalRentIncome_ << "\n";
    oss << "  Average Rent/Apartment:  $" << averageRentPerApartment_ << "\n";
    oss << "  Total Expenses:          $" << totalExpenses_ << "\n";
    oss << "  Net Profit/Loss:         $" << netProfit_ << "\n";
    oss << "============================================================\n";
    return oss.str();
}