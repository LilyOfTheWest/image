QT += widgets
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer.h \
    picdisplay.h \
    pictlabel.h \
    transfocouleur.h \
    kernelconv.h
SOURCES       = imageviewer.cpp \
                main.cpp \
    picdisplay.cpp \
    pictlabel.cpp \
    transfocouleur.cpp \
    kernelconv.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target


wince {
   DEPLOYMENT_PLUGIN += qjpeg qgif
}

FORMS += \
    picdisplay.ui

RESOURCES += \
    res.qrc
