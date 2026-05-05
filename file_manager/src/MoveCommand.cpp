#include "MoveCommand.h"
#include "FileManager.h"

void MoveCommand::execute(FileManager* manager) {
    manager->moveBetweenPanels();
}