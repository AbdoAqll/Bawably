#include "RentPaymentController.h"
#include "Domain/Shared/DomainException.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include <iomanip>

RentPaymentController::RentPaymentController(
    shared_ptr<RecordRentPaymentUseCase> recordUseCase,
    shared_ptr<AddPartialPaymentUseCase> addPartialUseCase,
    shared_ptr<ViewPaidTenantsUseCase> viewPaidUseCase,
    shared_ptr<ViewUnpaidOrPartialTenantsUseCase> viewUnpaidUseCase,
    shared_ptr<IRentPaymentRepository> repository) {
    recordRentPaymentUseCase = recordUseCase;
    addPartialPaymentUseCase = addPartialUseCase;
    viewPaidTenantsUseCase = viewPaidUseCase;
    viewUnpaidOrPartialTenantsUseCase = viewUnpaidUseCase;
    rentPaymentRepository = repository;
}

void RentPaymentController::execute() {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Rent Payment Management", {
            "1. Record Rent Payment",
            "2. Add Partial Payment",
            "3. View Paid Tenants",
            "4. View Unpaid/Partial Tenants",
            "5. View All Payments",
            "0. Back to Main Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            handleRecordRentPayment();
            break;
        case 1:
            handleAddPartialPayment();
            break;
        case 2:
            handleViewPaidTenants();
            break;
        case 3:
            handleViewUnpaidOrPartialTenants();
            break;
        case 4:
            handleViewAllPayments();
            break;
        case 5:
        case -1:
            running = false;
            break;
        }
    }
}

void RentPaymentController::handleRecordRentPayment() {
    ConsoleUtils::clearScreen();

    InputForm form("Record Rent Payment");
    form.addNumberField("contractId", "Contract ID", true)
        .addNumberField("month", "Month (1-12)", true)
        .addNumberField("year", "Year", true)
        .addDecimalField("amountPaid", "Amount Paid ($)", true)
        .addDateField("paymentDate", "Payment Date (YYYY-MM-DD)", true);

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

    // Validate amount
    form.setValidator("amountPaid", [](const string& val) {
        try {
            double amount = stod(val);
            return amount >= 0;
        }
        catch (...) {
            return false;
        }
        }, "Amount must be a non-negative number");

    FormResult result = form.show();

    if (result.submitted) {
        try {
            RecordRentPaymentParams params;
            params.contractId = result.getInt("contractId");
            params.month = result.getInt("month");
            params.year = result.getInt("year");
            params.amountPaid = result.getDouble("amountPaid");
            params.paymentDate = result.get("paymentDate");

            auto execResult = recordRentPaymentUseCase->execute(params);
            auto paymentResult = any_cast<RecordRentPaymentResult>(execResult);

            displayPaymentDetails(paymentResult);
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

void RentPaymentController::handleAddPartialPayment() {
    ConsoleUtils::clearScreen();

    InputForm form("Add Partial Payment");
    form.addNumberField("contractId", "Contract ID", true)
        .addNumberField("month", "Month (1-12)", true)
        .addNumberField("year", "Year", true)
        .addDecimalField("amount", "Amount to Add ($)", true)
        .addDateField("paymentDate", "Payment Date (YYYY-MM-DD)", true);

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

    // Validate amount must be positive
    form.setValidator("amount", [](const string& val) {
        try {
            double amount = stod(val);
            return amount > 0;
        }
        catch (...) {
            return false;
        }
        }, "Amount must be a positive number");

    FormResult result = form.show();

    if (result.submitted) {
        try {
            AddPartialPaymentParams params;
            params.contractId = result.getInt("contractId");
            params.month = result.getInt("month");
            params.year = result.getInt("year");
            params.amount = result.getDouble("amount");
            params.paymentDate = result.get("paymentDate");

            auto execResult = addPartialPaymentUseCase->execute(params);
            auto paymentResult = any_cast<AddPartialPaymentResult>(execResult);

            displayPartialPaymentResult(paymentResult);
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

void RentPaymentController::handleViewPaidTenants() {
    ConsoleUtils::clearScreen();

    InputForm form("View Paid Tenants");
    form.addNumberField("month", "Month (1-12)", true)
        .addNumberField("year", "Year", true);

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
            ViewPaidTenantsParams params;
            params.month = result.getInt("month");
            params.year = result.getInt("year");

            auto execResult = viewPaidTenantsUseCase->execute(params);
            auto paidTenants = any_cast<vector<PaidTenantInfo>>(execResult);

            displayPaidTenantsList(paidTenants, params.month, params.year);
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

void RentPaymentController::handleViewUnpaidOrPartialTenants() {
    ConsoleUtils::clearScreen();

    InputForm form("View Unpaid/Partial Tenants");
    form.addNumberField("month", "Month (1-12)", true)
        .addNumberField("year", "Year", true);

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
            ViewUnpaidOrPartialTenantsParams params;
            params.month = result.getInt("month");
            params.year = result.getInt("year");

            auto execResult = viewUnpaidOrPartialTenantsUseCase->execute(params);
            auto tenants = any_cast<vector<UnpaidOrPartialTenantInfo>>(execResult);

            displayUnpaidOrPartialTenantsList(tenants, params.month, params.year);
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

void RentPaymentController::handleViewAllPayments() {
    ConsoleUtils::clearScreen();

    auto payments = rentPaymentRepository->getAll();

    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== All Rent Payments ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    if (payments.empty()) {
        cout << "\nNo payments recorded yet." << endl;
    }
    else {
        cout << "\n" << left
            << setw(6) << "ID"
            << setw(10) << "Contract"
            << setw(10) << "Tenant"
            << setw(12) << "Period"
            << setw(12) << "Paid"
            << setw(12) << "Expected"
            << setw(10) << "Status"
            << "Date" << endl;
        cout << string(80, '-') << endl;

        for (const auto& payment : payments) {
            string period = to_string(payment.getMonth()) + "/" + to_string(payment.getYear());

            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << left
                << setw(6) << payment.getPaymentId()
                << setw(10) << payment.getContractId()
                << setw(10) << payment.getTenantId()
                << setw(12) << period
                << "$" << setw(10) << fixed << setprecision(2) << payment.getAmountPaid()
                << "$" << setw(10) << payment.getExpectedAmount();

            // Color-code status
            switch (payment.getStatus()) {
            case PaymentStatus::Paid:
                ConsoleUtils::textattr(Colors::HIGHLIGHT);
                cout << setw(10) << "Paid";
                break;
            case PaymentStatus::Partial:
                ConsoleUtils::textattr(Colors::TITLE);
                cout << setw(10) << "Partial";
                break;
            case PaymentStatus::Unpaid:
                ConsoleUtils::textattr(Colors::ERR);
                cout << setw(10) << "Unpaid";
                break;
            }
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << payment.getPaymentDate() << endl;
        }
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void RentPaymentController::displayPaymentDetails(const RecordRentPaymentResult& result) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::HIGHLIGHT);
    cout << "\n Rent payment recorded successfully!" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n--- Payment Details ---" << endl;
    cout << "Payment ID: " << result.paymentId << endl;
    cout << "Contract ID: " << result.contractId << endl;
    cout << "Tenant ID: " << result.tenantId << endl;
    cout << "Period: " << getMonthName(result.month) << " " << result.year << endl;
    cout << "Amount Paid: $" << fixed << setprecision(2) << result.amountPaid << endl;
    cout << "Expected Amount: $" << result.expectedAmount << endl;
    cout << "Remaining: $" << result.remainingAmount << endl;
    cout << "Status: ";

    switch (result.status) {
    case PaymentStatus::Paid:
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "PAID";
        break;
    case PaymentStatus::Partial:
        ConsoleUtils::textattr(Colors::TITLE);
        cout << "PARTIAL";
        break;
    case PaymentStatus::Unpaid:
        ConsoleUtils::textattr(Colors::ERR);
        cout << "UNPAID";
        break;
    }
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void RentPaymentController::displayPartialPaymentResult(const AddPartialPaymentResult& result) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::HIGHLIGHT);
    cout << "\n Partial payment added successfully!" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n--- Payment Update ---" << endl;
    cout << "Payment ID: " << result.paymentId << endl;
    cout << "Contract ID: " << result.contractId << endl;
    cout << "Tenant ID: " << result.tenantId << endl;
    cout << "Period: " << getMonthName(result.month) << " " << result.year << endl;
    cout << "\nPrevious Amount: $" << fixed << setprecision(2) << result.previousAmount << endl;
    cout << "Added Amount: $" << result.addedAmount << endl;
    cout << "Total Paid: $" << result.totalAmountPaid << endl;
    cout << "Expected Amount: $" << result.expectedAmount << endl;
    cout << "Remaining: $" << result.remainingAmount << endl;

    cout << "\nStatus Change: ";
    cout << getStatusString(result.previousStatus) << " -> ";

    switch (result.newStatus) {
    case PaymentStatus::Paid:
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        break;
    case PaymentStatus::Partial:
        ConsoleUtils::textattr(Colors::TITLE);
        break;
    case PaymentStatus::Unpaid:
        ConsoleUtils::textattr(Colors::ERR);
        break;
    }
    cout << getStatusString(result.newStatus);
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\n\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void RentPaymentController::displayPaidTenantsList(const vector<PaidTenantInfo>& tenants, int month, int year) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== Paid Tenants for " << getMonthName(month) << " " << year << " ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    if (tenants.empty()) {
        cout << "\nNo tenants with fully paid rent for this period." << endl;
    }
    else {
        cout << "\n" << left
            << setw(10) << "Tenant"
            << setw(20) << "Name"
            << setw(10) << "Contract"
            << setw(10) << "Building"
            << setw(10) << "Apt"
            << setw(12) << "Amount"
            << "Date" << endl;
        cout << string(90, '-') << endl;

        for (const auto& tenant : tenants) {
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << left
                << setw(10) << tenant.tenantId
                << setw(20) << tenant.tenantName
                << setw(10) << tenant.contractId
                << setw(10) << tenant.buildingId
                << setw(10) << tenant.apartmentId
                << "$" << setw(11) << fixed << setprecision(2) << tenant.amountPaid
                << tenant.paymentDate << endl;
        }
        ConsoleUtils::textattr(Colors::DEFAULT);

        cout << string(90, '-') << endl;
        cout << "Total compliant tenants: " << tenants.size() << endl;
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void RentPaymentController::displayUnpaidOrPartialTenantsList(const vector<UnpaidOrPartialTenantInfo>& tenants, int month, int year) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "\n=== Unpaid/Partial Tenants for " << getMonthName(month) << " " << year << " ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    if (tenants.empty()) {
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "\nAll tenants have fully paid rent for this period!" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    else {
        cout << "\n" << left
            << setw(10) << "Tenant"
            << setw(18) << "Name"
            << setw(10) << "Contract"
            << setw(10) << "Paid"
            << setw(10) << "Expected"
            << setw(10) << "Remaining"
            << "Status" << endl;
        cout << string(85, '-') << endl;

        for (const auto& tenant : tenants) {
            cout << left
                << setw(10) << tenant.tenantId
                << setw(18) << tenant.tenantName
                << setw(10) << tenant.contractId
                << "$" << setw(9) << fixed << setprecision(2) << tenant.amountPaid
                << "$" << setw(9) << tenant.expectedAmount
                << "$" << setw(9) << tenant.remainingAmount;

            if (tenant.status == PaymentStatus::Unpaid) {
                ConsoleUtils::textattr(Colors::ERR);
                cout << "UNPAID";
            }
            else {
                ConsoleUtils::textattr(Colors::TITLE);
                cout << "PARTIAL";
            }
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << endl;
        }

        cout << string(85, '-') << endl;
        cout << "Total tenants requiring follow-up: " << tenants.size() << endl;
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

string RentPaymentController::getStatusString(PaymentStatus status) {
    switch (status) {
    case PaymentStatus::Paid: return "Paid";
    case PaymentStatus::Partial: return "Partial";
    case PaymentStatus::Unpaid: return "Unpaid";
    default: return "Unknown";
    }
}

string RentPaymentController::getMonthName(int month) {
    const string months[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    if (month >= 1 && month <= 12) {
        return months[month];
    }
    return "Invalid";
}
