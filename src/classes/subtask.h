#pragma once

#include <QDebug>
#include <QString>

class Subtask {
public:
	QString name;
	bool is_finished;

	Subtask();
	Subtask (QString _name);
	~Subtask();

	friend QDebug operator<< (QDebug debug, const Subtask &subtask);
};