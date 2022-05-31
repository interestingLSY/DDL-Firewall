#pragma once

#include <functional>

#include "../3rdparty/jsoncpp/json.h"
#include "../3rdparty/jsoncpp/json-forwards.h"
#include "../classes/uuid.hpp"
#include "../fileio/textfile.h"
#include "../classes/tasklist.h"

/*
DataManager 类
负责管理所有的数据
*/

class DataManager {
private:
	Textfile file_handler;
	static int instance_count;

	Json::Value dump_as_json();
	void load_from_json(const Json::Value &);
	
public:
	QVector<Tasklist> tasklists; 

	void load();
	void save();

	void add_tasklist(const Tasklist &tasklist);
	QVector<Tasklist*> filter_tasklist(std::function<bool(const Tasklist&)> filt);
	void del_tasklisk(uuid_t target_uuid);

	DataManager();
	~DataManager();
};

extern DataManager data_manager;