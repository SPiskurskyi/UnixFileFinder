#include "../include/task.h"

std::mutex mtx;
std::queue<std::filesystem::path> directoriesToSearch;

void searchFile(const std::string& target, std::atomic<bool>& stopFlag, std::atomic<int>& threadsStopped) {
    while (!directoriesToSearch.empty() && !stopFlag) {
        std::filesystem::path currentPath;
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (directoriesToSearch.empty()) {
                break;
            }
            currentPath = directoriesToSearch.front();
            directoriesToSearch.pop();
        }

        try {
            for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
                if (stopFlag) return; 

                if (entry.is_directory()) {
                    std::lock_guard<std::mutex> lock(mtx);
                    directoriesToSearch.push(entry.path());
                } else if (entry.is_regular_file() && entry.path().filename() == target) {
                    std::cout << "File found: " << entry.path() << std::endl;
                    stopFlag = true; 
                    threadsStopped++;
                    return;
                }
            }
        } catch (const std::exception& ex) {
        }
    }

    threadsStopped++;
}

