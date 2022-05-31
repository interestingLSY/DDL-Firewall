#pragma once

#include <QDebug>
#include <QString>
#include <QVector>
#include "task.h"

class Tasklist {
public:
	QString name;
	QVector<Task> tasks;

	friend QDebug operator<< (QDebug debug, const Tasklist &task);
	friend bool operator== (const Tasklist &tasklist1, const Tasklist &tasklist2);
};