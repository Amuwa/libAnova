TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../anova/anova.cpp \
    ../../anova/fdistribution.cpp

HEADERS += \
    ../../anova/anova.h \
    ../../anova/fdistribution.h \
    ../../anova/libAnova.h

