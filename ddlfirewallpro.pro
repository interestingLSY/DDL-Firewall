QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtask.cpp \
    addtasklist.cpp \
    calendar_type.cpp \
    errors.cpp \
    list_type.cpp \
    list_type2.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    addtask.h \
    addtasklist.h \
    calendar_type.h \
    errors.h \
    list_type.h \
    list_type2.h \
    mainwindow.h

FORMS += \
    addtask.ui \
    addtasklist.ui \
    calendar_type.ui \
    errors.ui \
    list_type.ui \
    list_type2.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
