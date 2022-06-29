#pragma once
#include <functional>

#include "../3rdparty/jsoncpp/json-forwards.h"
#include "../3rdparty/jsoncpp/json.h"

#include "../classes/reminder.h"
#include "../classes/subtask.h"
#include "../classes/task.h"
#include "../classes/tasklist.h"

namespace json_io {

// QDateTime
Json::Value dump(const QDateTime &qdatatime);
QDateTime load_qdatetime(const Json::Value &value);

// QVector
template<typename T>
Json::Value dump(const QVector<T> &qvector, std::function<Json::Value(const T&)> dumper);
template<typename T>
QVector<T> load_qvector(const Json::Value &value, std::function<T(const Json::Value&)> loader);

// Reminder
Json::Value dump(const Reminder &reminder);
Reminder load_reminder(const Json::Value &value);

// Subtask
Json::Value dump(const Subtask &subtask);
Subtask load_subtask(const Json::Value &value);

// Task
Json::Value dump(const Task &task);
Task load_task(const Json::Value &value);

// Tasklist
Json::Value dump(const Tasklist &tasklist);
Tasklist load_tasklist(const Json::Value &value);

}	// namespace json_io