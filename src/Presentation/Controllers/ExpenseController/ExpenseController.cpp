#include "ExpenseController.h"
#include "Application/UseCases/Expense/AddExpense/AddExpenseUseCase.h"
#include "Application/UseCases/Expense/GetBuildingExpenses/GetBuildingExpensesUseCase.h"
#include "Application/UseCases/Expense/GetExpensesByBuildingAndMonth/GetExpensesByBuildingAndMonthUseCase.h"
#include "Application/UseCases/Expense/GetAllExpenses/GetAllExpensesUseCase.h"
#include "Domain/Expense/Expense.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "UI/TextEditor.h"
#include <iostream>
#include <iomanip>

ExpenseController::ExpenseController(vector<shared_ptr<IUseCase>>& useCases) {
    for (auto useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
}

string getCategoryName(ExpenseCategory category) {
    switch (category) {
    case ExpenseCategory::Electricity: return "Electricity";
    case ExpenseCategory::Cleaning: return "Cleaning";
    case ExpenseCategory::Plumbing: return "Plumbing";
    case ExpenseCategory::Security: return "Security";
    case ExpenseCategory::Other: return "Other";
    default: return "Unknown";
    }
}

void ExpenseController::executeForBuilding(int buildingId) {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Expense Management (Building ID: " + to_string(buildingId) + ")", {
            "1. Add Expense",
            "2. View Building Expenses",
            "0. Back"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            addExpense(buildingId);
            break;
        case 1:
            viewBuildingExpenses(buildingId);
            break;
        case 2:
        case -1:
            running = false;
            break;
        }
    }
}

void ExpenseController::addExpense(int buildingId) {
    ConsoleUtils::clearScreen();

    string formTitle = "Add Expense - Building " + to_string(buildingId) + " | Categories: 0=Electricity, 1=Cleaning, 2=Plumbing, 3=Security, 4=Other";

    InputForm form(formTitle);
    form.addTextField("amount", "Amount", 15, true)
        .addTextField("date", "Date (YYYY-MM-DD)", 12, true)
        .addTextField("category", "Category (0-4)", 5, true)
        .addTextField("description", "Description", 50, false);

    FormResult result = form.show();

    if (result.submitted) {
        try {
            double amount = stod(result.get("amount"));
            string date = result.get("date");
            string description = result.get("description");
            int categoryInt = stoi(result.get("category"));

            if (categoryInt < 0 || categoryInt > 4) {
                throw invalid_argument("Invalid category (must be 0-4)");
            }

            AddExpenseParams params;
            params.buildingId = buildingId;
            params.amount = amount;
            params.expenseDate = date;
            params.description = description;
            params.category = static_cast<ExpenseCategory>(categoryInt);

            auto expenseId = any_cast<int>(useCases["AddExpense"]->execute(params));

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Expense added successfully! ID: " << expenseId << endl;
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
}

void ExpenseController::viewBuildingExpenses(int buildingId) {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== Expenses for Building ID: " << buildingId << " ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    try {
        auto result = useCases["GetBuildingExpenses"]->execute(buildingId);
        vector<Expense> expenses = any_cast<vector<Expense>>(result);

        if (expenses.empty()) {
            cout << "\nNo expenses found for this building." << endl;
        }
        else {
            double totalAmount = 0;
            cout << "\n" << left << setw(8) << "ID"
                << setw(15) << "Category"
                << setw(12) << "Amount"
                << setw(14) << "Date"
                << "Description" << endl;
            cout << string(70, '-') << endl;

            for (const auto& expense : expenses) {
                cout << left << setw(8) << expense.getExpenseId()
                    << setw(15) << getCategoryName(expense.getCategory())
                    << setw(12) << fixed << setprecision(2) << expense.getAmount()
                    << setw(14) << expense.getExpenseDate()
                    << expense.getDescription() << endl;
                totalAmount += expense.getAmount();
            }

            cout << string(70, '-') << endl;
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "Total: " << fixed << setprecision(2) << totalAmount << " EGP" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
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

void ExpenseController::execute() {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Expense Reports", {
            "1. View All Expenses",
            "2. Get Expenses By Building",
            "3. Get Expenses By Building And Month",
            "0. Back to Main Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            viewAllExpenses();
            break;
        case 1:
            getExpensesByBuilding();
            break;
        case 2:
            getExpensesByBuildingAndMonth();
            break;
        case 3:
        case -1:
            running = false;
            break;
        }
    }
}

void ExpenseController::viewAllExpenses() {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== All Expenses ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    try {
        auto result = useCases["GetAllExpenses"]->execute();
        vector<Expense> expenses = any_cast<vector<Expense>>(result);

        if (expenses.empty()) {
            cout << "\nNo expenses found." << endl;
        }
        else {
            double totalAmount = 0;
            cout << "\n" << left << setw(8) << "ID"
                << setw(12) << "Building"
                << setw(15) << "Category"
                << setw(12) << "Amount"
                << setw(14) << "Date"
                << "Description" << endl;
            cout << string(80, '-') << endl;

            for (const auto& expense : expenses) {
                cout << left << setw(8) << expense.getExpenseId()
                    << setw(12) << expense.getBuildingId()
                    << setw(15) << getCategoryName(expense.getCategory())
                    << setw(12) << fixed << setprecision(2) << expense.getAmount()
                    << setw(14) << expense.getExpenseDate()
                    << expense.getDescription() << endl;
                totalAmount += expense.getAmount();
            }

            cout << string(80, '-') << endl;
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "Total: " << fixed << setprecision(2) << totalAmount << " EGP" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
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

void ExpenseController::getExpensesByBuilding() {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Building ID", 10);
    editor.setPosition(2, 2).setInputType(InputType::NUMERIC);

    string idStr = editor.show();

    if (idStr.empty()) return;

    int buildingId = stoi(idStr);
    viewBuildingExpenses(buildingId);
}

void ExpenseController::getExpensesByBuildingAndMonth() {
    ConsoleUtils::clearScreen();

    InputForm form("Get Expenses By Building And Month");
    form.addTextField("buildingId", "Building ID", 10, true)
        .addTextField("year", "Year", 6, true)
        .addTextField("month", "Month (1-12)", 4, true);

    FormResult result = form.show();

    if (result.submitted) {
        try {
            int buildingId = stoi(result.get("buildingId"));
            int year = stoi(result.get("year"));
            int month = stoi(result.get("month"));

            GetExpensesByBuildingAndMonthParams params;
            params.buildingId = buildingId;
            params.year = year;
            params.month = month;

            auto queryResult = useCases["GetExpensesByBuildingAndMonth"]->execute(params);
            auto data = any_cast<GetExpensesByBuildingAndMonthResult>(queryResult);

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::TITLE);
            cout << "=== Expenses for Building " << buildingId << " in " << month << "/" << year << " ===" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);

            if (data.expenses.empty()) {
                cout << "\nNo expenses found for this period." << endl;
            }
            else {
                cout << "\n" << left << setw(8) << "ID"
                    << setw(15) << "Category"
                    << setw(12) << "Amount"
                    << setw(14) << "Date"
                    << "Description" << endl;
                cout << string(70, '-') << endl;

                for (const auto& expense : data.expenses) {
                    cout << left << setw(8) << expense.getExpenseId()
                        << setw(15) << getCategoryName(expense.getCategory())
                        << setw(12) << fixed << setprecision(2) << expense.getAmount()
                        << setw(14) << expense.getExpenseDate()
                        << expense.getDescription() << endl;
                }

                cout << string(70, '-') << endl;
                ConsoleUtils::textattr(Colors::HIGHLIGHT);
                cout << "Total: " << fixed << setprecision(2) << data.totalAmount << " EGP" << endl;
                ConsoleUtils::textattr(Colors::DEFAULT);
            }
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
}