TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
TARGET = oalplus_test

# custom compiler option to enable ISO C++ 2011 standard (required for oalplus)
QMAKE_CXXFLAGS += -std=c++11

# neccessary libs
LIBS += -lopenal
LIBS += -lalut
LIBS += -lSDL
