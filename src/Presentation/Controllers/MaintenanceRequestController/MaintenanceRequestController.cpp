#include "MaintenanceRequestController.h"

#include <iostream>
#include "Application/UseCases/MaintenanceRequest/AddMaintenanceRequest/AddMaintenanceRequestUseCase.h"

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


}
