#include "FileSystemFacade.h"
#include <filesystem>
#include <windows.h>
#include <shellapi.h>

namespace fs = std::filesystem;

bool FileSystemFacade::copyFile(const fs::path& src, const fs::path& dst) {
    try {
        fs::copy(src, dst, fs::copy_options::overwrite_existing);
        return true;
    } catch (...) {
        return false;
    }
}

bool FileSystemFacade::moveFile(const fs::path& src, const fs::path& dst) {
    try {
        fs::rename(src, dst);
        return true;
    } catch (...) {
        return false;
    }
}

bool FileSystemFacade::deleteFile(const fs::path& path) {
    try {
        return fs::remove(path);
    } catch (...) {
        return false;
    }
}

bool FileSystemFacade::openFile(const fs::path& path) {
    ShellExecuteA(NULL, "open", path.string().c_str(), NULL, NULL, SW_SHOW);
    return true;
}

bool FileSystemFacade::isDirectory(const fs::path& path) {
    try {
        return fs::is_directory(path);
    } catch (...) {
        return false;
    }
}

bool FileSystemFacade::isRegularFile(const fs::path& path) {
    try {
        return fs::is_regular_file(path);
    } catch (...) {
        return false;
    }
}

bool FileSystemFacade::exists(const fs::path& path) {
    try {
        return fs::exists(path);
    } catch (...) {
        return false;
    }
}

std::string FileSystemFacade::getFileName(const fs::path& path) {
    return path.filename().string();
}