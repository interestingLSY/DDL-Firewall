#include "data.h"
#include "json_io.h"

#include <cassert>

DataManager data_manager;
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

Json::Value DataManager::dump_as_json() {
	Json::Value result;
	result["tasklists"] = json_io::dump<Tasklist>(this->tasklists, [](const Tasklist &t){ return json_io::dump(t); });
	return result;
}

void DataManager::load_from_json(const Json::Value &value) {
	this->tasklists = json_io::load_qvector<Tasklist>(value["tasklists"], json_io::load_tasklist);
}

void DataManager::add_tasklist(const Tasklist &tasklist) {
	this->tasklists.push_back(tasklist);
}

QVector<Tasklist*> DataManager::filter_tasklist(std::function<bool(const Tasklist&)> filt) {
	QVector<Tasklist*> result;
	for (Tasklist& tasklist : this->tasklists)
		if (filt(tasklist))
			result.push_back(&tasklist);
	return result;
}

void DataManager::del_tasklisk(uuid_t target_uuid) {
	for (auto p = this->tasklists.begin(); p != this->tasklists.end(); ) {
		if (p->uuid == target_uuid)
			p = this->tasklists.erase(p);
		else
			p++;
	}
}

QVector<Task*> DataManager::generate_virtual_tasklist(std::function<bool(const Task&)> filt) {
	QVector<Task*> result;
	for (Tasklist& tasklist : this->tasklists) {
		result.append(tasklist.filter_task(filt));
	}
	return result;
}

void DataManager::del_task(uuid_t target_uuid) {
	for (Tasklist &tasklist : this->tasklists) {
		tasklist.del_task(target_uuid);
	}
}

bool DataManager::update_task(uuid_t target_uuid, const Task& new_task) {
	bool result = false;
	for (Tasklist &tasklist : this->tasklists) {
		result |= tasklist.update_task(target_uuid, new_task);
	}
	return result;
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

	this->load_from_json(json_data);
}

void DataManager::save() {
	Json::Value json_data = this->dump_as_json();
	
	Json::StyledWriter writer;
	std::string data_string = writer.write(json_data);
	this->file_handler.write_all(QString(data_string.c_str()));
}