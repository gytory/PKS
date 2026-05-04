#ifndef COPY_COMMAND_H
#define COPY_COMMAND_H

#include "Command.h"

class CopyCommand : public Command {
public:
    void execute(FileManager* manager) override;
};

#endif