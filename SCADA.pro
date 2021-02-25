QT += widgets

SOURCES += \
    SCADAWindow.cpp \
    main.cpp

HEADERS += \
    ../../../TwinCAT/AdsApi/TcAdsDll/Include/TcAdsAPI.h \
    ../../../TwinCAT/AdsApi/TcAdsDll/Include/TcAdsDef.h \
    SCADAWindow.h

win32: LIBS += -L$$PWD/../../../TwinCAT/AdsApi/TcAdsDll/x64/lib/ -lTcAdsDll

INCLUDEPATH += $$PWD/../../../TwinCAT/AdsApi/TcAdsDll/x64
DEPENDPATH += $$PWD/../../../TwinCAT/AdsApi/TcAdsDll/x64

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../TwinCAT/AdsApi/TcAdsDll/x64/lib/TcAdsDll.lib
