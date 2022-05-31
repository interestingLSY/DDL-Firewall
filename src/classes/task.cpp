#include "task.h"

Task::Task() {
    this->is_finished = false;
}

Task::~Task() {}

QDebug operator<< (QDebug debug, const Task &task) {
    debug << "Task{" << task.name;
    debug << "comment" << task.comment;
    debug << "type:" << static_cast<int>(task.type);
    debug << "start_time:" << task.start_time;
    debug << "end_time:" << task.end_time;
    debug << "is_finished:" << task.is_finished;
    debug << "subtasks:" << task.subtasks;
    debug << "reminders:" << task.reminders;
    debug << "}";
    return debug;
}

bool operator== (const Task &task1, const Task &task2) {
    return task1.type == task2.type &&
            task1.name == task2.name &&
            task1.comment == task2.comment &&
            task1.subtasks == task2.subtasks &&
            task1.reminders == task2.reminders &&
            task1.start_time == task2.start_time &&
            task1.end_time == task2.end_time &&
            task1.is_finished == task2.is_finished;
}
