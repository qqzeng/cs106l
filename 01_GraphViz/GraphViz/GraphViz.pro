QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    simplegraph.cpp

HEADERS += \
    simplegraph.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    res/10clique \
    res/10grid \
    res/10line \
    res/127binary-tree \
    res/2line \
    res/30clique \
    res/30cycle \
    res/31binary-tree \
    res/32wheel \
    res/3grid \
    res/50line \
    res/5clique \
    res/5grid \
    res/60cycle \
    res/63binary-tree \
    res/64wheel \
    res/8wheel \
    res/bull \
    res/cube \
    res/desargues \
    res/dodecahedron \
    res/doodad-1 \
    res/doodad-2 \
    res/doodad-3 \
    res/durer \
    res/heawood \
    res/icosahedron \
    res/mobius-kantor \
    res/moser-spindle \
    res/octahedron \
    res/petersen \
    res/star \
    res/tesseract \
    res/tietze \
    res/triangle

CONFIG+= console
