#include "Executor.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <iostream>

std::vector<std::string> Executor::loadOperations(const std::string& filename) {
    std::vector<std::string> operations;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open file " << filename << std::endl;
        return operations;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            operations.push_back(line);
        }
    }
    file.close();

    std::cout << "Loaded " << operations.size() << " operations from " << filename << std::endl;
    return operations;
}

void Executor::executeOperations(DataStructure& ds,
    const std::vector<std::string>& operations) {
    for (const auto& op : operations) {
        std::istringstream iss(op);
        std::string command;
        iss >> command;

        if (command == "read") {
            int field;
            iss >> field;
            ds.read(field);
        }
        else if (command == "write") {
            int field, value;
            iss >> field >> value;
            ds.write(field, value);
        }
        else if (command == "string") {
            ds.toString();
        }
    }
}

double Executor::executeFile(DataStructure& ds, const std::string& filename) {
    auto operations = loadOperations(filename);

    if (operations.empty()) {
        std::cerr << "ERROR: No operations loaded from " << filename << std::endl;
        return 0.0;
    }

    std::cout << "Executing " << operations.size() << " operations (single thread)..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    executeOperations(ds, operations);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

double Executor::executeMultiThreaded(DataStructure& ds,
    const std::vector<std::string>& filenames) {
    std::vector<std::thread> threads;
    std::vector<std::vector<std::string>> all_operations;

    for (const auto& filename : filenames) {
        auto ops = loadOperations(filename);
        if (!ops.empty()) {
            all_operations.push_back(ops);
        }
    }

    if (all_operations.empty()) {
        std::cerr << "ERROR: No operations loaded" << std::endl;
        return 0.0;
    }

    int total_ops = 0;
    for (const auto& ops : all_operations) {
        total_ops += ops.size();
    }
    std::cout << "Executing " << total_ops << " operations ("
        << all_operations.size() << " threads)..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& operations : all_operations) {
        threads.emplace_back([&ds, operations]() {
            for (const auto& op : operations) {
                std::istringstream iss(op);
                std::string command;
                iss >> command;

                if (command == "read") {
                    int field;
                    iss >> field;
                    ds.read(field);
                }
                else if (command == "write") {
                    int field, value;
                    iss >> field >> value;
                    ds.write(field, value);
                }
                else if (command == "string") {
                    ds.toString();
                }
            }
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}