#-------------------------------------------------
#
# Project created by QtCreator 2019-11-10T12:33:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_annotation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        imageannotation.cpp \
    matdisplay.cpp

HEADERS += \
        imageannotation.h \
    matdisplay.h

FORMS += \
        imageannotation.ui

INCLUDEPATH += F:\\opencv\\qt_opencv_64\\install\\include
LIBS += -LF:\\opencv\\qt_opencv_64\\install\\x64\\vc16\\lib \
    -lopencv_calib3d347d \
    -lopencv_core347d \
    -lopencv_dnn347d \
    -lopencv_features2d347d \
    -lopencv_flann347d \
    -lopencv_highgui347d \
    -lopencv_imgcodecs347d \
    -lopencv_imgproc347d \
    -lopencv_ml347d \
    -lopencv_objdetect347d \
    -lopencv_photo347d \
    -lopencv_stitching347d \
    -lopencv_superres347d \
    -lopencv_video347d \
    -lopencv_videostab347d

DISTFILES +=

RESOURCES += \
    resource.qrc \
    resource.qrc \
    resource.qrc
