QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
!versionAtLeast(QT_VERSION, 5.14):error("Use at least Qt version 5.14")

CONFIG += c++11

SOURCES += \
    MarkdownHandler.cpp \
    main.cpp \
    mainwindow.cpp \
    TextEdit.cpp

HEADERS += \
    MarkdownHandler.h \
    mainwindow.h \
    TextEdit.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    MarkItDown_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MyRes.qrc
