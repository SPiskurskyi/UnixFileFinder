#pragma once

#include <iostream>
#include <filesystem>
#include <queue>
#include <atomic>
#include <mutex>

const int MAX_THREADS = 8;
extern std::queue<std::filesystem::path> directoriesToSearch;

void searchFile(const std::string& target, std::atomic<bool>& stopFlag, std::atomic<int>& threadsStopped);
