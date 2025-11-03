#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H

#include <string>
#include <vector>

class FileGenerator {
public:
    static void generateVariant12File(const std::string& filename, int operations_count);

    static void generateEqualFile(const std::string& filename, int operations_count);

    static void generateWrongFile(const std::string& filename, int operations_count);

private:
    static void writeOperationsToFile(const std::string& filename,
        const std::vector<std::string>& operations);
};

#endif