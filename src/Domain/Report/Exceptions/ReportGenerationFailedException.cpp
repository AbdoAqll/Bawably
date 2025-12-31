#include "ReportGenerationFailedException.h"

ReportGenerationFailedException::ReportGenerationFailedException(const std::string& reason)
    : DomainException(reason) {
}
