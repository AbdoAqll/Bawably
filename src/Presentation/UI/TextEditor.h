#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <string>
#include <functional>

// Input validation types
enum class InputType {
    ANY,           // Any printable character
    ALPHA,         // Letters only (a-z, A-Z)
    NUMERIC,       // Numbers only (0-9)
    ALPHANUMERIC,  // Letters and numbers
    DECIMAL,       // Numbers with decimal point
    DATE,          // Date format (YYYY-MM-DD)
    CUSTOM         // Custom range
};

// Single line text editor for individual field input
class SingleLineEditor {
private:
    std::string value;
    std::string label;
    int maxLen;
    int startX, startY;
    int cursorPos;
    char rangeStart, rangeEnd;
    InputType inputType;
    bool showLabel;
    std::function<bool(char)> customValidator;

    void draw();
    bool isValidChar(char c) const;
    void insertChar(char c);
    void deleteChar();
    void backspaceChar();

public:
    SingleLineEditor(const std::string& label = "", int maxLen = 50);

    // Show editor and return the entered value (empty if cancelled)
    std::string show();

    // Configuration methods (fluent interface)
    SingleLineEditor& setPosition(int x, int y);
    SingleLineEditor& setInputType(InputType type);
    SingleLineEditor& setCustomRange(char start, char end);
    SingleLineEditor& setCustomValidator(std::function<bool(char)> validator);
    SingleLineEditor& setInitialValue(const std::string& val);
    SingleLineEditor& setShowLabel(bool show);
    SingleLineEditor& setMaxLength(int len);

    // Get value without showing
    std::string getValue() const { return value; }

    // Clear value
    void clear() { value.clear(); cursorPos = 0; }
};

#endif // TEXT_EDITOR_H
