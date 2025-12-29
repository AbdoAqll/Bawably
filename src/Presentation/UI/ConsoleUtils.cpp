#include "ConsoleUtils.h"

using namespace std;

void ConsoleUtils::initConsole() {
    // Set console code page to 437 (DOS) for box-drawing characters
    SetConsoleOutputCP(437);
    SetConsoleCP(437);

    // Enable virtual terminal processing for better compatibility
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void ConsoleUtils::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ConsoleUtils::textattr(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ConsoleUtils::hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ConsoleUtils::showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ConsoleUtils::clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);

    // Fill the entire buffer with the current colors and attributes
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);

    // Move the cursor home
    SetConsoleCursorPosition(hConsole, homeCoords);

    // Also use ANSI escape codes to clear scrollback buffer
    cout << "\033[2J\033[3J\033[H" << flush;
}

void ConsoleUtils::clearLine(int y, int startX, int length) {
    gotoxy(startX, y);
    for (int i = 0; i < length; i++) {
        cout << ' ';
    }
    gotoxy(startX, y);
}

int ConsoleUtils::getKey() {
    int key = _getch();

    // Handle extended keys (arrow keys, home, end, delete, etc.)
    if (key == Keys::NULL_KEY || key == Keys::EXTENDED || key == Keys::EXTENDED2) {
        key = _getch();
        // Return negative values for extended keys to distinguish them
        return -key;
    }

    return key;
}

void ConsoleUtils::setTitle(const string& title) {
    SetConsoleTitleA(title.c_str());
}

pair<int, int> ConsoleUtils::getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return { width, height };
}
