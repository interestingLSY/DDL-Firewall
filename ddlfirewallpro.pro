QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS= ddlfirewall.ico
CONFIG += c++17
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_reminder.cpp \
    add_subtask.cpp \
    edit_reminder.cpp \
    edit_subtask.cpp \
    src/3rdparty/jsoncpp/jsoncpp.cpp \
    src/classes/reminder.cpp \
    src/classes/task.cpp \
    src/classes/subtask.cpp \
    src/classes/tasklist.cpp \
    src/config/config.cpp \
    src/data/data.cpp \
    src/data/json_io.cpp \
    src/fileio/textfile.cpp \
    src/self_test/data_gen.cpp \
    add_job.cpp \
    add_sche_task.cpp \
    add_tasklist.cpp \
    calendar_type.cpp \
    errors.cpp \
    main.cpp \
    mainwindow.cpp \
    edit_sche_task.cpp \
    edit_job.cpp

HEADERS += \
    add_reminder.h \
    add_reminder.h \
    add_subtask.h \
    edit_reminder.h \
    edit_subtask.h \
    src/3rdparty/jsoncpp/json.h \
    src/3rdparty/jsoncpp/json-forwards.h \
    src/classes/reminder.h \
    src/classes/task.h \
    src/classes/subtask.h \
    src/classes/tasklist.h \
    src/config/config.h \
    src/data/data.h\
    src/data/json_io.h\
    src/fileio/textfile.h \
    src/self_test/data_gen.h \
    add_job.h \
    add_sche_task.h \
    add_tasklist.h \
    calendar_type.h \
    errors.h \
    mainwindow.h \
    edit_sche_task.h \
    edit_job.h

FORMS += \
    add_job.ui \
    add_reminder.ui \
    add_reminder.ui \
    add_sche_task.ui \
    add_subtask.ui \
    add_tasklist.ui \
    calendar_type.ui \
    edit_reminder.ui \
    edit_subtask.ui \
    errors.ui \
    mainwindow.ui \
    edit_sche_task.ui \
    edit_job.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
