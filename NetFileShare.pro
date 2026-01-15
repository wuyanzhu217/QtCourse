QT += core gui widgets sql network core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customtransfermodel.cpp \
    fileiomanager.cpp \
    filetransferclient.cpp \
    landevicediscoverer.cpp \
    main.cpp \
    transferqueuemanager.cpp \
    transferworkerthread.cpp \
    widget.cpp

HEADERS += \
    customtransfermodel.h \
    fileiomanager.h \
    filetransferclient.h \
    landevicediscoverer.h \
    transferqueuemanager.h \
    transferworkerthread.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEFINES += LAN_BROADCAST_PORT=8899 \
           FILE_TRANSFER_PORT=9900 \
           FILE_BLOCK_SIZE=4096
