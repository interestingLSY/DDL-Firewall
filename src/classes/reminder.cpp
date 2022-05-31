#include "reminder.h"

Reminder::Reminder() {
    this->uuid = get_uuid();
}

QDebug operator<< (QDebug debug, const Reminder &reminder) {
    debug << "Reminder{";
    if (reminder.type == ReminderType::BY_ACCURATE_TIME) {
        debug << "BY_ACCURATE_TIME,";
        debug << reminder.accurate_time.toString("yyyy.MM.dd hh:mm:ss");
    } else {
        debug << "BY_TIME_DELTA," << reminder.second_delta;
    }
    debug << "}";
    return debug;
}

bool operator== (const Reminder &reminder1, const Reminder &reminder2) {
    return reminder1.type == reminder2.type &&
            reminder1.accurate_time == reminder2.accurate_time &&
            reminder1.second_delta == reminder2.second_delta;
}
