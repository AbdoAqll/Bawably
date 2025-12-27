#include "RentalContractController.h"
#include "Domain/Shared/DomainException.h"
#include <limits>

RentalContractController::RentalContractController(
    shared_ptr<CreateRentalContractUseCase> createUseCase,
    shared_ptr<EndRentalContractUseCase> endUseCase,
    shared_ptr<IRentalContractRepository> repository) {
    createRentalContractUseCase = createUseCase;
    endRentalContractUseCase = endUseCase;
    rentalContractRepository = repository;
}

void RentalContractController::showMenu() {
    int choice;
    do {
        cout << "\n=== Rental Contract Management ===" << endl;
        cout << "1. Create Rental Contract" << endl;
        cout << "2. End Rental Contract" << endl;
        cout << "3. View Active Contracts" << endl;
        cout << "4. View All Contracts" << endl;
        cout << "5. View Contract Details" << endl;
        cout << "0. Back to Previous Menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            handleCreateRentalContract();
            break;
        case 2:
            handleEndRentalContract();
            break;
        case 3:
            handleViewActiveContracts();
            break;
        case 4:
            handleViewAllContracts();
            break;
        case 5:
            handleViewContractDetails();
            break;
        case 0:
            cout << "Returning to main menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void RentalContractController::handleCreateRentalContract() {
    cout << "\n--- Create Rental Contract ---" << endl;

    int apartmentId, tenantId;
    double monthlyRent;
    string startDate;

    cout << "Enter Apartment ID: ";
    cin >> apartmentId;

    cout << "Enter Tenant ID: ";
    cin >> tenantId;

    cout << "Enter Monthly Rent: ";
    cin >> monthlyRent;

    cin.ignore();
    cout << "Enter Start Date (YYYY-MM-DD): ";
    getline(cin, startDate);

    try {
        CreateRentalContractParams params{ apartmentId, tenantId, monthlyRent, startDate };
        auto result = createRentalContractUseCase->execute(params);
        int contractId = any_cast<int>(result);

        cout << "\n✓ Rental contract created successfully!" << endl;
        cout << "Contract ID: " << contractId << endl;
        cout << "Apartment ID: " << apartmentId << endl;
        cout << "Tenant ID: " << tenantId << endl;
        cout << "Monthly Rent: $" << monthlyRent << endl;
        cout << "Start Date: " << startDate << endl;
    }
    catch (const DomainException& e) {
        cout << "\n✗ Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "\n✗ Unexpected error: " << e.what() << endl;
    }
}

void RentalContractController::handleEndRentalContract() {
    cout << "\n--- End Rental Contract ---" << endl;

    int contractId;
    string endDate;

    cout << "Enter Contract ID: ";
    cin >> contractId;

    cin.ignore();
    cout << "Enter End Date (YYYY-MM-DD): ";
    getline(cin, endDate);

    try {
        EndRentalContractParams params{ contractId, endDate };
        endRentalContractUseCase->execute(params);

        cout << "\n✓ Rental contract ended successfully!" << endl;
        cout << "Contract ID: " << contractId << endl;
        cout << "End Date: " << endDate << endl;
        cout << "Status: Inactive" << endl;
        cout << "Apartment Status: Vacant" << endl;
    }
    catch (const DomainException& e) {
        cout << "\n✗ Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "\n✗ Unexpected error: " << e.what() << endl;
    }
}

void RentalContractController::handleViewActiveContracts() {
    cout << "\n--- Active Rental Contracts ---" << endl;

    try {
        vector<RentalContract> contracts = rentalContractRepository->getActiveContracts();

        if (contracts.empty()) {
            cout << "No active rental contracts found." << endl;
            return;
        }

        displayContractList(contracts);
    }
    catch (const exception& e) {
        cout << "\n✗ Error: " << e.what() << endl;
    }
}

void RentalContractController::handleViewAllContracts() {
    cout << "\n--- All Rental Contracts ---" << endl;

    try {
        vector<RentalContract> contracts = rentalContractRepository->getAll();

        if (contracts.empty()) {
            cout << "No rental contracts found." << endl;
            return;
        }

        displayContractList(contracts);
    }
    catch (const exception& e) {
        cout << "\n✗ Error: " << e.what() << endl;
    }
}

void RentalContractController::handleViewContractDetails() {
    cout << "\n--- View Contract Details ---" << endl;

    int contractId;
    cout << "Enter Contract ID: ";
    cin >> contractId;

    try {
        RentalContract* contract = rentalContractRepository->findById(contractId);

        if (contract == nullptr) {
            cout << "\n✗ Contract not found." << endl;
            return;
        }

        cout << "\n=== Contract Details ===" << endl;
        displayContract(*contract);
    }
    catch (const exception& e) {
        cout << "\n✗ Error: " << e.what() << endl;
    }
}

void RentalContractController::displayContract(const RentalContract& contract) {
    cout << "Contract ID: " << contract.getContractId() << endl;
    cout << "Apartment ID: " << contract.getApartmentId() << endl;
    cout << "Tenant ID: " << contract.getTenantId() << endl;
    cout << "Monthly Rent: $" << contract.getMonthlyRent() << endl;
    cout << "Start Date: " << contract.getStartDate() << endl;
    cout << "End Date: " << (contract.getEndDate().empty() ? "N/A" : contract.getEndDate()) << endl;
    cout << "Status: " << (contract.getIsActive() ? "Active" : "Inactive") << endl;
    cout << "---" << endl;
}

void RentalContractController::displayContractList(const vector<RentalContract>& contracts) {
    cout << "\nTotal Contracts: " << contracts.size() << "\n" << endl;

    for (const auto& contract : contracts) {
        displayContract(contract);
    }
}
