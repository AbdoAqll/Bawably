#include "ExpenseCategory.h"
#include <string>

using namespace std;
#pragma once


class Expense
{
private:
    int expenseId;
    int buildingId;
    ExpenseCategory category;
    double amount;
    string description;
    string expenseDate;

public:
    Expense(int id, int buildingId, ExpenseCategory category, double amount,const string &description,const string &expenseDate);

    int getExpenseId() const;
    int getBuildingId() const;
    ExpenseCategory getCategory() const;
    double getAmount() const;
    string getDescription() const;
    string getExpenseDate() const;

    void setCategory(ExpenseCategory newCategory);
    void setExpenseId(int _id);
    void setAmount(double newAmount);
    void setDescription(string &newDescription);
    void setExpenseDate(string &newDate);

    void increaseAmount(double extra);
    void decreaseAmount(double deduction);
};