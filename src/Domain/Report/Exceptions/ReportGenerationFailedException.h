#ifndef REPORTGENERATIONFAILEDEXCEPTION_H
#define REPORTGENERATIONFAILEDEXCEPTION_H

#include <Shared/DomainException.h>
#include <string>

class ReportGenerationFailedException : public DomainException {
public:
    explicit ReportGenerationFailedException(const std::string& reason);
};

#endif //REPORTGENERATIONFAILEDEXCEPTION_H
