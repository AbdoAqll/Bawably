#include "ExpenseNotFoundException.h"

ExpenseNotFoundException::ExpenseNotFoundException(int expenseId)
    : DomainException("Expense with ID " + std::to_string(expenseId) + " not found") {
}