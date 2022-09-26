QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += serialport
QT += printsupport
QT += 3dcore
QT += 3drender
QT += 3dinput
QT += 3dextras

CONFIG += c++17

CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mycombobox.cpp \
    myserialportreader.cpp \
    qcustomplot.cpp

HEADERS += \
    stable.h \
    stable.h \
    mainwindow.h \
    mycombobox.h \
    myserialportreader.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
