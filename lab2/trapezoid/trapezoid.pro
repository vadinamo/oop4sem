QT += widgets

TEMPLATE = lib
DEFINES += TRAPEZOID_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../lab2/basefigure.cpp \
    trapezoid.cpp

HEADERS += \
    ../lab2/basefigure.h \
    trapezoid_global.h \
    trapezoid.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
