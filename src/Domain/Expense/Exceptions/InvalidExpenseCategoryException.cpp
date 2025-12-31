#include "InvalidExpenseCategoryException.h"

InvalidExpenseCategoryException::InvalidExpenseCategoryException(int categoryValue)
    : DomainException("Invalid expense category: " + std::to_string(categoryValue) + ". Must be between 0-4 (Electricity, Cleaning, Plumbing, Security, Other)") {
}