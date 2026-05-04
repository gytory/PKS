#ifndef OPEN_COMMAND_H
#define OPEN_COMMAND_H

#include "Command.h"

class OpenCommand : public Command {
public:
    void execute(FileManager* manager) override;
};

#endif