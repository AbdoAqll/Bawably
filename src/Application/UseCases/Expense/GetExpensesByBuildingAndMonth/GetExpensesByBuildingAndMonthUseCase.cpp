#include "GetExpensesByBuildingAndMonthUseCase.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"
#include "Domain/Expense/Exceptions/InvalidBuildingIdForExpenseException.h"

GetExpensesByBuildingAndMonthUseCase::GetExpensesByBuildingAndMonthUseCase(const shared_ptr<IExpenseRepository>& expenseRepository) {
    _expenseRepository = expenseRepository;
    UseCaseName = "GetExpensesByBuildingAndMonth";
}

any GetExpensesByBuildingAndMonthUseCase::execute(const any& params) {
    auto args = any_cast<GetExpensesByBuildingAndMonthParams>(params);

    if (args.buildingId <= 0) {
        throw InvalidBuildingIdForExpenseException(args.buildingId);
    }

    if (args.month < 1 || args.month > 12) {
        throw InvalidMonthException(args.month);
    }

    if (args.year < 2000 || args.year > 2100) {
        throw InvalidYearException(args.year);
    }

    vector<Expense> expenses = _expenseRepository->getByBuildingAndMonth(args.buildingId, args.year, args.month);

    double total = 0.0;
    for (const auto& e : expenses) {
        total += e.getAmount();
    }

    GetExpensesByBuildingAndMonthResult result;
    result.expenses = expenses;
    result.totalAmount = total;

    return result;
}
