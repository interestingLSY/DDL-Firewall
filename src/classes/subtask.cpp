#include "subtask.h"

Subtask::Subtask() {
    this->is_finished = false;
}

Subtask::Subtask (QString _name)
    : name(_name) {
    this->is_finished = false;
}

Subtask::~Subtask() {}

QDebug operator<< (QDebug debug, const Subtask &subtask) {
    debug << "Subtask{" << subtask.name << "is_finished:" << subtask.is_finished << "}";
    return debug;
}

bool operator== (const Subtask &subtask1, const Subtask &subtask2) {
    return subtask1.name == subtask2.name &&
            subtask1.is_finished == subtask2.is_finished;
}
