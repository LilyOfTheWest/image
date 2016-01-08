QT += widgets
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer.h \
    picdisplay.h \
    pictlabel.h \
    transfocouleur.h \
    kernelconv.h \
    mainwindow.h \
    imageanalyse.h \
    kernelconvmoyenneur.h
SOURCES       = imageviewer.cpp \
                main.cpp \
    picdisplay.cpp \
    pictlabel.cpp \
    transfocouleur.cpp \
    kernelconv.cpp \
    mainwindow.cpp \
    imageanalyse.cpp \
    kernelconvmoyenneur.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target


wince {
   DEPLOYMENT_PLUGIN += qjpeg qgif
}

FORMS += \
    picdisplay.ui \
    mainwindow.ui

RESOURCES += \
    res.qrc
