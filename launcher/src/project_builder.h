#pragma once
#include <string>

class ProjectBuilder {
public:
    static bool CloneRepository();
    static bool ConfigureProject();
    static bool BuildProject();
    static std::string GetExecutablePath();
    static bool ExecutableExists();

private:
    static const std::string REPO_URL;
    static const std::string PROJECT_DIR;
    static const std::string BUILD_DIR;
    static const std::string EXE_PATH;
};
