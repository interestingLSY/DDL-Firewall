#include "tasklist.h"

QDebug operator<< (QDebug debug, const Tasklist &tasklist) {
    debug << "Tasklist{" << tasklist.name;
    debug << "tasks:" << tasklist.tasks;
    debug << "}";
    return debug;
}
