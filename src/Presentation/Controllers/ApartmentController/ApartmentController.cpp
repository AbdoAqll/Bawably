#include "ApartmentController.h"

#include <Apartment/Exceptions/ApartmentAlreadyExistsException.h>
#include <Apartment/Exceptions/ApartmentNotExistException.h>
#include <Building/Exceptions/BuildingNotExistException.h>
#include <UseCases/Apartment/AddApartment/AddApartmentUseCase.h>
#include <UseCases/Apartment/GetAllApartments/GetAllApartmentsUseCase.h>
#include <UseCases/Apartment/GetApartmentDetails/GetApartmentDetailsUseCase.h>
#include <UseCases/Apartment/IsApartmentExists/IsApartmentExistsUseCase.h>
#include <UseCases/Apartment/CheckApartmentExistsAndGetId/CheckApartmentExistsAndGetIdUseCase.h>
#include <UseCases/Apartment/CheckApartmentStatus/CheckApartmentStatusUseCase.h>
#include "Controllers/RentalContractController/RentalContractController.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "UI/TextEditor.h"

ApartmentController::ApartmentController(vector<shared_ptr<IUseCase> >& useCases,
    shared_ptr<RentalContractController> rentalContractCtrl) {
    for (const auto& useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
    rentalContractController = rentalContractCtrl;
}


void ApartmentController::displayMenu() {
    // Kept for compatibility
    cout << "\nApartment Menu:\n";
    cout << "1. Add Apartment\n";
    cout << "2. Manage Apartment\n";
    cout << "3. Get All Apartments\n";
    cout << "4. Get Apartment Details\n";
    cout << "5. Check Apartment Status\n";
    cout << "6. Check if Apartment Exists\n";
    cout << "0. Back to Building Menu\n";
    cout << "Enter your choice: ";
}

void ApartmentController::createApartment(int buildingId) {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Apartment Number", 20);
    editor.setPosition(2, 2).setInputType(InputType::ALPHANUMERIC);

    string apartmentNumber = editor.show();

    if (apartmentNumber.empty()) return;

    AddApartmentParams params = { buildingId, apartmentNumber };

    try {
        useCases["AddApartment"]->execute(params);
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "\n Apartment created successfully!" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "Building ID: " << buildingId << endl;
        cout << "Apartment Number: " << apartmentNumber << endl;
    }
    catch (const ApartmentAlreadyExistsException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const BuildingNotExistException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const exception& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Error: " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}


void ApartmentController::getAllApartments(int buildingId) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== All Apartments (Building ID: " << buildingId << ") ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    GetAllApartmentArgs getAllApartmentArgs = { buildingId };
    try {
        auto result = useCases["GetAllApartments"]->execute(getAllApartmentArgs);
        auto apartments = any_cast<vector<Apartment>>(result);

        if (apartments.empty()) {
            cout << "\nNo apartments found in this building." << endl;
        }
        else {
            cout << "\nTotal Apartments: " << apartments.size() << "\n" << endl;
            for (const auto& apartment : apartments) {
                cout << "Apartment Number: " << apartment.getApartmentNumber() << endl;
                cout << "Status: " << apartment.getStatus() << endl;
                cout << "------------------------------------" << endl;
            }
        }
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


void ApartmentController::getApartmentDetails(int buildingId) {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Apartment Number", 20);
    editor.setPosition(2, 2).setInputType(InputType::ALPHANUMERIC);

    string apartmentNumber = editor.show();

    if (apartmentNumber.empty()) return;

    GetApartmentDetailsParams params = { apartmentNumber, buildingId };

    try {
        auto result = useCases["GetApartmentDetails"]->execute(params);
        Apartment apartment = any_cast<Apartment>(result);

        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::TITLE);
        cout << "=== Apartment Details ===" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "Apartment Number: " << apartment.getApartmentNumber() << endl;
        cout << "Building ID: " << buildingId << endl;
        cout << "Status: " << apartment.getStatus() << endl;
    }
    catch (const BuildingNotExistException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const ApartmentNotExistException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const exception& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Error: " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}


void ApartmentController::isApartmentExists(int buildingId) {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Apartment Number", 20);
    editor.setPosition(2, 2).setInputType(InputType::ALPHANUMERIC);

    string apartmentNumber = editor.show();

    if (apartmentNumber.empty()) return;

    IsApartmentExistsParams params = { apartmentNumber, buildingId };

    try {
        auto result = useCases["IsApartmentExists"]->execute(params);
        bool isExist = any_cast<bool>(result);

        ConsoleUtils::clearScreen();
        if (isExist) {
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Apartment '" << apartmentNumber << "' exists in Building " << buildingId << endl;
        }
        else {
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Apartment '" << apartmentNumber << "' does not exist in Building " << buildingId << endl;
        }
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const exception& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Error: " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void ApartmentController::checkApartmentStatus(int buildingId) {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Apartment Number", 20);
    editor.setPosition(2, 2).setInputType(InputType::ALPHANUMERIC);

    string apartmentNumber = editor.show();

    if (apartmentNumber.empty()) return;

    CheckApartmentStatusParams params = { apartmentNumber, buildingId };

    try {
        auto result = useCases["CheckApartmentStatus"]->execute(params);
        ApartmentStatus status = any_cast<ApartmentStatus>(result);

        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::TITLE);
        cout << "=== Apartment Status ===" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "Apartment: " << apartmentNumber << endl;
        cout << "Current Status: " << status << endl;
    }
    catch (const BuildingNotExistException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const ApartmentNotExistException& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    catch (const exception& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Error: " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void ApartmentController::manageApartment(int buildingId) {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Apartment Number to manage", 20);
    editor.setPosition(2, 2).setInputType(InputType::ALPHANUMERIC);

    string apartmentNumber = editor.show();

    if (apartmentNumber.empty()) return;

    CheckApartmentExistsAndGetIdParams params = { apartmentNumber, buildingId };

    try {
        auto result = useCases["CheckApartmentExistsAndGetId"]->execute(params);
        int apartmentId = any_cast<int>(result);
        bool isExist = (apartmentId != -1);
        if (!isExist) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Apartment does not exist." << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
            return;
        }

        bool running = true;
        while (running) {
            std::vector<std::string> options = {
                "1. Rental Contract Management",
                "0. Back to Apartment Menu"
            };
            MenuDisplayer menu("Manage Apartment (" + apartmentNumber + ")", options);

            int choice = menu.show();

            switch (choice) {
            case 0:
                rentalContractController->execute(buildingId, apartmentId);
                break;
            case 1:
            case -1:
                running = false;
                break;
            }
        }
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


void ApartmentController::execute(int buildingId) {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Apartment Management (Building ID: " + to_string(buildingId) + ")", {
            "1. Add Apartment",
            "2. Manage Apartment",
            "3. Get All Apartments",
            "4. Get Apartment Details",
            "5. Check Apartment Status",
            "6. Check if Apartment Exists",
            "0. Back to Building Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            createApartment(buildingId);
            break;
        case 1:
            manageApartment(buildingId);
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
        case 6:
        case -1:
            running = false;
            break;
        }
    }
}



