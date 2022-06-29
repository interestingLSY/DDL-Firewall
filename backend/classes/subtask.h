#pragma once

#include <QDebug>
#include <QString>

#include "uuid.hpp"

class Subtask {
public:
	uuid_t uuid;
	QString name;
	bool is_finished;

	Subtask();
	Subtask (QString _name);
	~Subtask();

	friend QDebug operator<< (QDebug debug, const Subtask &subtask);
	friend bool operator== (const Subtask &subtask1, const Subtask &subtask2);
};