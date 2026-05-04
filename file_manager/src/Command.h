#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class FileManager;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(FileManager* manager) = 0;
};

#endif