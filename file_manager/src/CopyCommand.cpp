#include "CopyCommand.h"
#include "FileManager.h"

void CopyCommand::execute(FileManager* manager) {
    manager->copyBetweenPanels();
}