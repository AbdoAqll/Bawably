#ifndef IEXPENSEREPOSITORY_H
#define IEXPENSEREPOSITORY_H

#include "Domain/Expense/Expense.h"
#include <vector>
#include <memory>

using namespace std;

class IExpenseRepository {
public:
    virtual ~IExpenseRepository() = default;
    virtual void add(const Expense& expense) = 0;
    virtual vector<Expense> getByBuilding(int buildingId) = 0;
    virtual vector<Expense> getByBuildingAndMonth(int buildingId, int year, int month) = 0;
    virtual vector<Expense> getAll() = 0;
    virtual int getNextId() = 0;
};

#endif // IEXPENSEREPOSITORY_H
