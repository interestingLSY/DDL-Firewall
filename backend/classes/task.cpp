#include "task.h"

void Task::add_subtask(const Subtask &subtask) {
    this->subtasks.push_back(subtask);
}

QVector<Subtask*> Task::filter_subtask(std::function<bool(const Subtask&)> filt) {
    QVector<Subtask*> result;
    for (Subtask& subtask : this->subtasks)
        if (filt(subtask))
            result.push_back(&subtask);
    return result;
}

void Task::del_subtask(uuid_t target_uuid) {
	for (auto p = this->subtasks.begin(); p != this->subtasks.end(); ) {
		if (p->uuid == target_uuid)
			p = this->subtasks.erase(p);
		else
			p++;
	}
}

void Task::add_reminder(const Reminder &reminder) {
    this->reminders.push_back(reminder);
}

QVector<Reminder*> Task::filter_reminder(std::function<bool(const Reminder&)> filt) {
    QVector<Reminder*> result;
    for (Reminder& reminder : this->reminders)
        if (filt(reminder))
            result.push_back(&reminder);
    return result;
}

void Task::del_reminder(uuid_t target_uuid) {
	for (auto p = this->reminders.begin(); p != this->reminders.end(); ) {
		if (p->uuid == target_uuid)
			p = this->reminders.erase(p);
		else
			p++;
	}
}

Task::Task() {
    this->is_finished = false;
    this->uuid = get_uuid();
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
