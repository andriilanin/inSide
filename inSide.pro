QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addnewchatdialog.cpp \
    chatdatabase.cpp \
    chatgui.cpp \
    chatitem.cpp \
    chatslist.cpp \
    main.cpp \
    mainwindow.cpp \
    messageitem.cpp

HEADERS += \
    addnewchatdialog.h \
    chatdatabase.h \
    chatgui.h \
    chatitem.h \
    chatslist.h \
    mainwindow.h \
    messageitem.h

FORMS += \
    addnewchatdialog.ui \
    chatgui.ui \
    chatitem.ui \
    chatslist.ui \
    mainwindow.ui \
    messageitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
