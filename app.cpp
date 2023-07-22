#include "include/filefinder.h"
#include <future> 
#include <thread> 

int main(int argc, char*  argv[]) {
    std::string targetFileName;
    if(argc > 1){
        targetFileName = argv[1];
    }
    else{
        std::cout << "Enter the file name to search for: ";
        std::cin >> targetFileName;
    }
    std::filesystem::path rootPath = "/"; 
    directoriesToSearch.push(rootPath);

    std::atomic<bool> stopFlag = false; 
    std::atomic<int> threadsStopped = 0;

    auto future = std::async(std::launch::async, searchFile, targetFileName, std::ref(stopFlag), std::ref(threadsStopped));

    std::chrono::seconds timeout(5);
    if (future.wait_for(timeout) == std::future_status::timeout) {
        stopFlag = true; 
        std::this_thread::yield(); 
        if (threadsStopped < MAX_THREADS) {
            future.wait();
        }
        std::cout << "File not found: " << targetFileName << std::endl;
    } else {
        stopFlag = true; 
    }

    return 0;
}
