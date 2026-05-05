#include "FileManager.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    FileManager app;
    app.run();
    return 0;
}