#include "tasklist.h"

QDebug operator<< (QDebug debug, const Tasklist &tasklist) {
    debug << "Tasklist{" << tasklist.name;
    debug << "tasks:" << tasklist.tasks;
    debug << "}";
    return debug;
}

bool operator== (const Tasklist &tasklist1, const Tasklist &tasklist2) {
    return tasklist1.name == tasklist2.name &&
            tasklist1.tasks == tasklist2.tasks;
}
