#include "InputForm.h"
#include "ConsoleUtils.h"
#include <algorithm>

using namespace std;

InputForm::InputForm(const string& title)
    : title(title), startX(2), startY(1), currentField(0), showBorder(true) {
}

int InputForm::getMaxLabelWidth() const {
    int maxWidth = 0;
    for (const auto& field : fields) {
        maxWidth = max(maxWidth, static_cast<int>(field.label.length()));
    }
    return maxWidth;
}

void InputForm::drawField(int index, bool isActive) {
    const FormField& field = fields[index];
    int labelWidth = getMaxLabelWidth();
    int fieldY = startY + 3 + (index * 3);  // 3 lines per field (label+input, cursor, spacing)

    // Draw label
    ConsoleUtils::gotoxy(startX, fieldY);
    ConsoleUtils::textattr(isActive ? Colors::HIGHLIGHT : Colors::LABEL);
    cout << field.label;

    // Pad to align input fields
    for (int i = static_cast<int>(field.label.length()); i < labelWidth; i++) {
        cout << ' ';
    }

    ConsoleUtils::textattr(Colors::DEFAULT);
    cout << ": ";

    // Draw required indicator
    if (field.required) {
        ConsoleUtils::textattr(Colors::ERR);
        cout << "* ";
        ConsoleUtils::textattr(Colors::DEFAULT);
    }
    else {
        cout << "  ";
    }

    // Draw the current value (if not the active field being edited)
    if (!isActive && !field.value.empty()) {
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << field.value;
        // Clear any remaining characters from previous longer values
        for (int i = static_cast<int>(field.value.length()); i < field.maxLen; i++) {
            cout << ' ';
        }
    }
    else if (!isActive) {
        // Draw empty field placeholder
        for (int i = 0; i < field.maxLen; i++) {
            cout << '_';
        }
    }
}

void InputForm::draw() {
    ConsoleUtils::clearScreen();

    // Draw title
    ConsoleUtils::gotoxy(startX, startY);
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== " << title << " ===";

    // Draw instructions
    ConsoleUtils::gotoxy(startX, startY + 1);
    ConsoleUtils::textattr(Colors::DEFAULT);
    cout << "TAB: Next Field | ENTER: Submit | ESC: Cancel";

    // Draw separator
    ConsoleUtils::gotoxy(startX, startY + 2);
    int formWidth = getMaxLabelWidth() + 60;  // Label + input width
    for (int i = 0; i < formWidth; i++) cout << char(196);

    // Draw all field labels
    for (int i = 0; i < static_cast<int>(fields.size()); i++) {
        drawField(i, i == currentField);
    }

    // Draw errors if any
    if (!errors.empty()) {
        int errorY = startY + 3 + static_cast<int>(fields.size()) * 3;
        ConsoleUtils::gotoxy(startX, errorY);
        ConsoleUtils::textattr(Colors::ERR);
        for (const auto& error : errors) {
            cout << "! " << error << endl;
            ConsoleUtils::gotoxy(startX, ++errorY);
        }
    }

    ConsoleUtils::textattr(Colors::DEFAULT);
}

bool InputForm::validateField(int index) {
    const FormField& field = fields[index];

    // Check required
    if (field.required && field.value.empty()) {
        return false;
    }

    // Custom validator
    if (field.validator && !field.value.empty()) {
        return field.validator(field.value);
    }

    return true;
}

bool InputForm::validateAll() {
    errors.clear();
    bool valid = true;

    for (int i = 0; i < static_cast<int>(fields.size()); i++) {
        if (!validateField(i)) {
            if (fields[i].required && fields[i].value.empty()) {
                errors.push_back(fields[i].label + " is required");
            }
            else if (!fields[i].errorMessage.empty()) {
                errors.push_back(fields[i].errorMessage);
            }
            else {
                errors.push_back(fields[i].label + " is invalid");
            }
            valid = false;
        }
    }

    return valid;
}

FormResult InputForm::show() {
    FormResult result;
    result.submitted = false;
    result.cancelled = false;

    if (fields.empty()) {
        return result;
    }

    ConsoleUtils::hideCursor();
    currentField = 0;

    while (true) {
        draw();

        // Create editor for current field
        FormField& field = fields[currentField];
        int labelWidth = getMaxLabelWidth();
        int fieldY = startY + 3 + (currentField * 3);
        int inputX = startX + labelWidth + 4;  // +4 for ": " and required indicator

        SingleLineEditor editor(field.label, field.maxLen);
        editor.setPosition(inputX, fieldY)
            .setShowLabel(false)
            .setInputType(field.inputType)
            .setInitialValue(field.value);

        string value = editor.show();

        // If editor returns empty string and field was also empty, user pressed ESC
        if (value.empty() && field.value.empty()) {
            result.cancelled = true;
            return result;
        }

        // Store the value
        field.value = value;

        // Move to next field or submit
        currentField++;

        if (currentField >= static_cast<int>(fields.size())) {
            // Validate all fields
            if (validateAll()) {
                result.submitted = true;
                for (const auto& f : fields) {
                    result.values[f.name] = f.value;
                }
                return result;
            }
            else {
                // Show errors and restart from first error
                currentField = 0;
                for (int i = 0; i < static_cast<int>(fields.size()); i++) {
                    if (!validateField(i)) {
                        currentField = i;
                        break;
                    }
                }
            }
        }
    }
}

InputForm& InputForm::addField(const string& name, const string& label, int maxLen,
    InputType inputType, bool required) {
    fields.emplace_back(name, label, maxLen, inputType, required);
    return *this;
}

InputForm& InputForm::addTextField(const string& name, const string& label, int maxLen, bool required) {
    return addField(name, label, maxLen, InputType::ANY, required);
}

InputForm& InputForm::addNumberField(const string& name, const string& label, bool required) {
    return addField(name, label, 15, InputType::NUMERIC, required);
}

InputForm& InputForm::addDecimalField(const string& name, const string& label, bool required) {
    return addField(name, label, 15, InputType::DECIMAL, required);
}

InputForm& InputForm::addDateField(const string& name, const string& label, bool required) {
    return addField(name, label, 10, InputType::DATE, required);
}

InputForm& InputForm::setValidator(const string& fieldName, function<bool(const string&)> validator,
    const string& errorMessage) {
    for (auto& field : fields) {
        if (field.name == fieldName) {
            field.validator = validator;
            field.errorMessage = errorMessage;
            break;
        }
    }
    return *this;
}

InputForm& InputForm::setInitialValue(const string& fieldName, const string& value) {
    for (auto& field : fields) {
        if (field.name == fieldName) {
            field.value = value;
            break;
        }
    }
    return *this;
}

InputForm& InputForm::setPosition(int x, int y) {
    startX = x;
    startY = y;
    return *this;
}

InputForm& InputForm::setBorder(bool show) {
    showBorder = show;
    return *this;
}
