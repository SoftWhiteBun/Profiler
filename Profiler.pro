TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CConstants.cpp \
    FThreads.cpp \
    UBaseProcess.cpp \
    UInteraction.cpp \
    UProcess.cpp \
    UProcessDoubleBuffer.cpp \
    UTask.cpp \
    UTimer.cpp

HEADERS += \
    CConstants.h \
    CThreadConstants.h \
    FThreads.h \
    UBaseProcess.h \
    UInteraction.h \
    UProcess.h \
    UProcessDoubleBuffer.h \
    UTask.h \
    UTimer.h

LIBS += -lrt \
        -lpthread
