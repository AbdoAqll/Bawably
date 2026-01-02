# Bawably

Bawably is a C++ application organized with a hybrid of Clean Architecture and the Vertical Slice pattern. The repository separates core business rules from application orchestration, concrete infrastructure, and presentation, while grouping feature-related code together for clarity and easier maintenance.

## Architecture (Clean Architecture + Vertical Slice)

High-level intent
- Keep the domain model and business invariants central and independent from delivery and persistence concerns.
- Organize code by vertical slices (features/use-cases) so each feature's use-case, presentation controller, DTOs, and domain exceptions are easy to find and change.

Primary layers
- Domain: Pure business entities, value objects, domain exceptions, and report models. No dependencies on other layers.
- Application: Use-cases (one per action) that orchestrate domain entities and repository abstractions. This is the place for application-level validation and orchestration.
- Infrastructure: Concrete implementations of repository interfaces and adapters (currently in-memory repositories). Outer layer that depends on application/domain abstractions.
- Presentation: CLI entrypoint, controllers, dependency container and UI helpers. This layer wires concrete implementations into use-cases and presents results to the user.

Dependency rule
- Inner layers (Domain) are independent and contain no references to outer layers. Application depends on Domain abstractions. Infrastructure and Presentation depend on Application and Domain abstractions but concrete implementations are kept in outer layers.

Why this mixture?
- Clean Architecture stabilizes the core domain and allows independent testing.
- Vertical Slice keeps related code (use-case + controller + DTOs + exceptions) colocated, improving discoverability and making feature changes localized.

## Project layout (important folders)
- `src/Domain/` — Entities (Apartment, Building, RentalContract, RentPayment, Expense, MaintenanceRequest, User), domain exceptions, and report models (MonthlyBuildingReport, RevenueStatistics, ExpenseStatistics, etc.).
- `src/Application/` — Use-cases organized per feature (e.g., `UseCases/Apartment/AddApartment/`). Each use-case coordinates domain operations using repository abstractions.
- `src/Infrastructure/` — Concrete repository implementations (e.g., `InMemory*Repository`) and other environment-specific adapters.
- `src/Presentation/` — CLI entrypoint (`main.cpp`), controllers, `Container/DependencyContainer.cpp` for composition, and UI helpers.

Vertical-slice organization
- Features are organized so that everything needed to implement a single business action is near each other:
  - Use-case in `Application/UseCases/<Feature>/<Action>`
  - Controllers in `Presentation/Controllers/<Feature>`
  - Domain models & exceptions in `Domain/<Feature>`
  - Repository adapters in `Infrastructure/<Feature>/Repositories`
- This reduces cognitive overhead when implementing or changing a feature.

## Key features implemented
The repository contains a broad set of property-management features; notable implemented features include:

- Building management
  - Add building, get building details, list buildings, check building existence.

- Apartment management
  - Add apartment, get apartment details, list apartments, check apartment status and existence.

- Rental contracts
  - Create and end rental contracts, get contract by tenant ID, enforce active/terminated contract rules.

- Rent payments
  - Record full/partial payments, view unpaid/partial tenants, view paid tenants, payment validation and status tracking.

- Users & authentication
  - Create tenant users, login, remove tenant, retrieve all tenants. Distinguishes Owner and Tenant user types with domain-level validation for credentials and uniqueness.

- Maintenance requests
  - Add and close maintenance requests, view requests by building or apartment, status transitions and validations.

- Expenses
  - Add expenses, list all expenses, query expenses by building and month, validate amounts/categories/dates, and surface domain exceptions.

- Reporting and statistics
  - Generate monthly building reports and global reports.
  - Generate occupancy, revenue, and expense statistics (domain-level models such as `RevenueStatistics`, `ExpenseStatistics`, `MonthlyBuildingReport`).

## Error handling and validation
- Domain-specific exception classes express precise failure modes (e.g., `ApartmentNotExistException`, `InvalidPaymentAmountException`, `UsernameAlreadyTakenException`).
- Validation happens at the domain and application levels; use-cases translate invalid states into exceptions which controllers can map to friendly messages.

## Persistence & composition
- Infrastructure currently provides in-memory repositories (`InMemory*Repository` implementations) making the system lightweight and easy to run for development and testing.
- Composition is done in `src/Presentation/Container/DependencyContainer.cpp` where repository implementations are wired into use-cases and controllers; swapping to a persistent store involves implementing the same repository interfaces and updating the DI wiring.