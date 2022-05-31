#include "data.h"
#include "json_io.h"

#include <cassert>

DataManager data;
int DataManager::instance_count = 0;

DataManager::DataManager():
	file_handler("data.json", "{}") {
	++instance_count;
	if (instance_count >= 2) {
		// There must exist exactly one instance
		// So there must be something wrong
		fprintf(stderr, "ERROR! There must exist exactly one instance of config\n");
		assert(0);
	}
	this->load();
}

DataManager::~DataManager() {
	this->save();
}

void DataManager::load() {
	QString content = this->file_handler.read_all();

	Json::Reader reader;
	Json::Value json_data;
	bool is_parse_success = reader.parse(content.toStdString(), json_data);
	if (!is_parse_success) {
		// TODO: use QErrorMessage
		fprintf(stderr, "在解析 data.json 时出现错误。\ndata.json:\n%s\n\n", content.toStdString().c_str());
		exit(1);
	}

	// TODO parse tasklists
}

void DataManager::save() {
	Json::Value json_data;
	Json::StyledWriter writer;
	std::string data_string = writer.write(json_data);
	this->file_handler.write_all(QString(data_string.c_str()));
}