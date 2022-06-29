QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS= frontend/ddlfirewall.ico
CONFIG += c++17
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    frontend/add_reminder.cpp \
    frontend/add_subtask.cpp \
    frontend/edit_reminder.cpp \
    frontend/edit_subtask.cpp \
    backend/3rdparty/jsoncpp/jsoncpp.cpp \
    backend/classes/reminder.cpp \
    backend/classes/task.cpp \
    backend/classes/subtask.cpp \
    backend/classes/tasklist.cpp \
    backend/config/config.cpp \
    backend/data/data.cpp \
    backend/data/json_io.cpp \
    backend/fileio/textfile.cpp \
    backend/self_test/data_gen.cpp \
    frontend/add_job.cpp \
    frontend/add_sche_task.cpp \
    frontend/add_tasklist.cpp \
    frontend/main.cpp \
    frontend/mainwindow.cpp \
    frontend/edit_sche_task.cpp \
    frontend/edit_job.cpp

HEADERS += \
    frontend/add_reminder.h \
    frontend/add_reminder.h \
    frontend/add_subtask.h \
    frontend/edit_reminder.h \
    frontend/edit_subtask.h \
    backend/3rdparty/jsoncpp/json.h \
    backend/3rdparty/jsoncpp/json-forwards.h \
    backend/classes/reminder.h \
    backend/classes/task.h \
    backend/classes/subtask.h \
    backend/classes/tasklist.h \
    backend/config/config.h \
    backend/data/data.h\
    backend/data/json_io.h\
    backend/fileio/textfile.h \
    backend/self_test/data_gen.h \
    frontend/add_job.h \
    frontend/add_sche_task.h \
    frontend/add_tasklist.h \
    frontend/mainwindow.h \
    frontend/edit_sche_task.h \
    frontend/edit_job.h

FORMS += \
    frontend/add_job.ui \
    frontend/add_reminder.ui \
    frontend/add_reminder.ui \
    frontend/add_sche_task.ui \
    frontend/add_subtask.ui \
    frontend/add_tasklist.ui \
    frontend/edit_reminder.ui \
    frontend/edit_subtask.ui \
    frontend/mainwindow.ui \
    frontend/edit_sche_task.ui \
    frontend/edit_job.ui

RESOURCES += frontend/ddlfirewall.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
