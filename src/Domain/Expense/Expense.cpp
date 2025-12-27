#include "Expense.h"

Expense::Expense(int id, int buildingId, ExpenseCategory category, double amount,const string &description,const string &expenseDate)
{
}

int Expense::getExpenseId() const
{
    return 0;
}

int Expense::getBuildingId() const
{
    return 0;
}

ExpenseCategory Expense::getCategory() const
{
    return ExpenseCategory();
}

double Expense::getAmount() const
{
    return 0.0;
}

string Expense::getDescription() const
{
    return string();
}

string Expense::getExpenseDate() const
{
    return string();
}

void Expense::setCategory(ExpenseCategory newCategory)
{
}

void Expense::setAmount(double newAmount)
{
}

void Expense::setDescription(string &newDescription)
{
}

void Expense::setExpenseDate(string &newDate)
{
}

void Expense::increaseAmount(double extra)
{
}

void Expense::decreaseAmount(double deduction)
{
}
