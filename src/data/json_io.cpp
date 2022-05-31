#include "json_io.h"

namespace json_io {

// QDateTime
Json::Value dump(const QDateTime &qdatatime) {
	return Json::Value(qdatatime.toString("yyyy-MM-dd hh:mm:ss").toStdString());
}

QDateTime load_qdatetime(const Json::Value &value) {
	return QDateTime::fromString(QString(value.asString().c_str()), QString("yyyy-MM-dd hh:mm:ss"));
}

// QVector
template<typename T>
Json::Value dump(const QVector<T> &qvector, std::function<Json::Value(const T&)> dumper) {
	Json::Value result;
	for (const T& item : qvector) {
		result.append(dumper(item));
	}
	return result;
}

template<typename T>
QVector<T> load_qvector(const Json::Value &value, std::function<T(const Json::Value&)> loader) {
	QVector<T> result;
	size_t sz = value.size();
	for (size_t i = 0; i < sz; ++i) {
		result.append(loader(value[(int)i]));
	}
	return result;
}

// Reminder
Json::Value dump(const Reminder &reminder) {
	Json::Value result;
	result["type"] = static_cast<int>(reminder.type);
	result["accurate_time"] = dump(reminder.accurate_time);
	result["second_delta"] = reminder.second_delta;
	return result;
}

Reminder load_reminder(const Json::Value &value) {
	Reminder result;
	result.type = static_cast<ReminderType>(value["type"].asInt());
	result.accurate_time = load_qdatetime(value["accurate_time"]);
	result.second_delta = value["second_delta"].asInt();
	return result;
}

// Subtask
Json::Value dump(const Subtask &subtask) {
	Json::Value result;
	result["name"] = subtask.name.toStdString();
	result["is_finished"] = subtask.is_finished;
	return result;
}

Subtask load_subtask(const Json::Value &value) {
	Subtask result;
	result.name = QString(value["name"].asCString());
	result.is_finished = value["is_finished"].asBool();
	return result;
}

// Task
Json::Value dump(const Task &task) {
	Json::Value result;
	result["type"] = static_cast<int>(task.type);
	result["name"] = task.name.toStdString();
	result["comment"] = task.comment.toStdString();
	result["subtasks"] = dump<Subtask>(task.subtasks, [](const Subtask &t){ return dump(t); });
	result["reminders"] = dump<Reminder>(task.reminders, [](const Reminder &t){ return dump(t); });
	result["start_time"] = dump(task.start_time);
	result["end_time"] = dump(task.end_time);
	result["is_finished"] = task.is_finished;
	return result;
}

Task load_task(const Json::Value &value) {
	Task result;
	result.type = static_cast<TaskType>(value["type"].asInt());
	result.name = value["name"].asCString();
	result.comment = value["comment"].asCString();
	result.subtasks = load_qvector<Subtask>(value["subtasks"], load_subtask);
	result.reminders = load_qvector<Reminder>(value["reminders"], load_reminder);
	result.start_time = load_qdatetime(value["start_time"]);
	result.end_time = load_qdatetime(value["end_time"]);
	result.is_finished = value["is_finished"].asBool();
	return result;
}

// Tasklist
Json::Value dump(const Tasklist &tasklist) {
	Json::Value result;
	result["name"] = tasklist.name.toStdString();
	result["tasks"] = dump<Task>(tasklist.tasks, [](const Task &task){ return dump(task); });
	return result;
}

Tasklist load_tasklist(const Json::Value &value) {
	Tasklist result;
	result.name = value["name"].asCString();
	result.tasks = load_qvector<Task>(value["tasks"], load_task);
	return result;
}


}