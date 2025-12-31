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
    int vacantApartments_;
    double totalRentIncome_;
    double totalExpenses_;
    double netProfit_;
    double occupancyRate_;
    double averageRentPerApartment_;

    void updateNetProfit() {
        netProfit_ = totalRentIncome_ - totalExpenses_;
    }

    void updateCalculatedFields() {
        vacantApartments_ = totalApartments_ - rentedApartments_;
        occupancyRate_ = totalApartments_ > 0 ? (static_cast<double>(rentedApartments_) / totalApartments_ * 100.0) : 0.0;
        averageRentPerApartment_ = rentedApartments_ > 0 ? (totalRentIncome_ / rentedApartments_) : 0.0;
        updateNetProfit();
    }

public:
    MonthlyBuildingReport(int buildingId, int year, int month);

    int getBuildingId() const;
    int getYear() const;
    int getMonth() const;
    int getTotalApartments() const;
    int getRentedApartments() const;
    int getVacantApartments() const;
    double getTotalRentIncome() const;
    double getTotalExpenses() const;
    double getNetProfit() const;
    double getOccupancyRate() const;
    double getAverageRentPerApartment() const;

    void setTotalApartments(int count);
    void setRentedApartments(int count);
    void setTotalRentIncome(double income);
    void setTotalExpenses(double expenses);

    std::string generateReport() const;
};