#include "MaintenanceRequestController.h"

#include <iostream>

#include "Apartment/Exceptions/ApartmentNotExistException.h"
#include "Application/UseCases/MaintenanceRequest/AddMaintenanceRequest/AddMaintenanceRequestUseCase.h"
#include "Building/Exceptions/BuildingNotExistException.h"
#include "MaintenanceRequest/Exceptions/MaintenanceRequestAlreadyClosedException.h"
#include "MaintenanceRequest/Exceptions/MaintenanceRequestNotFoundException.h"
#include "UseCases/MaintenanceRequest/CloseMaintenanceRequest/CloseMaintenanceRequestUseCase.h"
#include "UseCases/MaintenanceRequest/ViewBuildingMaintenanceRequests/ViewBuildingMaintenanceRequestsUseCase.h"

MaintenanceRequestController::MaintenanceRequestController(vector<shared_ptr<IUseCase>> &useCases) {
    for (const auto &useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
}

void MaintenanceRequestController::displayMenu() {
    cout<<"Maintenance Request Menu: "<<endl;
    cout<<"1. Request maintenance for apartment"<<endl;
    cout<<"2. View maintenance requests for a building"<<endl;
    cout<<"3. Close a maintenance request"<<endl;
    cout<<"4. Exit"<<endl;
}

void MaintenanceRequestController::createMaintenanceRequest() {
    int buildingId, apartmentId, tenantId=-1;
    string description;

    cout<<"Enter building number: "<<endl;
    cin>>buildingId;
    cout<<"Enter apartment number: "<<endl;
    cin>>apartmentId;
    cout<<"Enter your id as a tenant (-1) if you are an owner:"<<endl;
    cin>>tenantId;
    cout<<"Enter the description of your problem:"<<endl;
    getline(cin,description);

    AddMaintenanceRequestParams params = {
        apartmentId, buildingId, tenantId, description
    };

    try {
        useCases["AddMaintenanceRequest"]->execute(params);
        cout<<"Maintenance Request created Successfully"<<endl;
    }catch (const BuildingNotExistException &e) {
        cout << e.what() << endl;
    }catch (const ApartmentNotExistException &e) {
        cout << e.what() << endl;
    }catch (const exception &e) {
        cout<<"Error: "<<e.what()<<endl;
    }

}

void MaintenanceRequestController::getBuildingMaintenanceRequest() {
    int buildingId;

    cout<<"Enter building number: "<<endl;
    cin>>buildingId;

    ViewMaintenanceRequestsParams params = {buildingId};

    try {
        useCases[ "ViewBuildingMaintenanceRequests"]->execute(params);
    }catch (const BuildingNotExistException &e) {
        cout << e.what() << endl;
    }catch (const exception &e) {
        cout<<"Error: "<<e.what()<<endl;
    }
}


void MaintenanceRequestController::closeMaintenanceRequest() {
    int requestId;

    cout<<"Enter request id you want to close: "<<endl;
    cin>>requestId;

    CloseMaintenanceRequestParams params = {requestId};

    try {
        useCases[ "CloseMaintenanceRequest"]->execute(params);
        cout<<"Maintenance Request closed Successfully"<<endl;
    }catch (const MaintenanceRequestNotFoundException &e) {
        cout << e.what() << endl;
    }catch (const MaintenanceRequestAlreadyClosedException &e) {
        cout << e.what() << endl;
    }catch (const exception &e) {
        cout<<"Error: "<<e.what()<<endl;
    }
}

void MaintenanceRequestController::execute() {
    int choice = 0;
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                createMaintenanceRequest();
                break;
            case 2:
                getBuildingMaintenanceRequest();
                break;
            case 3:
                closeMaintenanceRequest();
                break;
            case 4:
                return;
            default:
                cout<<"Invalid choice"<<endl;
                break;
        }

    }

}
