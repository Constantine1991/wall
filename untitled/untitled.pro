#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T13:34:07
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app
CONFIG	+= qaxcontainer

SOURCES += \
    settingswindow.cpp \
    propertieswallwindow.cpp \
    propertiespillarwindow.cpp \
    mainwindow.cpp \
    main.cpp \
    listitem.cpp \
    graphicstext.cpp \
    graphicspillaritem.cpp \
    excelexport.cpp \
    diagramviewwall.cpp \
    diagramviewpillar.cpp \
    diagramview.cpp \
    calculate.cpp \
    cryptxor.cpp \
    graphicswallitem.cpp \
    graphicswicketitem.cpp \
    groupitem.cpp \
    graphicsgate1item.cpp \
    graphicsgate2item.cpp \
    interval.cpp \
    component.cpp \
    graphicslineitem.cpp \
    about.cpp \
    activationwindow.cpp

HEADERS  += \
    settingswindow.h \
    propertieswallwindow.h \
    propertiespillarwindow.h \
    propertiesitem.h \
    mainwindow.h \
    listitem.h \
    graphicswallitem.h \
    graphicstext.h \
    graphicspillaritem.h \
    excelexport.h \
    diagramviewwall.h \
    diagramviewpillar.h \
    diagramview.h \
    calculate.h \
    cryptxor.h \
    graphicswicketitem.h \
    groupitem.h \
    graphicsgate1item.h \
    graphicsgate2item.h \
    interval.h \
    component.h \
    graphicslineitem.h \
    about.h \
    activationwindow.h

FORMS    += \
    settingswindow.ui \
    propertieswallwindow.ui \
    propertiespillarwindow.ui \
    mainwindow.ui \
    interval.ui \
    component.ui \
    about.ui \
    activationwindow.ui

RESOURCES += \
    res.qrc

OTHER_FILES +=
