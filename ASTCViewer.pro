QT += core gui quickwidgets widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(debug, debug|release) {
  DESTDIR = bin/debug
}

CONFIG(release, debug|release) {
  DESTDIR = bin/release
}
VERSION = 1.0.0.0
OBJECTS_DIR = bin/semi-finished/.obj
MOC_DIR = bin/semi-finished/.moc
RCC_DIR = bin/semi-finished/.rcc
UI_DIR = bin/semi-finished/.ui

SOURCES += \
    fileviewersource.cpp \
    main.cpp \
    qmlfileviewer.cpp \
    viewerwidget.cpp

HEADERS += \
    fileviewersource.h \
    qmlfileviewer.h \
    viewerwidget.h

FORMS += viewerwidget.ui
RC_ICONS += res/bitmap_image.ico
RESOURCES += res.qrc


deployData.path = $${DESTDIR}
deployData.files += deploy/*
INSTALLS += deployData
