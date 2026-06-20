#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class Downloader {
public:
    static bool FileExists(const std::string& path);
    static long long GetFileSize(const std::string& path);
    static bool DownloadFile(const std::string& url, const std::string& savePath);
    static bool DownloadFileWithProgress(const std::string& url, const std::string& savePath,
        void (*progressCallback)(int progress));
};
