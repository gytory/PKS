#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "FilePanel.h"
#include "Command.h"
#include <vector>

class FileManager {
private:
    FilePanel* leftPanel;
    FilePanel* rightPanel;
    int activePanel;
    bool running;
    int panelWidth;
    int panelHeight;
    std::vector<Command*> commandHistory;

    void displayUI();
    bool confirmAction(const std::string& message);
    void showError(const std::string& message);
    std::string getUserInput();

public:
    FileManager();
    ~FileManager();
    void run();
    void copyBetweenPanels();
    void moveBetweenPanels();
    void deleteSelected();
    void openSelected();
    FilePanel* getActivePanel();
    FilePanel* getInactivePanel();
};

#endif