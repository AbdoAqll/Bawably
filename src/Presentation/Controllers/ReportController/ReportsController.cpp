// src/Presentation/Cli/ReportsController.cpp
#include "ReportsController.h"
#include <iomanip>
#include <any>

using namespace std;

ReportsController::ReportsController(
    vector<shared_ptr<IUseCase>>& useCases
) {
    for (auto useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
}

void ReportsController::execute() {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Reports & Statistics Management", {
            "1. Monthly Building Report",
            "2. Global Report",
            "3. Occupancy Statistics",
            "4. Revenue Analysis",
            "5. Expense Analysis",
            "0. Back to Main Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            handleMonthlyReport();
            break;
        case 1:
            handleGlobalReport();
            break;
        case 2:
            handleOccupancyStatistics();
            break;
        case 3:
            handleRevenueStatistics();
            break;
        case 4:
            handleExpenseStatistics();
            break;
        case 5:
        case -1:
            running = false;
            break;
        }
    }
}

void ReportsController::handleMonthlyReport() {
    ConsoleUtils::clearScreen();

    InputForm form("Monthly Building Report");
    form.addNumberField("buildingId", "Building ID", true)
        .addNumberField("year", "Year (e.g., 2025)", true)
        .addNumberField("month", "Month (1-12)", true);

    FormResult result = form.show();

    if (result.submitted) {
        try {
            GenerateMonthlyReportParams params;
            params.buildingId = result.getInt("buildingId");
            params.year = result.getInt("year");
            params.month = result.getInt("month");

            auto execResult = useCases["GenerateMonthlyBuildingReport"]->execute(params);
            auto report = any_cast<MonthlyBuildingReport>(execResult);

            displayMonthlyReport(report);
        }
        catch (const DomainException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Unexpected error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
}

void ReportsController::handleGlobalReport() {
    ConsoleUtils::clearScreen();

    InputForm form("Global Portfolio Report");
    form.addNumberField("year", "End Year (e.g., 2025)", true)
        .addNumberField("month", "End Month (1-12)", true);

    // Validate month
    form.setValidator("month", [](const string& val) {
        try {
            int month = stoi(val);
            return month >= 1 && month <= 12;
        }
        catch (...) {
            return false;
        }
        }, "Month must be between 1 and 12");

    // Validate year
    form.setValidator("year", [](const string& val) {
        try {
            int year = stoi(val);
            return year >= 2000 && year <= 2100;
        }
        catch (...) {
            return false;
        }
        }, "Year must be between 2000 and 2100");

    FormResult result = form.show();

    if (result.submitted) {
        try {
            GenerateGlobalReportParams params;
            params.year = result.getInt("year");
            params.month = result.getInt("month");

            auto execResult = useCases["GenerateGlobalBuildingReport"]->execute(params);
            auto report = any_cast<GlobalBuildingReport>(execResult);

            displayGlobalReport(report);
        }
        catch (const DomainException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Unexpected error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
}

void ReportsController::handleOccupancyStatistics() {
    ConsoleUtils::clearScreen();

    InputForm form("Occupancy Statistics");
    form.addNumberField("year", "Year (e.g., 2025)", true)
        .addNumberField("month", "Month (1-12)", true);

    // Validate month
    form.setValidator("month", [](const string& val) {
        try {
            int month = stoi(val);
            return month >= 1 && month <= 12;
        }
        catch (...) {
            return false;
        }
        }, "Month must be between 1 and 12");

    // Validate year
    form.setValidator("year", [](const string& val) {
        try {
            int year = stoi(val);
            return year >= 2000 && year <= 2100;
        }
        catch (...) {
            return false;
        }
        }, "Year must be between 2000 and 2100");

    FormResult result = form.show();

    if (result.submitted) {
        try {
            GenerateOccupancyStatsParams params;
            params.year = result.getInt("year");
            params.month = result.getInt("month");

            auto execResult = useCases["GenerateOccupancyStatistics"]->execute(params);
            auto statistics = any_cast<OccupancyStatistics>(execResult);

            displayOccupancyStatistics(statistics);
        }
        catch (const DomainException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Unexpected error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
}

void ReportsController::handleRevenueStatistics() {
    ConsoleUtils::clearScreen();

    InputForm form("Revenue Analysis");
    form.addNumberField("year", "Year (e.g., 2025)", true)
        .addNumberField("month", "Month (1-12)", true);

    // Validate month
    form.setValidator("month", [](const string& val) {
        try {
            int month = stoi(val);
            return month >= 1 && month <= 12;
        }
        catch (...) {
            return false;
        }
        }, "Month must be between 1 and 12");

    // Validate year
    form.setValidator("year", [](const string& val) {
        try {
            int year = stoi(val);
            return year >= 2000 && year <= 2100;
        }
        catch (...) {
            return false;
        }
        }, "Year must be between 2000 and 2100");

    FormResult result = form.show();

    if (result.submitted) {
        try {
            GenerateRevenueStatsParams params;
            params.year = result.getInt("year");
            params.month = result.getInt("month");

            auto execResult = useCases["GenerateRevenueStatistics"]->execute(params);
            auto statistics = any_cast<RevenueStatistics>(execResult);

            displayRevenueStatistics(statistics);
        }
        catch (const DomainException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Unexpected error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
}

void ReportsController::handleExpenseStatistics() {
    ConsoleUtils::clearScreen();

    InputForm form("Expense Analysis");
    form.addNumberField("year", "Year (e.g., 2025)", true)
        .addNumberField("month", "Month (1-12)", true);

    // Validate month
    form.setValidator("month", [](const string& val) {
        try {
            int month = stoi(val);
            return month >= 1 && month <= 12;
        }
        catch (...) {
            return false;
        }
        }, "Month must be between 1 and 12");

    // Validate year
    form.setValidator("year", [](const string& val) {
        try {
            int year = stoi(val);
            return year >= 2000 && year <= 2100;
        }
        catch (...) {
            return false;
        }
        }, "Year must be between 2000 and 2100");

    FormResult result = form.show();

    if (result.submitted) {
        try {
            GenerateExpenseStatsParams params;
            params.year = result.getInt("year");
            params.month = result.getInt("month");

            auto execResult = useCases["GenerateExpenseStatistics"]->execute(params);
            auto statistics = any_cast<ExpenseStatistics>(execResult);

            displayExpenseStatistics(statistics);
        }
        catch (const DomainException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Unexpected error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
}

void ReportsController::displayMonthlyReport(const MonthlyBuildingReport& report) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== Monthly Building Report ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n" << report.generateReport() << "\n";

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void ReportsController::displayGlobalReport(const GlobalBuildingReport& report) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== Global Portfolio Report ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n" << report.generateReport() << "\n";

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void ReportsController::displayOccupancyStatistics(const OccupancyStatistics& statistics) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== Occupancy Statistics ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n" << statistics.generateReport() << "\n";

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void ReportsController::displayRevenueStatistics(const RevenueStatistics& statistics) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== Revenue Analysis ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n" << statistics.generateReport() << "\n";

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void ReportsController::displayExpenseStatistics(const ExpenseStatistics& statistics) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== Expense Analysis ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n" << statistics.generateReport() << "\n";

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}