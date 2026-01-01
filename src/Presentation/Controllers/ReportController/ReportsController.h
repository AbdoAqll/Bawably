#ifndef REPORTSCONTROLLER_H
#define REPORTSCONTROLLER_H

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Application/UseCases/IUseCase.h"
#include "Domain/Shared/DomainException.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "../../../Domain/Report/MonthlyBuildingReport.h"
#include "../../../Domain/Report/GlobalBuildingReport.h"
#include "../../../Domain/Report/OccupancyStatistics.h"
#include "../../../Domain/Report/RevenueStatistics.h"
#include "../../../Domain/Report/ExpenseStatistics.h"
#include "../../../Application/UseCases/Report/GenerateMonthlyBuildingReportUseCase/GenerateMonthlyBuildingReportUseCase.h"
#include "../../../Application/UseCases/Report/GenerateGlobalBuildingReportUseCase/GenerateGlobalBuildingReportUseCase.h"
#include "../../../Application/UseCases/Report/GenerateOccupancyStatisticsUseCase/GenerateOccupancyStatisticsUseCase.h"
#include "../../../Application/UseCases/Report/GenerateRevenueStatisticsUseCase/GenerateRevenueStatisticsUseCase.h"
#include "../../../Application/UseCases/Report/GenerateExpenseStatisticsUseCase/GenerateExpenseStatisticsUseCase.h"

using namespace std;

class ReportsController {
private:
    unordered_map<string, shared_ptr<IUseCase>> useCases;

    void displayMonthlyReport(const MonthlyBuildingReport& report);
    void displayGlobalReport(const GlobalBuildingReport& report);
    void displayOccupancyStatistics(const OccupancyStatistics& statistics);
    void displayRevenueStatistics(const RevenueStatistics& statistics);
    void displayExpenseStatistics(const ExpenseStatistics& statistics);

public:
    ReportsController(
        vector<shared_ptr<IUseCase>>& useCases
    );

    void execute();
    void handleMonthlyReport();
    void handleGlobalReport();
    void handleOccupancyStatistics();
    void handleRevenueStatistics();
    void handleExpenseStatistics();

    ~ReportsController() = default;
};

#endif // REPORTSCONTROLLER_H