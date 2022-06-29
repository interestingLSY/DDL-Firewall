#pragma once

#include <iostream>
#include <cassert>
#include <QDebug>

#include "../3rdparty/jsoncpp/json.h"

#include "../classes/reminder.h"
#include "../classes/subtask.h"
#include "../classes/task.h"
#include "../classes/tasklist.h"
#include "../data/json_io.h"

#include "./data_gen.h"

namespace self_test {

void jsonio_test() {
	Tasklist tasklist = gen::tasklist(10, 10, 10);
	// qDebug() << tasklist;
	Json::Value value = json_io::dump(tasklist);
	std::cerr << value << std::endl;
	Tasklist tasklist_recovered = json_io::load_tasklist(value);
	// qDebug() << tasklist_recovered;
	assert(tasklist == tasklist_recovered);
	std::cerr << "PASSED!" << std::endl;
}

}	// namespace self_test