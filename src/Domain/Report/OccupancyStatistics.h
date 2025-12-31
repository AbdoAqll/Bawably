// src/Domain/Report/OccupancyStatistics.h
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

struct BuildingOccupancy {
    int buildingId;
    int totalApartments;
    int occupiedApartments;
    int vacantApartments;
    double occupancyRate;

    BuildingOccupancy(int id, int total, int occupied)
        : buildingId(id), totalApartments(total), occupiedApartments(occupied),
        vacantApartments(total - occupied),
        occupancyRate(total > 0 ? (static_cast<double>(occupied) / total * 100.0) : 0.0) {
    }
};

class OccupancyStatistics {
private:
    std::string periodDescription_;
    std::vector<BuildingOccupancy> buildingData_;

    int totalApartments_;
    int totalOccupied_;
    int totalVacant_;
    double overallOccupancyRate_;
    int buildingsFullyOccupied_;
    int buildingsPartiallyOccupied_;
    int buildingsEmpty_;

    void calculateStatistics() {
        totalApartments_ = 0;
        totalOccupied_ = 0;
        totalVacant_ = 0;
        buildingsFullyOccupied_ = 0;
        buildingsPartiallyOccupied_ = 0;
        buildingsEmpty_ = 0;

        for (const auto& building : buildingData_) {
            totalApartments_ += building.totalApartments;
            totalOccupied_ += building.occupiedApartments;
            totalVacant_ += building.vacantApartments;

            if (building.occupiedApartments == building.totalApartments && building.totalApartments > 0) {
                buildingsFullyOccupied_++;
            }
            else if (building.occupiedApartments > 0) {
                buildingsPartiallyOccupied_++;
            }
            else {
                buildingsEmpty_++;
            }
        }

        overallOccupancyRate_ = totalApartments_ > 0 ?
            (static_cast<double>(totalOccupied_) / totalApartments_ * 100.0) : 0.0;
    }

public:
    OccupancyStatistics(const std::string& period)
        : periodDescription_(period), totalApartments_(0), totalOccupied_(0),
        totalVacant_(0), overallOccupancyRate_(0.0), buildingsFullyOccupied_(0),
        buildingsPartiallyOccupied_(0), buildingsEmpty_(0) {
    }

    void addBuildingData(int buildingId, int totalApartments, int occupiedApartments) {
        buildingData_.emplace_back(buildingId, totalApartments, occupiedApartments);
        calculateStatistics();
    }

    std::string getPeriodDescription() const { return periodDescription_; }
    int getTotalApartments() const { return totalApartments_; }
    int getTotalOccupied() const { return totalOccupied_; }
    int getTotalVacant() const { return totalVacant_; }
    double getOverallOccupancyRate() const { return overallOccupancyRate_; }
    int getBuildingsFullyOccupied() const { return buildingsFullyOccupied_; }
    int getBuildingsPartiallyOccupied() const { return buildingsPartiallyOccupied_; }
    int getBuildingsEmpty() const { return buildingsEmpty_; }
    const std::vector<BuildingOccupancy>& getBuildingData() const { return buildingData_; }

    std::string generateReport() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);

        oss << "\n==================================================================\n";
        oss << "  OCCUPANCY STATISTICS REPORT\n";
        oss << "  " << periodDescription_ << "\n";
        oss << "==================================================================\n";
        oss << "  OVERALL STATISTICS\n";
        oss << "==================================================================\n";
        oss << "  Total Apartments:           " << totalApartments_ << "\n";
        oss << "  Occupied Apartments:        " << totalOccupied_ << "\n";
        oss << "  Vacant Apartments:          " << totalVacant_ << "\n";
        oss << "  Overall Occupancy Rate:     " << overallOccupancyRate_ << "%\n";
        oss << "==================================================================\n";
        oss << "  BUILDING STATUS\n";
        oss << "==================================================================\n";
        oss << "  Fully Occupied Buildings:   " << buildingsFullyOccupied_ << "\n";
        oss << "  Partially Occupied:         " << buildingsPartiallyOccupied_ << "\n";
        oss << "  Empty Buildings:            " << buildingsEmpty_ << "\n";

        if (!buildingData_.empty()) {
            oss << "==================================================================\n";
            oss << "  BUILDING-BY-BUILDING BREAKDOWN\n";
            oss << "==================================================================\n";
            oss << "  Building | Total | Occupied | Vacant | Rate\n";
            oss << "==================================================================\n";
            for (const auto& building : buildingData_) {
                oss << "  " << std::setw(8) << std::left << building.buildingId
                    << "| " << std::setw(5) << std::right << building.totalApartments
                    << " | " << std::setw(8) << building.occupiedApartments
                    << " | " << std::setw(6) << building.vacantApartments
                    << " | " << std::setw(6) << building.occupancyRate << "%\n";
            }
        }

        oss << "==================================================================\n";
        return oss.str();
    }
};
