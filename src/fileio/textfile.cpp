#include "textfile.h"

#include <cassert>
#include <cstring>
#include <iostream>

#include <QString>
#include <QDebug>
#include <QErrorMessage>

#define DATA_FOLDER_NAME ".ddl_firewall"

Textfile::Textfile(const QString &_filename, const QString &default_content = ""):
	filename(_filename) {
	this->qdir = QDir::home();
	bool is_directory_exist = this->qdir.cd(DATA_FOLDER_NAME);
	if (!is_directory_exist) {
		// try to create the directory
		bool is_create_success = this->qdir.mkdir(DATA_FOLDER_NAME);
		assert(is_create_success);
		bool is_cd_success = this->qdir.cd(DATA_FOLDER_NAME);
		assert(is_cd_success);
	}
	bool is_file_exist = this->qdir.exists(this->filename);
	this->qfile.setFileName(this->qdir.absoluteFilePath(this->filename));
	if (!is_file_exist) {
		this->write_all(default_content);
	}
}

Textfile::~Textfile() {
}

QString Textfile::read_all() {
	bool is_open_success = this->qfile.open(QIODevice::ReadOnly | QIODevice::Text);
	assert(is_open_success);

	QTextStream text_stream = QTextStream(&this->qfile);
	QString content = text_stream.readAll();

	this->qfile.close();
	return content;
}

void Textfile::write_all(const QString &content) {
	bool is_open_success = this->qfile.open(QIODevice::ReadWrite | QIODevice::Text);
	assert(is_open_success);

	QTextStream text_stream(&this->qfile);
	text_stream << content;

	this->qfile.close();
}