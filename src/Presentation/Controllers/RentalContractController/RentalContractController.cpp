#include "RentalContractController.h"
#include "Domain/Shared/DomainException.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "UI/TextEditor.h"
#include <limits>

RentalContractController::RentalContractController(
    vector<shared_ptr<IUseCase>>& useCases,
    shared_ptr<IRentalContractRepository> repository) {
    for (auto useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
    rentalContractRepository = repository;
}

void RentalContractController::execute(int buildingId, int apartmentId) {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Rental Contract Management", {
            "1. Create Rental Contract",
            "2. End Rental Contract",
            "3. View Active Contracts",
            "4. View All Contracts",
            "5. View Contract Details",
            "0. Back to Apartment Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            handleCreateRentalContract(buildingId, apartmentId);
            break;
        case 1:
            handleEndRentalContract();
            break;
        case 2:
            handleViewActiveContracts();
            break;
        case 3:
            handleViewAllContracts();
            break;
        case 4:
            handleViewContractDetails();
            break;
        case 5:
        case -1:
            running = false;
            break;
        }
    }
}

void RentalContractController::handleCreateRentalContract(int buildingId, int apartmentId) {
    ConsoleUtils::clearScreen();

    InputForm form("Create Rental Contract");
    form.addNumberField("tenantId", "Tenant ID", true)
        .addDecimalField("monthlyRent", "Monthly Rent ($)", true)
        .addDateField("startDate", "Start Date (YYYY-MM-DD)", true);

    form.setValidator("monthlyRent", [](const string& val) {
        try {
            double rent = stod(val);
            return rent > 0;
        }
        catch (...) {
            return false;
        }
        }, "Monthly rent must be a positive number");

    FormResult result = form.show();

    if (result.submitted) {
        try {
            int tenantId = result.getInt("tenantId");
            double monthlyRent = result.getDouble("monthlyRent");
            string startDate = result.get("startDate");

            CreateRentalContractParams params{ apartmentId, tenantId, monthlyRent, startDate };
            auto execResult = useCases["CreateRentalContract"]->execute(params);
            auto result = any_cast<CreateRentalContractResult>(execResult);

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n=== CONTRACT CREATION RESULT ===\n\n";
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "Contract ID: " << result.contractId << "\n";
            cout << "Status: " << result.message << "\n\n";

            if (result.isTransfer) {
                ConsoleUtils::textattr(Colors::HIGHLIGHT);
                cout << "** APARTMENT TRANSFER COMPLETED **\n";
                cout << "Previous Apartment ID: " << result.previousApartmentId << "\n";
                cout << "New Apartment ID: " << apartmentId << "\n\n";
            }

            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "Building ID: " << buildingId << endl;
            cout << "Apartment ID: " << apartmentId << endl;
            cout << "Tenant ID: " << tenantId << endl;
            cout << "Monthly Rent: $" << monthlyRent << endl;
            cout << "Start Date: " << startDate << endl;
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
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

void RentalContractController::handleEndRentalContract() {
    ConsoleUtils::clearScreen();

    InputForm form("End Rental Contract");
    form.addNumberField("contractId", "Contract ID", true)
        .addDateField("endDate", "End Date (YYYY-MM-DD)", true);

    FormResult result = form.show();

    if (result.submitted) {
        try {
            int contractId = result.getInt("contractId");
            string endDate = result.get("endDate");

            EndRentalContractParams params{ contractId, endDate };
            useCases["EndRentalContract"]->execute(params);

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Rental contract ended successfully!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "Contract ID: " << contractId << endl;
            cout << "End Date: " << endDate << endl;
            cout << "Status: Inactive" << endl;
            cout << "Apartment Status: Vacant" << endl;
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
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

void RentalContractController::handleViewActiveContracts() {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== Active Rental Contracts ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    try {
        vector<RentalContract> contracts = rentalContractRepository->getActiveContracts();

        if (contracts.empty()) {
            cout << "\nNo active rental contracts found." << endl;
        }
        else {
            displayContractList(contracts);
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

void RentalContractController::handleViewAllContracts() {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== All Rental Contracts ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    try {
        vector<RentalContract> contracts = rentalContractRepository->getAll();

        if (contracts.empty()) {
            cout << "\nNo rental contracts found." << endl;
        }
        else {
            displayContractList(contracts);
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

void RentalContractController::handleViewContractDetails() {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Contract ID", 10);
    editor.setPosition(2, 2).setInputType(InputType::NUMERIC);

    string idStr = editor.show();

    if (idStr.empty()) return;

    int contractId = stoi(idStr);

    try {
        RentalContract* contract = rentalContractRepository->findById(contractId);

        ConsoleUtils::clearScreen();
        if (contract == nullptr) {
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Contract not found." << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
        }
        else {
            ConsoleUtils::textattr(Colors::TITLE);
            cout << "=== Contract Details ===" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            displayContract(*contract);
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

shared_ptr<RentalContract> RentalContractController::getContractForTenantId(int tenantId) {
    try {
        auto res = useCases["GetRentalContractByTenantId"]->execute(tenantId);
        return make_shared<RentalContract>(any_cast<RentalContract>(res));
    }
    catch (const exception& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
    }
    return nullptr;
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

