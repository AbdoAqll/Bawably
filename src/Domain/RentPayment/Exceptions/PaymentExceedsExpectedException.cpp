#include "PaymentExceedsExpectedException.h"
#include <sstream>
#include <iomanip>

PaymentExceedsExpectedException::PaymentExceedsExpectedException(double totalAmount, double expectedAmount, double remainingAmount)
    : DomainException([&]() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Payment would exceed expected amount. ";
    oss << "Total would be: $" << totalAmount << ", ";
    oss << "Expected: $" << expectedAmount << ", ";
    oss << "Maximum allowed: $" << remainingAmount;
    return oss.str();
        }()) {
}
