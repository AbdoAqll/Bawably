#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <utility>

// Key codes for keyboard input
namespace Keys {
    constexpr int LEFT = 75;
    constexpr int RIGHT = 77;
    constexpr int HOME = 71;
    constexpr int END = 79;
    constexpr int DEL = 83;
    constexpr int BACKSPACE = 8;
    constexpr int ENTER = 13;
    constexpr int ESC = 27;
    constexpr int UP = 72;
    constexpr int DOWN = 80;
    constexpr int TAB = 9;
    constexpr int NULL_KEY = 0;
    constexpr int EXTENDED = 224;
    constexpr int EXTENDED2 = -32;
}

namespace Colors {
    constexpr int DEFAULT = 7;
    constexpr int HIGHLIGHT = 10;  // Green
    constexpr int SELECTED = 2;    // Dark Green
    constexpr int ERR = 12;        // Red
    constexpr int TITLE = 14;      // Yellow
    constexpr int LABEL = 11;      // Cyan
}

class ConsoleUtils {
public:
    static void initConsole();  // Initialize console settings (call once at startup)
    static void gotoxy(int x, int y);
    static void textattr(int color);
    static void hideCursor();
    static void showCursor();
    static void clearScreen();
    static void clearLine(int y, int startX = 0, int length = 80);
    static int getKey();  // Returns key code, handles extended keys
    static void setTitle(const std::string& title);
    static std::pair<int, int> getConsoleSize();
};

#endif // CONSOLE_UTILS_H
