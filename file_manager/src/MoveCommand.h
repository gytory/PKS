#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.h"

class MoveCommand : public Command {
public:
    void execute(FileManager* manager) override;
};

#endif