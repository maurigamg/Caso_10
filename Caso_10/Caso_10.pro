TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += \
        main.c
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
HEADERS += \
    linkdlst.h \
    matroid.h \
    mtdparll.h
