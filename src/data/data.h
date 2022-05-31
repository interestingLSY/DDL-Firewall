#pragma once

#include "../3rdparty/jsoncpp/json.h"
#include "../3rdparty/jsoncpp/json-forwards.h"
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
	void load();
	void save();

public:
	QVector<Tasklist> tasklists; 

	DataManager();
	~DataManager();
};

extern DataManager data_manager;