#pragma once

#include <vector>
#include <QDebug>
#include <QString>
#include <QVector>
#include "reminder.h"
#include "subtask.h"

enum class TaskType {
	LONG_TASK = 0,      // 长期任务
	SHORT_TASK = 1,     // 短期任务
	SCHEDULED_TASK = 2  // 定时事务
};

/*
Task 类，每个 Task 类表示一个“事务”
*/
class Task {
public:
	TaskType type;
	QString name;
	QString comment;
	QVector<Subtask> subtasks;
	QVector<Reminder> reminders;
	QDateTime start_time; // 开始时间（尽在）
	QDateTime end_time;   // 截止时间
	bool is_finished;

	Task();
	~Task();

	friend QDebug operator<< (QDebug debug, const Task &task);
};