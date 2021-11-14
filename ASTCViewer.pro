QT       += core gui quickwidgets widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(debug, debug|release) {
  DESTDIR = bin/debug
  OBJECTS_DIR = bin/debug/.obj
  MOC_DIR = bin/debug/.moc
  RCC_DIR = bin/debug/.rcc
  UI_DIR = bin/debug/.ui
}

CONFIG(release, debug|release) {
  # enable optimisation
  QMAKE_CXXFLAGS_RELEASE += -O4
  QMAKE_CXXFLAGS_RELEASE -= -O2
  QMAKE_CXXFLAGS_RELEASE -= -O3
  QMAKE_CXXFLAGS_RELEASE -= -Os
  QMAKE_CXXFLAGS += -O4
  QMAKE_CXXFLAGS -= -O2
  QMAKE_CXXFLAGS -= -O3
  QMAKE_CXXFLAGS -= -Os

  DESTDIR = bin/release
  OBJECTS_DIR = bin/release/.obj
  MOC_DIR = bin/release/.moc
  RCC_DIR = bin/release/.rcc
  UI_DIR = bin/release/.ui
}

## global compile flags
## enable open MP
QMAKE_CXXFLAGS += -floop-parallelize-all -ftree-parallelize-loops=4

SOURCES += \
    fileviewersource.cpp \
    main.cpp \
    qmlfileviewer.cpp \
    viewerwidget.cpp

HEADERS += \
    fileviewersource.h \
    qmlfileviewer.h \
    viewerwidget.h

FORMS += \
    viewerwidget.ui

RC_ICONS += res/bitmap_image.ico

RESOURCES += \
    res.qrc
