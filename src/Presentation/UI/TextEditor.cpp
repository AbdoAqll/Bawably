#include "TextEditor.h"
#include "ConsoleUtils.h"

using namespace std;

SingleLineEditor::SingleLineEditor(const string& label, int maxLen)
    : label(label), maxLen(maxLen), startX(2), startY(1), cursorPos(0),
    rangeStart(' '), rangeEnd('~'), inputType(InputType::ANY), showLabel(true) {
}

bool SingleLineEditor::isValidChar(char c) const {
    // First check custom validator if set
    if (customValidator && !customValidator(c)) {
        return false;
    }

    switch (inputType) {
    case InputType::ALPHA:
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ';
    case InputType::NUMERIC:
        return (c >= '0' && c <= '9');
    case InputType::ALPHANUMERIC:
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == ' ';
    case InputType::DECIMAL:
        return (c >= '0' && c <= '9') || c == '.' || c == '-';
    case InputType::DATE:
        return (c >= '0' && c <= '9') || c == '-';
    case InputType::CUSTOM:
        return c >= rangeStart && c <= rangeEnd;
    case InputType::ANY:
    default:
        return c >= ' ' && c <= '~';  // Printable ASCII
    }
}

void SingleLineEditor::insertChar(char c) {
    if (static_cast<int>(value.length()) >= maxLen) return;

    value.insert(cursorPos, 1, c);
    cursorPos++;
}

void SingleLineEditor::deleteChar() {
    if (cursorPos >= static_cast<int>(value.length())) return;
    value.erase(cursorPos, 1);
}

void SingleLineEditor::backspaceChar() {
    if (cursorPos == 0) return;
    cursorPos--;
    value.erase(cursorPos, 1);
}

void SingleLineEditor::draw() {
    int labelOffset = 0;

    // Draw label if enabled
    if (showLabel && !label.empty()) {
        ConsoleUtils::gotoxy(startX, startY);
        ConsoleUtils::textattr(Colors::LABEL);
        cout << label << ": ";
        labelOffset = static_cast<int>(label.length()) + 2;
    }

    // Draw input field
    ConsoleUtils::gotoxy(startX + labelOffset, startY);

    for (int i = 0; i < maxLen; i++) {
        bool isCursor = (i == cursorPos);
        ConsoleUtils::textattr(isCursor ? Colors::HIGHLIGHT : Colors::DEFAULT);

        if (i < static_cast<int>(value.length())) {
            cout << value[i];
        }
        else {
            cout << '_';
        }
    }

    // Draw cursor indicator below
    ConsoleUtils::gotoxy(startX + labelOffset, startY + 1);
    for (int i = 0; i < maxLen; i++) {
        if (i == cursorPos) {
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << '^';
        }
        else {
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << ' ';
        }
    }

    ConsoleUtils::textattr(Colors::DEFAULT);
}

string SingleLineEditor::show() {
    ConsoleUtils::hideCursor();

    while (true) {
        draw();

        int key = ConsoleUtils::getKey();

        // Handle extended keys
        if (key < 0) {
            key = -key;
            switch (key) {
            case Keys::LEFT:
                if (cursorPos > 0) cursorPos--;
                break;
            case Keys::RIGHT:
                if (cursorPos < static_cast<int>(value.length())) cursorPos++;
                break;
            case Keys::HOME:
                cursorPos = 0;
                break;
            case Keys::END:
                cursorPos = static_cast<int>(value.length());
                break;
            case Keys::DEL:
                deleteChar();
                break;
            }
        }
        else {
            switch (key) {
            case Keys::BACKSPACE:
                backspaceChar();
                break;
            case Keys::ENTER:
            case Keys::TAB:
                ConsoleUtils::showCursor();
                return value;
            case Keys::ESC:
                ConsoleUtils::showCursor();
                return "";  // Return empty on escape
            default:
                if (isValidChar(static_cast<char>(key))) {
                    insertChar(static_cast<char>(key));
                }
                break;
            }
        }
    }
}

SingleLineEditor& SingleLineEditor::setPosition(int x, int y) {
    startX = x;
    startY = y;
    return *this;
}

SingleLineEditor& SingleLineEditor::setInputType(InputType type) {
    inputType = type;
    return *this;
}

SingleLineEditor& SingleLineEditor::setCustomRange(char start, char end) {
    rangeStart = start;
    rangeEnd = end;
    inputType = InputType::CUSTOM;
    return *this;
}

SingleLineEditor& SingleLineEditor::setCustomValidator(function<bool(char)> validator) {
    customValidator = validator;
    return *this;
}

SingleLineEditor& SingleLineEditor::setInitialValue(const string& val) {
    value = val.substr(0, maxLen);
    cursorPos = static_cast<int>(value.length());
    return *this;
}

SingleLineEditor& SingleLineEditor::setShowLabel(bool show) {
    showLabel = show;
    return *this;
}

SingleLineEditor& SingleLineEditor::setMaxLength(int len) {
    maxLen = len;
    if (static_cast<int>(value.length()) > maxLen) {
        value = value.substr(0, maxLen);
    }
    if (cursorPos > maxLen) {
        cursorPos = maxLen;
    }
    return *this;
}
