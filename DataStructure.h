#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <mutex>
#include <string>
#include <sstream>

class DataStructure {
private:
    static const int FIELD_COUNT = 3;
    int fields[FIELD_COUNT];
    std::mutex field_mutexes[FIELD_COUNT];

public:
    DataStructure();

    int read(int field_index);
    void write(int field_index, int value);

    std::string toString();
};

#endif