// src/Domain/Reports/MonthlyBuildingReport.h
#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class MonthlyBuildingReport {
private:
    int buildingId_;
    int year_;
    int month_;

    int totalApartments_;
    int rentedApartments_;
    double totalRentIncome_;
    double totalExpenses_;
    double netProfit_;

    void updateNetProfit() {
        netProfit_ = totalRentIncome_ - totalExpenses_;
    }

public:
    MonthlyBuildingReport(int buildingId, int year, int month);

    int getBuildingId() const;
    int getYear() const;
    int getMonth() const;
    int getTotalApartments() const;
    int getRentedApartments() const;
    double getTotalRentIncome() const;
    double getTotalExpenses() const;
    double getNetProfit() const;

    void setTotalApartments(int count);
    void setRentedApartments(int count);
    void setTotalRentIncome(double income);
    void setTotalExpenses(double expenses);

    std::string generateReport() const;
};