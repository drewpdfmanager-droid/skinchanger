#include "downloader.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>

#pragma comment(lib, "wininet.lib")

bool Downloader::FileExists(const std::string& path) {
    return fs::exists(path);
}

long long Downloader::GetFileSize(const std::string& path) {
    if (!fs::exists(path)) return -1;
    return fs::file_size(path);
}

bool Downloader::DownloadFile(const std::string& url, const std::string& savePath) {
    std::cout << "[Downloader] Downloading: " << url << std::endl;
    std::cout << "[Downloader] Saving to: " << savePath << std::endl;

    HINTERNET hInternet = InternetOpenA("LauncherBot/1.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        std::cerr << "[Downloader] Failed to open internet" << std::endl;
        return false;
    }

    HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        std::cerr << "[Downloader] Failed to open URL" << std::endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    FILE* file = fopen(savePath.c_str(), "wb");
    if (!file) {
        std::cerr << "[Downloader] Failed to create file" << std::endl;
        InternetCloseHandle(hUrl);
        InternetCloseHandle(hInternet);
        return false;
    }

    char buffer[4096];
    DWORD bytesRead = 0;
    long long totalBytes = 0;

    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead)) {
        if (bytesRead == 0) break;
        fwrite(buffer, 1, bytesRead, file);
        totalBytes += bytesRead;
    }

    fclose(file);
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    std::cout << "[Downloader] Downloaded " << totalBytes << " bytes" << std::endl;
    return true;
}

bool Downloader::DownloadFileWithProgress(const std::string& url, const std::string& savePath,
    void (*progressCallback)(int progress)) {
    if (!progressCallback) return DownloadFile(url, savePath);

    std::cout << "[Downloader] Downloading with progress: " << url << std::endl;

    HINTERNET hInternet = InternetOpenA("LauncherBot/1.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return false;

    HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        InternetCloseHandle(hInternet);
        return false;
    }

    FILE* file = fopen(savePath.c_str(), "wb");
    if (!file) {
        InternetCloseHandle(hUrl);
        InternetCloseHandle(hInternet);
        return false;
    }

    char buffer[4096];
    DWORD bytesRead = 0;
    long long totalBytes = 0;
    long long fileSize = 1;  // Default to 1 to avoid division by zero

    // Try to get file size from HTTP header
    char szSize[32] = {0};
    DWORD dwSize = sizeof(szSize);
    if (HttpQueryInfoA((HINTERNET)hUrl, HTTP_QUERY_CONTENT_LENGTH, szSize, &dwSize, NULL)) {
        fileSize = atoll(szSize);
    }

    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead)) {
        if (bytesRead == 0) break;
        fwrite(buffer, 1, bytesRead, file);
        totalBytes += bytesRead;
        
        int progress = (int)((totalBytes * 100) / fileSize);
        if (progress > 100) progress = 100;
        progressCallback(progress);
    }

    progressCallback(100);
    fclose(file);
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    return true;
}
