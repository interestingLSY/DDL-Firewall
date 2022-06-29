#pragma once

#include <random>
#include <chrono>
#include <climits>

#include <QDateTime>

#include "../classes/reminder.h"
#include "../classes/subtask.h"
#include "../classes/task.h"
#include "../classes/tasklist.h"

namespace self_test {

namespace gen {

// generate a random number in [l,r] ∩ Z
int number(int l, int r);

QDateTime qdatetime();

QString qstring(int length = 6);

Reminder reminder();

Subtask subtask();

Task task(int subtask_cnt = 2, int reminder_cnt = 2);

Tasklist tasklist(int task_cnt = 2, int subtask_cnt = 2, int reminder_cnt = 2);

}	// namespace gen

}	// namespace self_test