#pragma once

#include <functional>
#include <QDebug>
#include <QString>
#include <QVector>

#include "uuid.hpp"
#include "task.h"

class Tasklist {
public:
	uuid_t uuid;
	QString name;
	QVector<Task> tasks;

	
	void add_task(const Task &task);
	QVector<Task*> filter_task(std::function<bool(const Task&)> filt);
	void del_task(uuid_t target_uuid);
	void update_task(uuid_t target_uuid, const Task &new_task);

	Tasklist();
	
	friend QDebug operator<< (QDebug debug, const Tasklist &task);
	friend bool operator== (const Tasklist &tasklist1, const Tasklist &tasklist2);
};