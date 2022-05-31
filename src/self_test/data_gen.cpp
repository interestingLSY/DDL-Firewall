#include "data_gen.h"

namespace self_test {

namespace gen {

// generate a random number in [l,r] ∩ Z
int number(int l, int r) {
	static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	return std::uniform_int_distribution<int>(l, r)(rng);
}

long long number64(long long l, long long r) {
	static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	return std::uniform_int_distribution<long long>(l, r)(rng);
}

QDateTime qdatetime() {
	long long milli_secs = number64(0, INT_MAX);
	milli_secs = (milli_secs / 1000) * 1000;
	return QDateTime::fromMSecsSinceEpoch(milli_secs);
}

QString qstring(int length) {
	QString result = "";
	for (int i = 0; i < length; ++i) {
		char c = 'a' + gen::number(0, 25);
		result.append(c);
	}
	return result;
}

Reminder reminder() {
	Reminder result;
	result.type = static_cast<ReminderType>(gen::number(0, 1));
	result.accurate_time = gen::qdatetime();
	result.second_delta = gen::number(0, 60*60*4);
	return result;
}

Subtask subtask() {
	Subtask result;
	result.name = gen::qstring();
	result.is_finished = (bool)number(0, 1);
	return result;
}

Task task(int subtask_cnt, int reminder_cnt) {
	Task result;
	result.type = static_cast<TaskType>(gen::number(0, 2));
	result.name = gen::qstring();
	result.comment = gen::qstring();
	for (int i = 0; i < subtask_cnt; ++i)
		result.subtasks.append(gen::subtask());
	for (int i = 0; i < reminder_cnt; ++i)
		result.reminders.append(gen::reminder());
	result.start_time = gen::qdatetime();
	result.end_time = gen::qdatetime();
	result.is_finished = (bool)number(0, 1);
	return result;
}

Tasklist tasklist(int task_cnt, int subtask_cnt, int reminder_cnt) {
	Tasklist result;
	result.name = gen::qstring();
	for (int i = 0; i < task_cnt; ++i)
		result.tasks.append(task(subtask_cnt, reminder_cnt));
	return result;
}

}	// namespace gen

}	// namespace self_test