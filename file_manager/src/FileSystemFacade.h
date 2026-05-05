#ifndef FILESYSTEM_FACADE_H
#define FILESYSTEM_FACADE_H

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class FileSystemFacade {
public:
    bool copyFile(const fs::path& src, const fs::path& dst);
    bool moveFile(const fs::path& src, const fs::path& dst);
    bool deleteFile(const fs::path& path);
    bool openFile(const fs::path& path);
    bool isDirectory(const fs::path& path);
    bool isRegularFile(const fs::path& path);
    bool exists(const fs::path& path);
    std::string getFileName(const fs::path& path);
};

#endif