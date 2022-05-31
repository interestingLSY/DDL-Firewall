#pragma once

#include <iostream>
#include <QDateTime>
#include <QDebug>

/*
Reminder 的类型
BY_ACCURATE_TIME 指的是“到指定的时间就提醒”
BY_TIME_DELTA 指的是“距离开始时间还有指定秒数的时候提醒”
*/
enum class ReminderType {
    BY_ACCURATE_TIME = 0,
    BY_TIME_DELTA    = 1
};

/*
“提醒”类
每个 Task 类均包含一个名为 reminders 的 vector<Reminder>，表示要在哪些时间提醒
*/
class Reminder {
public:
    ReminderType type;

	// 如果这个 Reminder 的类型是 BY_ACCURATE_TIME（到指定的时间就提醒），那么该 field 就表示提醒的时间
	QDateTime accurate_time;

	// 如果这个 Reminder 的类型是 BY_TIME_DELTA（距离事务的开始时间还有指定秒数的时候提醒），那么该 field 就表示距离开始时间还有多少秒的时候提醒
	int second_delta;

	friend QDebug operator<< (QDebug debug, const Reminder &reminder);
	friend bool operator== (const Reminder &reminder1, const Reminder &reminder2);
};