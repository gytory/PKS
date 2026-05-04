#include "ConsoleManager.h"
#include <iostream>

ConsoleManager* ConsoleManager::instance = nullptr;

ConsoleManager::ConsoleManager() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

ConsoleManager* ConsoleManager::getInstance() {
    if (!instance) {
        instance = new ConsoleManager();
    }
    return instance;
}

void ConsoleManager::clearScreen() {
    system("cls");
}

void ConsoleManager::setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(consoleHandle, coord);
}

void ConsoleManager::showMessage(const std::string& msg) {
    setCursorPosition(0, 25);
    std::cout << msg << std::endl;
    Sleep(800);
}

void ConsoleManager::showMessageAt(int x, int y, const std::string& msg) {
    setCursorPosition(x, y);
    std::cout << msg;
}

void ConsoleManager::setColor(int color) {
    SetConsoleTextAttribute(consoleHandle, color);
}

void ConsoleManager::resetColor() {
    SetConsoleTextAttribute(consoleHandle, 7);
}

int ConsoleManager::getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int ConsoleManager::getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}