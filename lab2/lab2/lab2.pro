QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basefigure.cpp \
    brokenline.cpp \
    ellipse.cpp \
    line.cpp \
    main.cpp \
    paint.cpp \
    paintscene.cpp \
    polygon.cpp \
    rectangle.cpp

HEADERS += \
    basefigure.h \
    brokenline.h \
    ellipse.h \
    line.h \
    paint.h \
    paintscene.h \
    polygon.h \
    rectangle.h \
    tools.h

FORMS += \
    paint.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
