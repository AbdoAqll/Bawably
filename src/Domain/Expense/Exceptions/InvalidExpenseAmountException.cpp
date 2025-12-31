#include "InvalidExpenseAmountException.h"

InvalidExpenseAmountException::InvalidExpenseAmountException(double amount)
    : DomainException("Invalid expense amount: " + std::to_string(amount) + ". Amount must be positive") {
}