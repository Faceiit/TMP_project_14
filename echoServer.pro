QT -= gui
QT += core #?
QT += network
QT += sql  

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000



SOURCES += \
    main.cpp \
    mytcpserver.cpp \
    database.cpp


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mytcpserver.h \
    database.h