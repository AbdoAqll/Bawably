// src/Domain/Report/RevenueStatistics.h
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct BuildingRevenue {
    int buildingId;
    double totalRevenue;
    int paidTenants;
    int totalTenants;
    double averageRevenuePerTenant;
    double collectionRate;

    BuildingRevenue(int id, double revenue, int paid, int total)
        : buildingId(id), totalRevenue(revenue), paidTenants(paid), totalTenants(total),
        averageRevenuePerTenant(paid > 0 ? (revenue / paid) : 0.0),
        collectionRate(total > 0 ? (static_cast<double>(paid) / total * 100.0) : 0.0) {
    }
};

class RevenueStatistics {
private:
    std::string periodDescription_;
    std::vector<BuildingRevenue> buildingData_;

    double totalRevenue_;
    double averageRevenuePerBuilding_;
    double highestBuildingRevenue_;
    double lowestBuildingRevenue_;
    int totalPaidTenants_;
    int totalTenants_;
    double overallCollectionRate_;

    void calculateStatistics() {
        totalRevenue_ = 0.0;
        totalPaidTenants_ = 0;
        totalTenants_ = 0;
        highestBuildingRevenue_ = 0.0;
        lowestBuildingRevenue_ = buildingData_.empty() ? 0.0 : buildingData_[0].totalRevenue;

        for (const auto& building : buildingData_) {
            totalRevenue_ += building.totalRevenue;
            totalPaidTenants_ += building.paidTenants;
            totalTenants_ += building.totalTenants;

            if (building.totalRevenue > highestBuildingRevenue_) {
                highestBuildingRevenue_ = building.totalRevenue;
            }
            if (building.totalRevenue < lowestBuildingRevenue_) {
                lowestBuildingRevenue_ = building.totalRevenue;
            }
        }

        averageRevenuePerBuilding_ = !buildingData_.empty() ?
            (totalRevenue_ / buildingData_.size()) : 0.0;
        overallCollectionRate_ = totalTenants_ > 0 ?
            (static_cast<double>(totalPaidTenants_) / totalTenants_ * 100.0) : 0.0;
    }

public:
    RevenueStatistics(const std::string& period)
        : periodDescription_(period), totalRevenue_(0.0), averageRevenuePerBuilding_(0.0),
        highestBuildingRevenue_(0.0), lowestBuildingRevenue_(0.0),
        totalPaidTenants_(0), totalTenants_(0), overallCollectionRate_(0.0) {
    }

    void addBuildingData(int buildingId, double revenue, int paidTenants, int totalTenants) {
        buildingData_.emplace_back(buildingId, revenue, paidTenants, totalTenants);
        calculateStatistics();
    }

    std::string getPeriodDescription() const { return periodDescription_; }
    double getTotalRevenue() const { return totalRevenue_; }
    double getAverageRevenuePerBuilding() const { return averageRevenuePerBuilding_; }
    double getHighestBuildingRevenue() const { return highestBuildingRevenue_; }
    double getLowestBuildingRevenue() const { return lowestBuildingRevenue_; }
    double getOverallCollectionRate() const { return overallCollectionRate_; }
    const std::vector<BuildingRevenue>& getBuildingData() const { return buildingData_; }

    std::string generateReport() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);

        oss << "\n==================================================================\n";
        oss << "  REVENUE ANALYSIS REPORT\n";
        oss << "  " << periodDescription_ << "\n";
        oss << "==================================================================\n";
        oss << "  REVENUE SUMMARY\n";
        oss << "==================================================================\n";
        oss << "  Total Revenue:              $" << totalRevenue_ << "\n";
        oss << "  Average Revenue/Building:   $" << averageRevenuePerBuilding_ << "\n";
        oss << "  Highest Building Revenue:   $" << highestBuildingRevenue_ << "\n";
        oss << "  Lowest Building Revenue:    $" << lowestBuildingRevenue_ << "\n";
        oss << "==================================================================\n";
        oss << "  COLLECTION METRICS\n";
        oss << "==================================================================\n";
        oss << "  Total Tenants:              " << totalTenants_ << "\n";
        oss << "  Paid Tenants:               " << totalPaidTenants_ << "\n";
        oss << "  Collection Rate:            " << overallCollectionRate_ << "%\n";

        if (!buildingData_.empty()) {
            oss << "==================================================================\n";
            oss << "  TOP PERFORMING BUILDINGS\n";
            oss << "==================================================================\n";

            auto sortedBuildings = buildingData_;
            std::sort(sortedBuildings.begin(), sortedBuildings.end(),
                [](const BuildingRevenue& a, const BuildingRevenue& b) {
                    return a.totalRevenue > b.totalRevenue;
                });

            int count = (std::min)(5, static_cast<int>(sortedBuildings.size()));
            for (int i = 0; i < count; ++i) {
                const auto& building = sortedBuildings[i];
                oss << "  #" << (i + 1) << " Building " << building.buildingId
                    << " - Revenue: $" << building.totalRevenue
                    << " (" << building.collectionRate << "%)\n";
            }
        }

        oss << "==================================================================\n";
        return oss.str();
    }
};
