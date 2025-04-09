QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/database_connection.cpp \
    src/diarywindow.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/tool_class/read_data.cpp \
    src/writewidget.cpp

HEADERS += \
    include/database_connection.h \
    include/diarywindow.h \
    include/mainwindow.h \
    include/simple_class/diary.h \
    include/simple_class/location.h \
    include/tool_class/read_data.h \
    include/writewidget.h

FORMS += \
    ui/diarywindow.ui \
    ui/mainwindow.ui \
    ui/writewidget.ui

INCLUDEPATH += include
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
