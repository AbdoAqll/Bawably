// src/Presentation/Cli/ReportsController.h
#pragma once

#include "../../Application/UseCases/Reports/GenerateMonthlyBuildingReportUseCase.h"
#include "../../Application/UseCases/Reports/GenerateGlobalBuildingReportUseCase.h"
#include <iostream>
#include <string>

class ReportsController {
private:
    GenerateMonthlyBuildingReportUseCase& monthlyUseCase;
    GenerateGlobalBuildingReportUseCase& globalUseCase;

public:
    ReportsController(
        GenerateMonthlyBuildingReportUseCase& monthly,
        GenerateGlobalBuildingReportUseCase& global
    );

    void showMenu() const;
    void handleMonthlyReport();
    void handleGlobalReport();
};