#include "MaintenanceRequestController.h"

#include <iostream>
#include <limits>

#include "Apartment/Exceptions/ApartmentNotExistException.h"
#include "Application/UseCases/MaintenanceRequest/AddMaintenanceRequest/AddMaintenanceRequestUseCase.h"
#include "Application/UseCases/MaintenanceRequest/ViewApartmentMaintenanceRequests/ViewApartmentMaintenanceRequestsUseCase.h"
#include "Building/Exceptions/BuildingNotExistException.h"
#include "MaintenanceRequest/Exceptions/MaintenanceRequestAlreadyClosedException.h"
#include "MaintenanceRequest/Exceptions/MaintenanceRequestNotFoundException.h"
#include "UseCases/MaintenanceRequest/CloseMaintenanceRequest/CloseMaintenanceRequestUseCase.h"
#include "UseCases/MaintenanceRequest/ViewBuildingMaintenanceRequests/ViewBuildingMaintenanceRequestsUseCase.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "UI/TextEditor.h"

MaintenanceRequestController::MaintenanceRequestController(vector<shared_ptr<IUseCase>>& useCases) {
    for (const auto& useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
}



void MaintenanceRequestController::createMaintenanceRequest(int buildingId) {
    ConsoleUtils::clearScreen();

    InputForm form("Create Maintenance Request");
    form.addNumberField("apartmentId", "Apartment Number", true)
        .addNumberField("tenantId", "Tenant ID (-1 if owner)", true)
        .addTextField("description", "Problem Description", 50, true);

    FormResult result = form.show();

    if (result.submitted) {
        int apartmentId = result.getInt("apartmentId");
        int tenantId = result.getInt("tenantId");
        string description = result.get("description");

        AddMaintenanceRequestParams params = {
            buildingId, tenantId, apartmentId, description
        };

        try {
            useCases["AddMaintenanceRequest"]->execute(params);

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Maintenance Request created successfully!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const BuildingNotExistException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const ApartmentNotExistException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
}

void MaintenanceRequestController::getBuildingMaintenanceRequest(int buildingId) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== Maintenance Requests for Building " << buildingId << " ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    try {
        ViewMaintenanceRequestsParams params = { buildingId };
        useCases["ViewBuildingMaintenanceRequests"]->execute(params);
    }
    catch (const BuildingNotExistException& e) {
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const exception& e) {
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Error: " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void MaintenanceRequestController::closeMaintenanceRequest() {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Request ID to close", 10);
    editor.setPosition(2, 2).setInputType(InputType::NUMERIC);

    string idStr = editor.show();

    if (idStr.empty()) return;

    int requestId = stoi(idStr);

    CloseMaintenanceRequestParams params = { requestId };

    try {
        useCases["CloseMaintenanceRequest"]->execute(params);

        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "\n Maintenance Request closed successfully!" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
    }
    catch (const MaintenanceRequestNotFoundException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
    }
    catch (const MaintenanceRequestAlreadyClosedException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
    }
    catch (const exception& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Error: " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
    }
}

void MaintenanceRequestController::execute(int buildingId) {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Maintenance Management (Building: " + to_string(buildingId) + ")", {
            "1. Request Maintenance for Apartment",
            "2. View Maintenance Requests",
            "3. Close a Maintenance Request",
            "0. Back to Building Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            createMaintenanceRequest(buildingId);
            break;
        case 1:
            getBuildingMaintenanceRequest(buildingId);
            break;
        case 2:
            closeMaintenanceRequest();
            break;
        case 3:
        case -1:
            running = false;
            break;
        }
    }
}

void MaintenanceRequestController::executeForOwner(int buildingId) {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Maintenance Management (Building: " + to_string(buildingId) + ")", {
            "1. View Maintenance Requests",
            "2. Close a Maintenance Request",
            "0. Back to Building Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            getBuildingMaintenanceRequest(buildingId);
            break;
        case 1:
            closeMaintenanceRequest();
            break;
        case 2:
        case -1:
            running = false;
            break;
        }
    }
}

void MaintenanceRequestController::createMaintenanceRequestForTenant(int buildingId, int apartmentId, int tenantId) {
    ConsoleUtils::clearScreen();

    InputForm form("Create Maintenance Request");
    form.addTextField("description", "Problem Description", 100, true);

    FormResult result = form.show();

    if (result.submitted) {
        string description = result.get("description");

        AddMaintenanceRequestParams params = {
            buildingId, tenantId, apartmentId, description
        };

        try {
            useCases["AddMaintenanceRequest"]->execute(params);

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Maintenance Request created successfully!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const BuildingNotExistException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const ApartmentNotExistException& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Error: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
}

void MaintenanceRequestController::getApartmentMaintenanceHistory(int buildingId, int apartmentId) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== Maintenance History for Apartment " << apartmentId << " ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    try {
        ViewApartmentMaintenanceRequestsParams params = { buildingId, apartmentId };
        any result = useCases["ViewApartmentMaintenanceRequests"]->execute(params);
        vector<MaintenanceRequest> requests = any_cast<vector<MaintenanceRequest>>(result);

        if (requests.empty()) {
            cout << "\nNo maintenance requests found for this apartment." << endl;
        }
        else {
            cout << "\nTotal Requests: " << requests.size() << "\n" << endl;
            for (auto& request : requests) {
                cout << "Request ID: " << request.getRequestId() << endl;
                cout << "Description: " << request.getDescription() << endl;
                cout << "Status: " << request.getStatusString() << endl;
                cout << "Created At: " << request.getCreatedAt() << endl;
                if (!request.getResolvedAt().empty()) {
                    cout << "Resolved At: " << request.getResolvedAt() << endl;
                }
                cout << "------------------------------------" << endl;
            }
        }
    }
    catch (const exception& e) {
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Error: " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}
