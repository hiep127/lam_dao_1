TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lrt
LIBS += -pthread

SOURCES += \
        File.cpp \
        Service.cpp \
        ShareMem.cpp \
        main.cpp

DISTFILES += \
    test.json

HEADERS += \
    Define.h \
    File.h \
    Service.h \
    ShareMem.h \
    include/nlohmann/json.hpp \
    include/nlohmann/json_fwd.hpp
