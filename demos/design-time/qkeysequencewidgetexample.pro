TEMPLATE = app
TARGET = demo-designtime
include(../../qkeysequencewidget/qkeysequencewidget.pri)
SOURCES += src/main.cpp \
    src/widget.cpp
HEADERS += src/widget.h
FORMS += src/widget.ui
