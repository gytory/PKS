#include "OpenCommand.h"
#include "FileManager.h"

void OpenCommand::execute(FileManager* manager) {
    manager->openSelected();
}