#include "DeleteCommand.h"
#include "FileManager.h"

void DeleteCommand::execute(FileManager* manager) {
    manager->deleteSelected();
}