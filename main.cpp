#include "DataStructure.h"
#include "FileGenerator.h"
#include "Executor.h"
#include <iostream>
#include <iomanip>
#include <direct.h>

int main() {
    _mkdir("generated_files");

    const int OPERATIONS_COUNT = 10000; 

    std::cout << "=== Generating Files ===" << std::endl << std::endl;

    // Генеруємо файли для 1 потоку
    std::cout << "--- 1 Thread Files ---" << std::endl;
    FileGenerator::generateVariant12File("generated_files/variant_1thread.txt", OPERATIONS_COUNT);
    FileGenerator::generateEqualFile("generated_files/equal_1thread.txt", OPERATIONS_COUNT);
    FileGenerator::generateWrongFile("generated_files/wrong_1thread.txt", OPERATIONS_COUNT);
    std::cout << std::endl;

    // Генеруємо файли для 2 потоків
    std::cout << "--- 2 Thread Files ---" << std::endl;
    FileGenerator::generateVariant12File("generated_files/variant_2thread_1.txt", OPERATIONS_COUNT / 2);
    FileGenerator::generateVariant12File("generated_files/variant_2thread_2.txt", OPERATIONS_COUNT / 2);
    FileGenerator::generateEqualFile("generated_files/equal_2thread_1.txt", OPERATIONS_COUNT / 2);
    FileGenerator::generateEqualFile("generated_files/equal_2thread_2.txt", OPERATIONS_COUNT / 2);
    FileGenerator::generateWrongFile("generated_files/wrong_2thread_1.txt", OPERATIONS_COUNT / 2);
    FileGenerator::generateWrongFile("generated_files/wrong_2thread_2.txt", OPERATIONS_COUNT / 2);
    std::cout << std::endl;

    // Генеруємо файли для 3 потоків
    std::cout << "--- 3 Thread Files ---" << std::endl;
    FileGenerator::generateVariant12File("generated_files/variant_3thread_1.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateVariant12File("generated_files/variant_3thread_2.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateVariant12File("generated_files/variant_3thread_3.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateEqualFile("generated_files/equal_3thread_1.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateEqualFile("generated_files/equal_3thread_2.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateEqualFile("generated_files/equal_3thread_3.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateWrongFile("generated_files/wrong_3thread_1.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateWrongFile("generated_files/wrong_3thread_2.txt", OPERATIONS_COUNT / 3);
    FileGenerator::generateWrongFile("generated_files/wrong_3thread_3.txt", OPERATIONS_COUNT / 3);

    std::cout << "\n=== Files Generated Successfully! ===" << std::endl << std::endl;

    std::cout << "=== Running Tests ===" << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    double results[3][3] = { 0 };

    // 1 потік
    std::cout << "--- Testing 1 Thread ---" << std::endl;
    {
        DataStructure ds;
        results[0][0] = Executor::executeFile(ds, "generated_files/variant_1thread.txt");
        std::cout << "Variant: " << results[0][0] << " ms" << std::endl;

        results[0][1] = Executor::executeFile(ds, "generated_files/equal_1thread.txt");
        std::cout << "Equal: " << results[0][1] << " ms" << std::endl;

        results[0][2] = Executor::executeFile(ds, "generated_files/wrong_1thread.txt");
        std::cout << "Wrong: " << results[0][2] << " ms" << std::endl << std::endl;
    }

    // 2 потоки
    std::cout << "--- Testing 2 Threads ---" << std::endl;
    {
        DataStructure ds;
        results[1][0] = Executor::executeMultiThreaded(ds, {
            "generated_files/variant_2thread_1.txt",
            "generated_files/variant_2thread_2.txt"
            });
        std::cout << "Variant: " << results[1][0] << " ms" << std::endl;

        results[1][1] = Executor::executeMultiThreaded(ds, {
            "generated_files/equal_2thread_1.txt",
            "generated_files/equal_2thread_2.txt"
            });
        std::cout << "Equal: " << results[1][1] << " ms" << std::endl;

        results[1][2] = Executor::executeMultiThreaded(ds, {
            "generated_files/wrong_2thread_1.txt",
            "generated_files/wrong_2thread_2.txt"
            });
        std::cout << "Wrong: " << results[1][2] << " ms" << std::endl << std::endl;
    }

    // 3 потоки
    std::cout << "--- Testing 3 Threads ---" << std::endl;
    {
        DataStructure ds;
        results[2][0] = Executor::executeMultiThreaded(ds, {
            "generated_files/variant_3thread_1.txt",
            "generated_files/variant_3thread_2.txt",
            "generated_files/variant_3thread_3.txt"
            });
        std::cout << "Variant: " << results[2][0] << " ms" << std::endl;

        results[2][1] = Executor::executeMultiThreaded(ds, {
            "generated_files/equal_3thread_1.txt",
            "generated_files/equal_3thread_2.txt",
            "generated_files/equal_3thread_3.txt"
            });
        std::cout << "Equal: " << results[2][1] << " ms" << std::endl;

        results[2][2] = Executor::executeMultiThreaded(ds, {
            "generated_files/wrong_3thread_1.txt",
            "generated_files/wrong_3thread_2.txt",
            "generated_files/wrong_3thread_3.txt"
            });
        std::cout << "Wrong: " << results[2][2] << " ms" << std::endl << std::endl;
    }

    std::cout << "\n======================================" << std::endl;
    std::cout << "=== Results (time in ms) ===" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "              Variant    Equal      Wrong" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "1 thread:     " << std::setw(8) << results[0][0] << "   "
        << std::setw(8) << results[0][1] << "   " << std::setw(8) << results[0][2] << std::endl;
    std::cout << "2 threads:    " << std::setw(8) << results[1][0] << "   "
        << std::setw(8) << results[1][1] << "   " << std::setw(8) << results[1][2] << std::endl;
    std::cout << "3 threads:    " << std::setw(8) << results[2][0] << "   "
        << std::setw(8) << results[2][1] << "   " << std::setw(8) << results[2][2] << std::endl;
    std::cout << "======================================" << std::endl;

    return 0;
}