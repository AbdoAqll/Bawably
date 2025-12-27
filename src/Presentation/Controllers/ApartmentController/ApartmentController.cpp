#include "ApartmentController.h"

#include <Apartment/Exceptions/ApartmentAlreadyExistsException.h>
#include <Apartment/Exceptions/ApartmentNotExistException.h>
#include <Building/Exceptions/BuildingNotExistException.h>
#include <UseCases/Apartment/AddApartment/AddApartmentUseCase.h>
#include <UseCases/Apartment/CheckApartmentStatus/CheckApartmentStatusUseCase.h>
#include <UseCases/Apartment/GetAllApartments/GetAllApartmentsUseCase.h>
#include <UseCases/Apartment/GetApartmentDetails/GetApartmentDetailsUseCase.h>
#include <UseCases/Apartment/IsApartmentExists/IsApartmentExistsUseCase.h>

ApartmentController::ApartmentController(vector<shared_ptr<IUseCase> > &useCases) {
    for (const auto& useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
}


void ApartmentController::displayMenu() {
    cout << "\nApartment Menu:\n";
    cout << "1. Add Apartment\n";
    cout << "2. Manage Apartment\n"; // rental / maintenance 
    // first take the id of the Apartment them start to pass it to all the controllers of the other modules
    cout << "3. Get All Apartments\n";
    cout << "4. Get Apartment Details\n";
    cout << "5. Check Apartment Status\n";
    cout << "6. Check if Apartment Exists\n";
    cout << "0. Back to Previous Menu\n";
    cout << "Enter your choice: ";
}

void ApartmentController::createApartment(int buildingId) {
    string apartmentNumber;
    cout << "Enter apartment number: ";
    cin >> apartmentNumber;

    AddApartmentParams params = {buildingId, apartmentNumber};

    try {
        useCases["AddApartment"]->execute(params);
        cout << "Apartment created successfully!" << endl;
    }catch(const ApartmentAlreadyExistsException& e) {
        cout << e.what() << endl;
    }catch (const BuildingNotExistException &e) {
        cout << e.what() << endl;
    }catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


void ApartmentController::getAllApartments(int buildingId) {
    GetAllApartmentArgs getAllApartmentArgs = {buildingId};
    try {
        auto result = useCases["GetAllApartments"]->execute(getAllApartmentArgs);
        auto apartments = any_cast<vector<Apartment>>(result);
        for (const auto& apartment : apartments) {
            cout << "Apartment number: " << apartment.getApartmentNumber() << endl;
            cout << "Apartment status: " << apartment.getStatus() << endl;
            cout << "------------------------------------" << endl;
        }

    }catch (const BuildingNotExistException &e) {
        cout << e.what() << endl;
    }catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


void ApartmentController::getApartmentDetails(int buildingId) {
    string apartmentNumber;
    cout << "Enter apartment number: ";
    cin >> apartmentNumber;

    GetApartmentDetailsParams params = {apartmentNumber, buildingId};

    try {
        auto result = useCases["GetApartmentDetails"]->execute(params);
        Apartment apartment = any_cast<Apartment>(result);
        cout << "Apartment number: " << apartment.getApartmentNumber() << endl;
        cout << "Apartment status: " << apartment.getStatus() << endl;
    }catch (const BuildingNotExistException& e) {
        cout << e.what() << endl;
    }catch (const ApartmentNotExistException& e) {
        cout << e.what() << endl;
    }catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


void ApartmentController::isApartmentExists(int buildingId) {
    string apartmentNumber;
    cout << "Enter apartment number: ";
    cin >> apartmentNumber;

    IsApartmentExistsParams params = {apartmentNumber, buildingId};

    try {
        auto result = useCases["IsApartmentExists"]->execute(params);
        bool isExist = any_cast<bool>(result);
        isExist ? cout << "Exists" : cout << "Not Exists";
        cout << endl;
    }catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void ApartmentController::checkApartmentStatus(int buildingId) {
    string apartmentNumber;
    cout << "Enter apartment number: ";
    cin >> apartmentNumber;

    CheckApartmentStatusParams params = {apartmentNumber, buildingId};

    try {
        auto result = useCases["CheckApartmentStatus"]->execute(params);
        ApartmentStatus status = any_cast<ApartmentStatus>(result);
        cout << "current status is: " << status << endl;
    }catch (const BuildingNotExistException& e) {
        cout << e.what() << endl;
    }catch (const ApartmentNotExistException& e) {
        cout << e.what() << endl;
    }catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


void ApartmentController::execute(int buildingId) {
    int choice = 0;
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                createApartment(buildingId);
                break;
            case 2:
                getAllApartments(buildingId);
                break;
            case 3:
                getApartmentDetails(buildingId);
                break;
            case 4:
                checkApartmentStatus(buildingId);
                break;
            case 5:
                isApartmentExists(buildingId);
                break;
            case 0:
                return;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}



