QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/campus_nav.cpp \
    src/database_connection.cpp \
    src/diaryread.cpp \
    src/diarywindow.cpp \
    src/kmp_search.cpp \
    src/location_choose.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/login_widget.cpp \
    src/route_plan.cpp \
    src/tool_class/read_data.cpp \
    src/tool_class/road_calcu.cpp \
    src/tool_class/update_database.cpp \
    src/writewidget.cpp

HEADERS += \
    include/campus_nav.h \
    include/database_connection.h \
    include/diarywindow.h \
    include/kmp_search.h \
    include/mainwindow.h \
    include/route_plan.h \
    include/simple_class/diary.h \
    include/simple_class/location.h \
    include/simple_class/map_elements.h \
    include/simple_class/user.h \
    include/tool_class/read_data.h \
    include/writewidget.h \
    include/diaryread.h \
    include/location_choose.h \
    include/tool_class/update_database.h \
    include/login_widget.h \
    include/top_k_algorithm.h

FORMS += \
    ui/campus_nav.ui \
    ui/login_widget.ui \
    ui/diaryread.ui \
    ui/location_choose.ui \
    ui/diarywindow.ui \
    ui/mainwindow.ui \
    ui/writewidget.ui

INCLUDEPATH += include
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
