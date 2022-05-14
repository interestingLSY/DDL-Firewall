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