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
    about.cpp \
    cryptxor.cpp \
    activationform.cpp \
    graphicswallitem.cpp \
    graphicswicketitem.cpp \
    groupitem.cpp \
    graphicsgate1item.cpp \
    graphicsgate2item.cpp \
    interval.cpp \
    component.cpp \
    graphicslineitem.cpp

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
    about.h \
    cryptxor.h \
    activationform.h \
    graphicswicketitem.h \
    groupitem.h \
    graphicsgate1item.h \
    graphicsgate2item.h \
    interval.h \
    component.h \
    graphicslineitem.h

FORMS    += \
    settingswindow.ui \
    propertieswallwindow.ui \
    propertiespillarwindow.ui \
    mainwindow.ui \
    about.ui \
    activationform.ui \
    interval.ui \
    component.ui

RESOURCES += \
    res.qrc

OTHER_FILES +=
