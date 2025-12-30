// src/Presentation/Cli/ReportsController.cpp
#include "ReportsController.h"
#include <iomanip>
#include <limits>

ReportsController::ReportsController(
    GenerateMonthlyBuildingReportUseCase& monthly,
    GenerateGlobalBuildingReportUseCase& global
)
    : monthlyUseCase(monthly), globalUseCase(global)
{
}

void ReportsController::showMenu() const {
    std::cout << "\n=== Reports Menu ===\n";
    std::cout << "1. Generate Monthly Building Report (US-23)\n";
    std::cout << "2. Generate Global Report (US-24)\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Your choice: ";
}

void ReportsController::handleMonthlyReport() {
    int buildingId, year, month;

    std::cout << "Enter Building ID: ";
    std::cin >> buildingId;

    std::cout << "Enter Year (e.g., 2025): ";
    std::cin >> year;

    std::cout << "Enter Month (1-12): ";
    std::cin >> month;

    // Clear input buffer for safety
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        auto report = monthlyUseCase.execute(buildingId, year, month);
        std::cout << "\n" << report.generateReport() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void ReportsController::handleGlobalReport() {
    try {
        auto report = globalUseCase.execute();
        std::cout << "\n" << report.generateReport() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}