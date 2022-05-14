#include "task.h"

Task::Task() {
    this->is_finished = false;
}

Task::~Task() {}

QDebug operator<< (QDebug debug, const Task &task) {
    debug << "Task{" << task.name;
    debug << "type:" << static_cast<int>(task.type);
    debug << "start_time:" << task.start_time;
    debug << "end_time:" << task.end_time;
    debug << "is_finished:" << task.is_finished;
    debug << "subtasks:" << task.subtasks;
    debug << "reminders:" << task.reminders;
    debug << "}";
    return debug;
}