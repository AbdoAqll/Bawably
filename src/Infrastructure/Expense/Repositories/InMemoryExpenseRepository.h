#ifndef INMEMORYEXPENSEREPOSITORY_H
#define INMEMORYEXPENSEREPOSITORY_H

#include "Application/UseCases/Expense/Interfaces/IExpenseRepository.h"
#include <vector>

class InMemoryExpenseRepository : public IExpenseRepository {
private:
    vector<Expense> expenses;
    int nextId = 1;

public:
    void add(const Expense& expense) override;
    vector<Expense> getByBuilding(int buildingId) override;
    vector<Expense> getByBuildingAndMonth(int buildingId, int year, int month) override;
    vector<Expense> getAll() override;
    int getNextId() override;
};

#endif // INMEMORYEXPENSEREPOSITORY_H