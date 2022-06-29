#pragma once

#include <vector>
#include <functional>
#include <QDebug>
#include <QString>
#include <QVector>

#include "uuid.hpp"
#include "reminder.h"
#include "subtask.h"

enum class TaskType {
	JOB = 0,      // 任务类
	SCHEDULED_EVENT = 2  // 定时事务
};

/*
Task 类，每个 Task 类表示一个“事务”
*/
class Task {
public:
	uuid_t uuid;
	TaskType type;
	QString name;
	QString comment;
	QVector<Subtask> subtasks;
	QVector<Reminder> reminders;
	QDateTime start_time; // 开始时间
	QDateTime end_time;   // 截止时间
	bool is_finished;

	void add_subtask(const Subtask &subtask);
	QVector<Subtask*> filter_subtask(std::function<bool(const Subtask&)> filt);
	void del_subtask(uuid_t target_uuid);

	void add_reminder(const Reminder &reminder);
	QVector<Reminder*> filter_reminder(std::function<bool(const Reminder&)> filt);
	void del_reminder(uuid_t target_uuid);

	Task();
	~Task();

	friend QDebug operator<< (QDebug debug, const Task &task);
	friend bool operator== (const Task &task1, const Task &task2);
};