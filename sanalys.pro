# -------------------------------------------------
# Project created by QtCreator 2011-11-11T11:38:09
# -------------------------------------------------
# include(C:\temp\qwt-6.0.1\qwt-6.0.1\qwt.prf)
QT += xml
INCLUDEPATH += C:\Users\Andrey\Downloads\qwt-6.0.1\qwt-6.0.1\src
INCLUDEPATH += C:\Users\Andrey\Downloads\fftw-3.3-dll32

# LIBS += C:\temp\qwt-6.0.1\qwt-6.0.1\lib\libqwt.a
LIBS += C:\Users\Andrey\Downloads\qwt-6.0.1\qwt-6.0.1\lib\libqwt.a
LIBS += C:\Users\Andrey\Downloads\fftw-3.3-dll32\libfftw3-3.dll
TARGET = sanalys
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    plot.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui
RESOURCES += 
