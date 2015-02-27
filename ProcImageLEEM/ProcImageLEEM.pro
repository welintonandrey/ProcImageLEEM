#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T10:35:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProcImageLEEM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gallium.cpp \
    openfiledialog.cpp \
    subwindowmdi.cpp \
    outvideo.cpp

HEADERS  += mainwindow.h \
    gallium.h \
    openfiledialog.h \
    subwindowmdi.h \
    outvideo.h \
    convertImage.h

FORMS    += mainwindow.ui \
    openfiledialog.ui \
    outvideo.ui

#Libs OPENCV
INCLUDEPATH += /usr/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
