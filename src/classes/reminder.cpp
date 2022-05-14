#include "reminder.h"

QDebug operator<< (QDebug debug, const Reminder &reminder){
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