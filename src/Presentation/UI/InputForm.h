#ifndef INPUT_FORM_H
#define INPUT_FORM_H

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include "TextEditor.h"

// Form field configuration
struct FormField {
    std::string name;           // Internal name for lookup
    std::string label;          // Display label
    int maxLen;
    InputType inputType;
    std::string value;
    bool required;
    std::function<bool(const std::string&)> validator;  // Custom validation
    std::string errorMessage;

    FormField(const std::string& name, const std::string& label, int maxLen = 50,
        InputType inputType = InputType::ANY, bool required = false)
        : name(name), label(label), maxLen(maxLen), inputType(inputType),
        required(required) {
    }
};

// Result from form submission
struct FormResult {
    bool submitted;        // true if user pressed Enter on last field/submit
    bool cancelled;        // true if user pressed ESC
    std::unordered_map<std::string, std::string> values;

    std::string get(const std::string& name) const {
        auto it = values.find(name);
        return (it != values.end()) ? it->second : "";
    }

    int getInt(const std::string& name) const {
        try { return std::stoi(get(name)); }
        catch (...) { return 0; }
    }

    double getDouble(const std::string& name) const {
        try { return std::stod(get(name)); }
        catch (...) { return 0.0; }
    }
};

// Multi-field input form with TAB navigation
class InputForm {
private:
    std::string title;
    std::vector<FormField> fields;
    int startX, startY;
    int currentField;
    bool showBorder;
    std::vector<std::string> errors;

    void draw();
    void drawField(int index, bool isActive);
    bool validateField(int index);
    bool validateAll();
    int getMaxLabelWidth() const;

public:
    InputForm(const std::string& title = "");

    // Add fields to the form
    InputForm& addField(const std::string& name, const std::string& label, int maxLen = 50,
        InputType inputType = InputType::ANY, bool required = false);

    // Convenience methods for common field types
    InputForm& addTextField(const std::string& name, const std::string& label, int maxLen = 50, bool required = false);
    InputForm& addNumberField(const std::string& name, const std::string& label, bool required = false);
    InputForm& addDecimalField(const std::string& name, const std::string& label, bool required = false);
    InputForm& addDateField(const std::string& name, const std::string& label, bool required = false);

    // Set custom validator for a field
    InputForm& setValidator(const std::string& fieldName, std::function<bool(const std::string&)> validator,
        const std::string& errorMessage = "Invalid input");

    // Set initial value for a field
    InputForm& setInitialValue(const std::string& fieldName, const std::string& value);

    // Configuration
    InputForm& setPosition(int x, int y);
    InputForm& setBorder(bool show);

    // Show form and get result
    FormResult show();

    // Get field count
    int getFieldCount() const { return static_cast<int>(fields.size()); }
};

#endif // INPUT_FORM_H
