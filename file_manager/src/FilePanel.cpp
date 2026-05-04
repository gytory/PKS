#include "FilePanel.h"
#include "ConsoleManager.h"
#include <algorithm>
#include <iostream>

FilePanel::FilePanel(const fs::path& startPath, int startX, int startY, int panelWidth, int panelHeight)
    : currentPath(startPath), selectedIndex(0), x(startX), y(startY), width(panelWidth), height(panelHeight) {
    refresh();
}

void FilePanel::sortItems() {
    std::sort(items.begin(), items.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
        bool aIsDir = a.is_directory();
        bool bIsDir = b.is_directory();
        if (aIsDir != bIsDir) {
            return aIsDir > bIsDir;
        }
        return a.path().filename().string() < b.path().filename().string();
    });
}

void FilePanel::refresh() {
    items.clear();
    if (currentPath.has_parent_path()) {
        items.push_back(fs::directory_entry(fs::path("..")));
    }
    try {
        for (const auto& entry : fs::directory_iterator(currentPath)) {
            items.push_back(entry);
        }
    } catch (...) {
        ConsoleManager::getInstance()->showMessage("Cannot read directory");
    }
    sortItems();
    if (selectedIndex >= (int)items.size()) {
        selectedIndex = 0;
    }
}

void FilePanel::moveUp() {
    if (selectedIndex > 0) {
        selectedIndex--;
    }
}

void FilePanel::moveDown() {
    if (selectedIndex < (int)items.size() - 1) {
        selectedIndex++;
    }
}

void FilePanel::enter() {
    if (selectedIndex >= (int)items.size()) return;
    
    std::string selectedName = items[selectedIndex].path().filename().string();
    
    if (selectedName == "..") {
        goUp();
    } else if (items[selectedIndex].is_directory()) {
        currentPath = items[selectedIndex].path();
        selectedIndex = 0;
        refresh();
    }
}

void FilePanel::goUp() {
    if (currentPath.has_parent_path()) {
        currentPath = currentPath.parent_path();
        selectedIndex = 0;
        refresh();
    }
}

fs::path FilePanel::getCurrentPath() const {
    return currentPath;
}

fs::path FilePanel::getSelectedPath() const {
    if (selectedIndex < (int)items.size()) {
        return items[selectedIndex].path();
    }
    return currentPath;
}

std::string FilePanel::getSelectedFileName() const {
    if (selectedIndex < (int)items.size()) {
        return items[selectedIndex].path().filename().string();
    }
    return "";
}

bool FilePanel::isSelectedDirectory() const {
    if (selectedIndex < (int)items.size()) {
        return items[selectedIndex].is_directory();
    }
    return false;
}

bool FilePanel::isSelectedRegularFile() const {
    if (selectedIndex < (int)items.size()) {
        return items[selectedIndex].is_regular_file();
    }
    return false;
}

bool FilePanel::isSelectedParentDir() const {
    if (selectedIndex < (int)items.size()) {
        return items[selectedIndex].path().filename().string() == "..";
    }
    return false;
}

void FilePanel::display(bool isActive) {
    ConsoleManager* console = ConsoleManager::getInstance();
    
    console->setCursorPosition(x, y);
    std::string pathStr = currentPath.string();
    if (pathStr.length() > (size_t)width - 5) {
        pathStr = "..." + pathStr.substr(pathStr.length() - (width - 8));
    }
    std::cout << " " << pathStr;
    for (int i = (int)pathStr.length(); i < width - 1; i++) std::cout << " ";
    
    for (int i = 0; i < height && i < (int)items.size(); i++) {
        console->setCursorPosition(x, y + 1 + i);
        
        if (isActive && i == selectedIndex) {
            console->setColor(10);
            std::cout << ">";
        } else {
            console->resetColor();
            std::cout << " ";
        }
        
        std::string name = items[i].path().filename().string();
        if (name == "..") {
            name = "[..]";
        } else if (items[i].is_directory()) {
            name = "[" + name + "]";
        }
        
        if (name.length() > (size_t)width - 3) {
            name = name.substr(0, width - 6) + "...";
        }
        
        std::cout << " " << name;
        for (size_t j = name.length(); j < (size_t)width - 2; j++) std::cout << " ";
        
        console->resetColor();
    }
    
    for (int i = (int)items.size(); i < height; i++) {
        console->setCursorPosition(x, y + 1 + i);
        std::cout << " ";
        for (int j = 0; j < width - 2; j++) std::cout << " ";
    }
}

void FilePanel::refreshAndDisplay(bool isActive) {
    refresh();
    display(isActive);
}