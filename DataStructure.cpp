#include "DataStructure.h"

DataStructure::DataStructure() {
    for (int i = 0; i < FIELD_COUNT; i++) {
        fields[i] = 0;
    }
}

int DataStructure::read(int field_index) {
    std::lock_guard<std::mutex> lock(field_mutexes[field_index]);

    volatile int temp = 0;
    for (int i = 0; i < 50000; i++) {
        temp += i;
    }

    return fields[field_index];
}

void DataStructure::write(int field_index, int value) {
    std::lock_guard<std::mutex> lock(field_mutexes[field_index]);

    volatile int temp = 0;
    for (int i = 0; i < 50000; i++) {
        temp += i;
    }

    fields[field_index] = value;
}

std::string DataStructure::toString() {
    std::lock_guard<std::mutex> lock0(field_mutexes[0]);
    std::lock_guard<std::mutex> lock1(field_mutexes[1]);
    std::lock_guard<std::mutex> lock2(field_mutexes[2]);

    volatile int temp = 0;
    for (int i = 0; i < 100000; i++) {
        temp += i;
    }

    std::stringstream ss;
    ss << "[" << fields[0] << ", " << fields[1] << ", " << fields[2] << "]";
    return ss.str();
}