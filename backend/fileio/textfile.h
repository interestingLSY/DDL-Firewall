#pragma once

#include <cstring>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>

extern const QString DATA_FOLDER_NAME;

class Textfile {
private:
	QString filename;
	QDir qdir;
	QFile qfile;

public:
	Textfile(const QString &_filename, const QString &default_content);
	~Textfile();

	QString read_all();
	void write_all(const QString &content);
};