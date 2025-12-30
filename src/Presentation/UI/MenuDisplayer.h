#ifndef MENU_DISPLAYER_H
#define MENU_DISPLAYER_H

#include <vector>
#include <string>
#include <functional>

// Menu item with optional callback
struct MenuItem {
    std::string label;
    std::function<void()> action;  // Optional action to execute
    bool enabled;

    MenuItem(const std::string& label, std::function<void()> action = nullptr, bool enabled = true)
        : label(label), action(action), enabled(enabled) {
    }
};

class MenuDisplayer {
private:
    std::string title;
    std::vector<MenuItem> items;
    int selected;
    int startX, startY;
    bool showBorder;
    bool clearOnShow;

    void draw();
    void drawBorder(int width, int height);
    int getMaxWidth() const;

public:
    // Constructor with simple string items
    MenuDisplayer(const std::string& title, const std::vector<std::string>& itemLabels);

    // Constructor with MenuItem objects (for callbacks and enabled states)
    MenuDisplayer(const std::string& title, const std::vector<MenuItem>& items);

    // Show menu and return selected index (-1 if escaped)
    int show();

    // Configuration methods (fluent interface)
    MenuDisplayer& setPosition(int x, int y);
    MenuDisplayer& setBorder(bool show);
    MenuDisplayer& setClearOnShow(bool clear);
    MenuDisplayer& setSelected(int index);

    // Enable/disable items dynamically
    void setItemEnabled(int index, bool enabled);
    void setItemLabel(int index, const std::string& label);

    // Get current selection without showing
    int getSelected() const { return selected; }

    // Get item count
    int getItemCount() const { return static_cast<int>(items.size()); }
};

#endif // MENU_DISPLAYER_H
