#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

#include <string>
#include <windows.h>

class ConsoleManager {
private:
    ConsoleManager();
    static ConsoleManager* instance;
    HANDLE consoleHandle;

public:
    static ConsoleManager* getInstance();
    void clearScreen();
    void setCursorPosition(int x, int y);
    void showMessage(const std::string& msg);
    void showMessageAt(int x, int y, const std::string& msg);
    void setColor(int color);
    void resetColor();
    int getConsoleWidth();
    int getConsoleHeight();

    ConsoleManager(const ConsoleManager&) = delete;
    ConsoleManager& operator=(const ConsoleManager&) = delete;
};

#endif