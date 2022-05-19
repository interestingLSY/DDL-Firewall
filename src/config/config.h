#pragma once

#include <QDir>
#include <QFile>
#include <QTextStream>
#include "../3rdparty/jsoncpp/json.h"
#include "../3rdparty/jsoncpp/json-forwards.h"

/*
Config 类
负责维护用户的“设置”

*/

class Config {
private:
	QDir config_qdir;
	QFile config_qfile;
	Json::Value data;

public:
	Config();
	~Config();

	void read_config();
	void save_config();

	std::string get_value(const std::string &key);
	void set_value(const std::string &key, const std::string &value);
};

extern Config config;