#include "Expense.h"

Expense::Expense(int id, int buildingId, ExpenseCategory category, double amount, const string& description, const string& expenseDate)
    : expenseId(id), buildingId(buildingId), category(category), amount(amount), description(description), expenseDate(expenseDate) {
}

int Expense::getExpenseId() const {
    return expenseId;
}

int Expense::getBuildingId() const {
    return buildingId;
}

ExpenseCategory Expense::getCategory() const {
    return category;
}

double Expense::getAmount() const {
    return amount;
}

string Expense::getDescription() const {
    return description;
}

string Expense::getExpenseDate() const {
    return expenseDate;
}

void Expense::setCategory(ExpenseCategory newCategory) {
    category = newCategory;
}

void Expense::setExpenseId(int _id) {
    expenseId = _id;
}

void Expense::setAmount(double newAmount) {
    amount = newAmount;
}

void Expense::setDescription(string& newDescription) {
    description = newDescription;
}

void Expense::setExpenseDate(string& newDate) {
    expenseDate = newDate;
}

void Expense::increaseAmount(double extra) {
    amount += extra;
}

void Expense::decreaseAmount(double deduction) {
    amount -= deduction;
}
