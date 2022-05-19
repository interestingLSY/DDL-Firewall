#include "config.h"

#include <cassert>
#include <cstring>
#include <iostream>

#include <QString>
#include <QDebug>
#include <QErrorMessage>

Config config;
int Config::instance_count = 0;

Config::Config() {
	++instance_count;
	if (instance_count >= 2) {
		// There must exist exactly one instance
		// So there must be something wrong
		fprintf(stderr, "ERROR! There must exist exactly one instance of config\n");
		assert(0);
	}
	this->config_qdir = QDir::home();
	bool is_directory_exist = this->config_qdir.cd("ddl_firewall");
	if (!is_directory_exist) {
		// try to create the directory
		bool is_create_success = this->config_qdir.mkdir("ddl_firewall");
		assert(is_create_success);
		bool is_cd_success = this->config_qdir.cd("ddl_firewall");
		assert(is_cd_success);
	}
	bool is_file_exist = this->config_qdir.exists("config.json");
	this->config_qfile.setFileName(this->config_qdir.absoluteFilePath("config.json"));
	if (!is_file_exist) {
		this->config_qfile.open(QIODevice::ReadWrite | QIODevice::Text);
		QTextStream text_stream(&this->config_qfile);
		text_stream << "{}";
		this->config_qfile.close();
	}
	this->read_config();
}

Config::~Config() {
	this->save_config();
}

void Config::read_config() {
	bool is_open_success = this->config_qfile.open(QIODevice::ReadOnly | QIODevice::Text);
	assert(is_open_success);
	QTextStream text_stream = QTextStream(&this->config_qfile);
	QString content = text_stream.readAll();

	Json::Reader reader;
	bool is_parse_success = reader.parse(content.toStdString(), this->data);
	if (!is_parse_success) {
		// TODO: use QErrorMessage
		fprintf(stderr, "在解析 config.json 时出现错误。\nconfig.json:\n%s\n\n", content.toStdString().c_str());
		exit(1);
	}
	
	// 依次检查每个字段，如果有空字段，就填上默认值
	// 为什么要在函数体内部 include? 因为在 C++ 中，全局静态变量的初始化顺序是随机的。
	// 这就导致在某些情况下，当 Config 被初始化的时候，CONFIG_TEMPLATE 没有被初始化。
	// 这样就会出现问题。
	// 但是如果我们把 static const ... CONFIG_TEMPLATE 的定义放到这里，那么初始化顺序就是确定的。
	// 总而言之，rust 真香。
	#include "config_template.hpp"
	for (auto &[key, default_val] : CONFIG_TEMPLATE) {
		if (!this->data.isMember(key)) {
			this->data[key] = default_val;
		}
	}

	this->config_qfile.close();
}

void Config::save_config() {
	bool is_open_success = this->config_qfile.open(QIODevice::ReadWrite | QIODevice::Text);
	assert(is_open_success);

	Json::StyledWriter writer;
	std::string data_string = writer.write(this->data);
	QTextStream text_stream(&this->config_qfile);
	text_stream << QString(data_string.c_str());

	this->config_qfile.close();
}

std::string Config::get_value(const std::string &key) {
	assert(this->data.isMember(key));
	return this->data[key].asString();
}

void Config::set_value(const std::string &key, const std::string &value) {
	this->data[key] = value;
}