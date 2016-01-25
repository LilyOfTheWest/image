QT += widgets
qtHaveModule(printsupport): QT += printsupport

HEADERS       = \
    picdisplay.h \
    pictlabel.h \
    transfocouleur.h \
    kernelconv.h \
    mainwindow.h \
    imageanalyse.h \
    kernelconvmoyenneur.h \
    kernelconvbinomial.h \
    imageresizer.h \
    seamcarver.h
SOURCES       = \
                main.cpp \
    picdisplay.cpp \
    pictlabel.cpp \
    transfocouleur.cpp \
    kernelconv.cpp \
    mainwindow.cpp \
    imageanalyse.cpp \
    kernelconvmoyenneur.cpp \
    kernelconvbinomial.cpp \
    imageresizer.cpp \
    seamcarver.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target


wince {
   DEPLOYMENT_PLUGIN += qjpeg qgif
}

FORMS += \
    picdisplay.ui \
    mainwindow.ui \
    histogramme.ui \
    fusion.ui

RESOURCES += \
    res.qrc

CONFIG+=qwt
