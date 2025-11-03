#include "FileGenerator.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>

void FileGenerator::generateVariant12File(const std::string& filename, int count) {
    std::vector<std::string> operations;
    std::random_device rd;
    std::mt19937 gen(rd());

    int read0_count = (count * 20) / 100;
    int write0_count = (count * 5) / 100;
    int read1_count = (count * 20) / 100;
    int write1_count = (count * 5) / 100;
    int read2_count = (count * 10) / 100;
    int write2_count = (count * 20) / 100;
    int string_count = (count * 20) / 100;

    std::cout << "Variant file: " << filename << " - " << count << " operations" << std::endl;
    std::cout << "  read0=" << read0_count << ", write0=" << write0_count << std::endl;
    std::cout << "  read1=" << read1_count << ", write1=" << write1_count << std::endl;
    std::cout << "  read2=" << read2_count << ", write2=" << write2_count << std::endl;
    std::cout << "  string=" << string_count << std::endl;

    for (int i = 0; i < read0_count; i++) operations.push_back("read 0");
    for (int i = 0; i < write0_count; i++) operations.push_back("write 0 1");
    for (int i = 0; i < read1_count; i++) operations.push_back("read 1");
    for (int i = 0; i < write1_count; i++) operations.push_back("write 1 1");
    for (int i = 0; i < read2_count; i++) operations.push_back("read 2");
    for (int i = 0; i < write2_count; i++) operations.push_back("write 2 1");
    for (int i = 0; i < string_count; i++) operations.push_back("string");

    std::shuffle(operations.begin(), operations.end(), gen);
    writeOperationsToFile(filename, operations);
}

void FileGenerator::generateEqualFile(const std::string& filename, int count) {
    std::vector<std::string> operations;
    std::random_device rd;
    std::mt19937 gen(rd());

    int per_type = count / 7;

    std::cout << "Equal file: " << filename << " - " << count << " operations" << std::endl;
    std::cout << "  Each operation type: " << per_type << std::endl;

    for (int i = 0; i < per_type; i++) operations.push_back("read 0");
    for (int i = 0; i < per_type; i++) operations.push_back("write 0 1");
    for (int i = 0; i < per_type; i++) operations.push_back("read 1");
    for (int i = 0; i < per_type; i++) operations.push_back("write 1 1");
    for (int i = 0; i < per_type; i++) operations.push_back("read 2");
    for (int i = 0; i < per_type; i++) operations.push_back("write 2 1");
    for (int i = 0; i < per_type; i++) operations.push_back("string");

    std::shuffle(operations.begin(), operations.end(), gen);
    writeOperationsToFile(filename, operations);
}

void FileGenerator::generateWrongFile(const std::string& filename, int count) {
    std::vector<std::string> operations;
    std::random_device rd;
    std::mt19937 gen(rd());

    int write2_count = (count * 60) / 100;
    int string_count = (count * 30) / 100;
    int other_count = (count * 10) / 100;

    std::cout << "Wrong file: " << filename << " - " << count << " operations" << std::endl;
    std::cout << "  write2=" << write2_count << ", string=" << string_count
        << ", read0=" << other_count << std::endl;

    for (int i = 0; i < write2_count; i++) operations.push_back("write 2 1");
    for (int i = 0; i < string_count; i++) operations.push_back("string");
    for (int i = 0; i < other_count; i++) operations.push_back("read 0");

    std::shuffle(operations.begin(), operations.end(), gen);
    writeOperationsToFile(filename, operations);
}

void FileGenerator::writeOperationsToFile(const std::string& filename,
    const std::vector<std::string>& operations) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open file " << filename << std::endl;
        return;
    }

    for (const auto& op : operations) {
        file << op << "\n";
    }
    file.close();

    std::cout << "  Written " << operations.size() << " operations to " << filename << std::endl;
}