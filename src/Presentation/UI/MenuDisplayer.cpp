#include "MenuDisplayer.h"
#include "ConsoleUtils.h"
#include <algorithm>

using namespace std;

MenuDisplayer::MenuDisplayer(const string& title, const vector<string>& itemLabels)
    : title(title), selected(0), startX(2), startY(1), showBorder(true), clearOnShow(true) {
    for (const auto& label : itemLabels) {
        items.emplace_back(label);
    }
}

MenuDisplayer::MenuDisplayer(const string& title, const vector<MenuItem>& items)
    : title(title), items(items), selected(0), startX(2), startY(1), showBorder(true), clearOnShow(true) {
}

int MenuDisplayer::getMaxWidth() const {
    int maxWidth = static_cast<int>(title.length());
    for (const auto& item : items) {
        maxWidth = max(maxWidth, static_cast<int>(item.label.length()));
    }
    return maxWidth + 4;  // Padding for "> " and spacing
}

void MenuDisplayer::drawBorder(int width, int height) {
    ConsoleUtils::textattr(Colors::DEFAULT);

    // Top border
    ConsoleUtils::gotoxy(startX - 1, startY - 1);
    cout << char(201);  // ╔
    for (int i = 0; i < width; i++) cout << char(205);  // ═
    cout << char(187);  // ╗

    // Side borders
    for (int i = 0; i < height; i++) {
        ConsoleUtils::gotoxy(startX - 1, startY + i);
        cout << char(186);  // ║
        ConsoleUtils::gotoxy(startX + width, startY + i);
        cout << char(186);  // ║
    }

    // Bottom border
    ConsoleUtils::gotoxy(startX - 1, startY + height);
    cout << char(200);  // ╚
    for (int i = 0; i < width; i++) cout << char(205);  // ═
    cout << char(188);  // ╝
}

void MenuDisplayer::draw() {
    int width = getMaxWidth();
    int height = static_cast<int>(items.size()) + 2;  // +2 for title and spacing

    if (showBorder) {
        drawBorder(width, height);
    }

    ConsoleUtils::gotoxy(startX, startY);
    ConsoleUtils::textattr(Colors::TITLE);
    cout << title;

    ConsoleUtils::gotoxy(startX, startY + 1);
    ConsoleUtils::textattr(Colors::DEFAULT);
    for (int i = 0; i < width - 1; i++) cout << char(196);  

    for (int i = 0; i < static_cast<int>(items.size()); i++) {
        ConsoleUtils::gotoxy(startX, startY + 2 + i);

        if (!items[i].enabled) {
            ConsoleUtils::textattr(8);  
            cout << "  " << items[i].label;
        }
        else if (i == selected) {
            ConsoleUtils::textattr(Colors::SELECTED);
            cout << "> " << items[i].label;
        }
        else {
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "  " << items[i].label;
        }

        // Clear rest of line
        for (int j = static_cast<int>(items[i].label.length()) + 2; j < width - 1; j++) {
            cout << ' ';
        }
    }

    // Draw instructions
    ConsoleUtils::gotoxy(startX, startY + height + 1);
    ConsoleUtils::textattr(Colors::DEFAULT);
    cout << "UP/DOWN: Navigate | ENTER: Select | ESC: Back";

    ConsoleUtils::textattr(Colors::DEFAULT);
}

int MenuDisplayer::show() {
    if (clearOnShow) {
        ConsoleUtils::clearScreen();
    }
    ConsoleUtils::hideCursor();

    // Find first enabled item
    while (selected < static_cast<int>(items.size()) && !items[selected].enabled) {
        selected++;
    }
    if (selected >= static_cast<int>(items.size())) {
        selected = 0;
    }

    while (true) {
        draw();

        int key = ConsoleUtils::getKey();

        // Handle extended keys (negative values from getKey)
        if (key < 0) {
            key = -key;  // Convert back to positive
            switch (key) {
            case Keys::UP: {
                int original = selected;
                do {
                    selected--;
                    if (selected < 0) selected = static_cast<int>(items.size()) - 1;
                } while (!items[selected].enabled && selected != original);
                break;
            }
            case Keys::DOWN: {
                int original = selected;
                do {
                    selected++;
                    if (selected >= static_cast<int>(items.size())) selected = 0;
                } while (!items[selected].enabled && selected != original);
                break;
            }
            case Keys::HOME: {
                selected = 0;
                while (selected < static_cast<int>(items.size()) && !items[selected].enabled) {
                    selected++;
                }
                break;
            }
            case Keys::END: {
                selected = static_cast<int>(items.size()) - 1;
                while (selected >= 0 && !items[selected].enabled) {
                    selected--;
                }
                break;
            }
            }
        }
        else {
            switch (key) {
            case Keys::ENTER:
                if (items[selected].enabled) {
                    // Execute callback if provided
                    if (items[selected].action) {
                        items[selected].action();
                    }
                    ConsoleUtils::showCursor();
                    return selected;
                }
                break;
            case Keys::ESC:
                ConsoleUtils::showCursor();
                return -1;
            }

            // Number shortcuts (1-9)
            if (key >= '1' && key <= '9') {
                int index = key - '1';
                if (index < static_cast<int>(items.size()) && items[index].enabled) {
                    selected = index;
                    if (items[selected].action) {
                        items[selected].action();
                    }
                    ConsoleUtils::showCursor();
                    return selected;
                }
            }
        }
    }
}

MenuDisplayer& MenuDisplayer::setPosition(int x, int y) {
    startX = x;
    startY = y;
    return *this;
}

MenuDisplayer& MenuDisplayer::setBorder(bool show) {
    showBorder = show;
    return *this;
}

MenuDisplayer& MenuDisplayer::setClearOnShow(bool clear) {
    clearOnShow = clear;
    return *this;
}

MenuDisplayer& MenuDisplayer::setSelected(int index) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        selected = index;
    }
    return *this;
}

void MenuDisplayer::setItemEnabled(int index, bool enabled) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        items[index].enabled = enabled;
    }
}

void MenuDisplayer::setItemLabel(int index, const string& label) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        items[index].label = label;
    }
}
