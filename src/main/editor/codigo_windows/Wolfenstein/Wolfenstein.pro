QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    celd.cpp \
    itemsid.cpp \
    main.cpp \
    mainwindow.cpp \
    mapgrid.cpp \
    option.cpp \
    options_container.cpp \
    optionselected.cpp

HEADERS += \
    celd.h \
    itemsid.h \
    mainwindow.h \
    mapgrid.h \
    option.h \
    options_container.h \
    optionselected.h

FORMS += \
    celd.ui \
    mainwindow.ui \
    mapgrid.ui \
    menu.ui \
    option.ui \
    options_container.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
