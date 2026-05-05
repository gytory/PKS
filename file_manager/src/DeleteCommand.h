#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include "Command.h"

class DeleteCommand : public Command {
public:
    void execute(FileManager* manager) override;
};

#endif