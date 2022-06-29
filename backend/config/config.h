#pragma once

#include "../3rdparty/jsoncpp/json.h"
#include "../3rdparty/jsoncpp/json-forwards.h"
#include "../fileio/textfile.h"

/*
Config 类
负责维护用户的“设置”

*/

class Config {
private:
	Textfile file_handler;
	Json::Value data;
	static int instance_count;
	void load();
	void save();

public:
	Config();
	~Config();

	std::string get_value(const std::string &key);
	void set_value(const std::string &key, const std::string &value);
};

extern Config config;