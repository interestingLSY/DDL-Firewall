#include "tasklist.h"

void Tasklist::add_task(const Task &task) {
    this->tasks.push_back(task);
}

QVector<Task*> Tasklist::filter_task(std::function<bool(const Task&)> filt) {
    QVector<Task*> result;
    for (Task& task : this->tasks) {
        if (filt(task)) {
            result.push_back(&task);
        }
    }
    return result;
}

void Tasklist::del_task(uuid_t target_uuid) {
    for (auto p = this->tasks.begin(); p != this->tasks.end(); ) {
		if (p->uuid == target_uuid)
			p = this->tasks.erase(p);
		else
			p++;
	}
}

Tasklist::Tasklist() {
    this->uuid = get_uuid();
}

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
