#include <filesystem>
#include <iostream>

namespace ikura {

std::filesystem::path
createResourceDirectoryPath(std::filesystem::path subPath);

#ifdef __linux__
// subPath is NOT starts with '/'
// ex) "dirA/dirB/aaa.txt", "dirA/destinationDir"
std::filesystem::path
createResourceDirectoryPath(std::filesystem::path subPath) {
    std::filesystem::path homeDir = getenv("HOME");
    std::filesystem::path resourceDir = homeDir / ".local" / "share" / "ikura";
    std::filesystem::path destinationPath = resourceDir / subPath;

    return destinationPath;
}
#endif
} // namespace ikura