SOURCES += main.cpp \
 m3uplaylist.cpp \
 mainwindow.cpp \
 cover.cpp \
 songlistview.cpp \
 songfile.cpp \
 alignsettings.cpp \
 sizesettings.cpp \
 coverscene.cpp \
 texttools.cpp
TEMPLATE = app
CONFIG += warn_on \
      thread \
          qt \
          debug
TARGET = ../bin/pcover

HEADERS += m3uplaylist.h \
 mainwindow.h \
 cover.h \
 songlistview.h \
 songfile.h \
 alignsettings.h \
 sizesettings.h \
 coverscene.h \
 texttools.h

INCLUDEPATH += /usr/include/taglib

LIBS += -ltag

QT += widgets

