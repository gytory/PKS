#include "FileManager.h"
#include "ConsoleManager.h"
#include "FileSystemFacade.h"
#include "CopyCommand.h"
#include "MoveCommand.h"
#include "DeleteCommand.h"
#include "OpenCommand.h"
#include <conio.h>
#include <iostream>

FileManager::FileManager() : activePanel(0), running(true) {
    ConsoleManager* console = ConsoleManager::getInstance();
    console->clearScreen();
    
    int width = console->getConsoleWidth();
    int height = console->getConsoleHeight();
    panelWidth = (width - 4) / 2;
    panelHeight = height - 8;
    
    leftPanel = new FilePanel(fs::current_path(), 2, 2, panelWidth, panelHeight);
    rightPanel = new FilePanel(fs::current_path(), panelWidth + 4, 2, panelWidth, panelHeight);
}

FileManager::~FileManager() {
    delete leftPanel;
    delete rightPanel;
    for (Command* cmd : commandHistory) {
        delete cmd;
    }
    commandHistory.clear();
}

void FileManager::displayUI() {
    ConsoleManager* console = ConsoleManager::getInstance();
    console->clearScreen();
    
    console->setCursorPosition(0, 0);
    std::cout << "┌─────────────────────────────────────────────────────────────────────────────┐";
    console->setCursorPosition(0, 1);
    std::cout << "│                    TWO-PANEL FILE MANAGER                                   │";
    console->setCursorPosition(0, 2);
    std::cout << "├─────────────────────────────────────────────────────────────────────────────┤";
    
    leftPanel->display(activePanel == 0);
    rightPanel->display(activePanel == 1);
    
    console->setCursorPosition(0, panelHeight + 4);
    std::cout << "├─────────────────────────────────────────────────────────────────────────────┤";
    console->setCursorPosition(0, panelHeight + 5);
    std::cout << "│ [Tab] Switch panel | [C] Copy | [M] Move | [D] Delete | [Enter] Open | [Q] Quit │";
    console->setCursorPosition(0, panelHeight + 6);
    std::cout << "└─────────────────────────────────────────────────────────────────────────────┘";
    
    console->setCursorPosition(0, panelHeight + 8);
    std::cout << "Active: " << (activePanel == 0 ? "LEFT" : "RIGHT");
    console->setCursorPosition(0, panelHeight + 9);
    std::cout << "Path: " << getActivePanel()->getCurrentPath().string();
}

bool FileManager::confirmAction(const std::string& message) {
    ConsoleManager* console = ConsoleManager::getInstance();
    console->showMessage(message + " (y/n): ");
    int ch = _getch();
    return (ch == 'y' || ch == 'Y');
}

void FileManager::showError(const std::string& message) {
    ConsoleManager::getInstance()->showMessage("ERROR: " + message);
}

std::string FileManager::getUserInput() {
    std::string result;
    int ch = _getch();
    result += (char)ch;
    return result;
}

FilePanel* FileManager::getActivePanel() {
    return (activePanel == 0) ? leftPanel : rightPanel;
}

FilePanel* FileManager::getInactivePanel() {
    return (activePanel == 0) ? rightPanel : leftPanel;
}

void FileManager::copyBetweenPanels() {
    FilePanel* src = getActivePanel();
    FilePanel* dst = getInactivePanel();
    
    if (!src->isSelectedRegularFile()) {
        showError("Cannot copy directory. Select a file.");
        return;
    }
    
    fs::path sourcePath = src->getSelectedPath();
    fs::path targetPath = dst->getCurrentPath() / sourcePath.filename();
    
    if (!confirmAction("Copy " + sourcePath.filename().string() + "?")) {
        showError("Cancelled");
        return;
    }
    
    FileSystemFacade fs;
    if (fs.copyFile(sourcePath, targetPath)) {
        ConsoleManager::getInstance()->showMessage("Copied: " + sourcePath.filename().string());
        leftPanel->refresh();
        rightPanel->refresh();
    } else {
        showError("Copy failed");
    }
}

void FileManager::moveBetweenPanels() {
    FilePanel* src = getActivePanel();
    FilePanel* dst = getInactivePanel();
    
    if (!src->isSelectedRegularFile()) {
        showError("Cannot move directory. Select a file.");
        return;
    }
    
    fs::path sourcePath = src->getSelectedPath();
    fs::path targetPath = dst->getCurrentPath() / sourcePath.filename();
    
    if (!confirmAction("Move " + sourcePath.filename().string() + "?")) {
        showError("Cancelled");
        return;
    }
    
    FileSystemFacade fs;
    if (fs.moveFile(sourcePath, targetPath)) {
        ConsoleManager::getInstance()->showMessage("Moved: " + sourcePath.filename().string());
        leftPanel->refresh();
        rightPanel->refresh();
    } else {
        showError("Move failed");
    }
}

void FileManager::deleteSelected() {
    FilePanel* panel = getActivePanel();
    
    if (panel->isSelectedParentDir()) {
        showError("Cannot delete '..'");
        return;
    }
    
    if (!panel->isSelectedRegularFile()) {
        showError("Cannot delete directory. Select a file.");
        return;
    }
    
    fs::path targetPath = panel->getSelectedPath();
    
    if (!confirmAction("Delete " + targetPath.filename().string() + "?")) {
        showError("Cancelled");
        return;
    }
    
    FileSystemFacade fs;
    if (fs.deleteFile(targetPath)) {
        ConsoleManager::getInstance()->showMessage("Deleted: " + targetPath.filename().string());
        leftPanel->refresh();
        rightPanel->refresh();
    } else {
        showError("Delete failed");
    }
}

void FileManager::openSelected() {
    FilePanel* panel = getActivePanel();
    
    if (panel->isSelectedDirectory()) {
        panel->enter();
        leftPanel->refresh();
        rightPanel->refresh();
    } else if (panel->isSelectedRegularFile()) {
        FileSystemFacade fs;
        fs.openFile(panel->getSelectedPath());
        ConsoleManager::getInstance()->showMessage("Opening: " + panel->getSelectedFileName());
    } else {
        showError("Nothing selected");
    }
}

void FileManager::run() {
    ConsoleManager* console = ConsoleManager::getInstance();
    
    while (running) {
        displayUI();
        
        int ch = _getch();
        
        if (ch == 224) {
            ch = _getch();
            switch (ch) {
                case 72:
                    getActivePanel()->moveUp();
                    break;
                case 80:
                    getActivePanel()->moveDown();
                    break;
            }
        } else {
            switch (ch) {
                case 9:
                    activePanel = !activePanel;
                    break;
                case 13:
                    openSelected();
                    break;
                case 8:
                case 127:
                    getActivePanel()->goUp();
                    leftPanel->refresh();
                    rightPanel->refresh();
                    break;
                case 'C':
                case 'c':
                    copyBetweenPanels();
                    break;
                case 'M':
                case 'm':
                    moveBetweenPanels();
                    break;
                case 'D':
                case 'd':
                    deleteSelected();
                    break;
                case 'Q':
                case 'q':
                case 27:
                    if (confirmAction("Exit program?")) {
                        running = false;
                    }
                    break;
            }
        }
    }
    
    console->clearScreen();
    console->setCursorPosition(0, 0);
    std::cout << "Goodbye!" << std::endl;
}