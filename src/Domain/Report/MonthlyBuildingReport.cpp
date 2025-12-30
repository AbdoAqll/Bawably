// src/Domain/Reports/MonthlyBuildingReport.cpp
#include "MonthlyBuildingReport.h"

MonthlyBuildingReport::MonthlyBuildingReport(int buildingId, int year, int month)
    : buildingId_(buildingId), year_(year), month_(month),
      totalApartments_(0), rentedApartments_(0),
      totalRentIncome_(0.0), totalExpenses_(0.0), netProfit_(0.0)
{
    if (month < 1 || month > 12) throw std::invalid_argument("Month must be 1-12");
    if (year < 2000) throw std::invalid_argument("Year must be reasonable");
}

int MonthlyBuildingReport::getBuildingId() const { return buildingId_; }
int MonthlyBuildingReport::getYear() const { return year_; }
int MonthlyBuildingReport::getMonth() const { return month_; }
int MonthlyBuildingReport::getTotalApartments() const { return totalApartments_; }
int MonthlyBuildingReport::getRentedApartments() const { return rentedApartments_; }
double MonthlyBuildingReport::getTotalRentIncome() const { return totalRentIncome_; }
double MonthlyBuildingReport::getTotalExpenses() const { return totalExpenses_; }
double MonthlyBuildingReport::getNetProfit() const { return netProfit_; }

void MonthlyBuildingReport::setTotalApartments(int count) {
    if (count < 0) throw std::invalid_argument("Total apartments cannot be negative");
    totalApartments_ = count;
}

void MonthlyBuildingReport::setRentedApartments(int count) {
    if (count < 0 || count > totalApartments_) throw std::invalid_argument("Invalid rented count");
    rentedApartments_ = count;
}

void MonthlyBuildingReport::setTotalRentIncome(double income) {
    if (income < 0) throw std::invalid_argument("Rent income cannot be negative");
    totalRentIncome_ = income;
    updateNetProfit();
}

void MonthlyBuildingReport::setTotalExpenses(double expenses) {
    if (expenses < 0) throw std::invalid_argument("Expenses cannot be negative");
    totalExpenses_ = expenses;
    updateNetProfit();
}

std::string MonthlyBuildingReport::generateReport() const {
    std::ostringstream oss;
    oss << "Monthly Report for Building " << buildingId_ << " - " << month_ << "/" << year_ << "\n";
    oss << "----------------------------------------\n";
    oss << "Total Apartments: " << totalApartments_ << "\n";
    oss << "Rented Apartments: " << rentedApartments_ << "\n";
    oss << "Occupancy Rate: "
        << (totalApartments_ > 0 ? (static_cast<double>(rentedApartments_) / totalApartments_ * 100) : 0) << "%\n\n";
    oss << "Total Rent Income: $" << std::fixed << std::setprecision(2) << totalRentIncome_ << "\n";
    oss << "Total Expenses: $" << std::fixed << std::setprecision(2) << totalExpenses_ << "\n";
    oss << "Net Profit: $" << std::fixed << std::setprecision(2) << netProfit_ << "\n";
    return oss.str();
}