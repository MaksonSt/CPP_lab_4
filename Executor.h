#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "DataStructure.h"
#include <string>
#include <vector>

class Executor {
public:
    static double executeFile(DataStructure& ds, const std::string& filename);
    static double executeMultiThreaded(DataStructure& ds,
        const std::vector<std::string>& filenames);

private:
    static void executeOperations(DataStructure& ds,
        const std::vector<std::string>& operations);
    static std::vector<std::string> loadOperations(const std::string& filename);
};

#endif