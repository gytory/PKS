#ifndef FILE_PANEL_H
#define FILE_PANEL_H

#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

class FilePanel {
private:
    fs::path currentPath;
    std::vector<fs::directory_entry> items;
    int selectedIndex;
    int x;
    int y;
    int width;
    int height;

    void sortItems();

public:
    FilePanel(const fs::path& startPath, int startX, int startY, int panelWidth, int panelHeight);
    void refresh();
    void moveUp();
    void moveDown();
    void enter();
    void goUp();
    fs::path getCurrentPath() const;
    fs::path getSelectedPath() const;
    std::string getSelectedFileName() const;
    bool isSelectedDirectory() const;
    bool isSelectedRegularFile() const;
    bool isSelectedParentDir() const;
    void display(bool isActive);
    void refreshAndDisplay(bool isActive);
};

#endif