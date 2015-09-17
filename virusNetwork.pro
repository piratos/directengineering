###########################################################
#                                                         #
#       VirusNetwork créeé par Malek Khlif le 30/01/2014  #
#                                                         #
###########################################################

CONFIG += release
CONFIG += -static-libgcc
CONFIG += -static-libstdc++
QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++
LIBS += -static -lwinpthread

RC_FILE = rc.rc

QT = widgets network sql
SOURCES += \
    main.cpp \
    systemevn.cpp \
    tools.cpp \
    networkmanager.cpp \
    keyboardmanager.cpp \
    downloadmanager.cpp \
    cookiesmanager.cpp

HEADERS += \
    systemevn.h \
    tools.h \
    networkmanager.h \
    keyboardmanager.h \
    downloadmanager.h \
    cookiesmanager.h
