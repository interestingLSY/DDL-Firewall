QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    job_edit.cpp \
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
    addtasklist.cpp \
    calendar_type.cpp \
    errors.cpp \
    list_type.cpp \
    list_type2.cpp \
    main.cpp \
    mainwindow.cpp \
    task_edit.cpp

HEADERS += \
    job_edit.h \
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
    addtasklist.h \
    calendar_type.h \
    errors.h \
    list_type.h \
    list_type2.h \
    mainwindow.h \
    task_edit.h

FORMS += \
    add_job.ui \
    add_sche_task.ui \
    addtasklist.ui \
    calendar_type.ui \
    errors.ui \
    job_edit.ui \
    list_type.ui \
    list_type2.ui \
    mainwindow.ui \
    task_edit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
