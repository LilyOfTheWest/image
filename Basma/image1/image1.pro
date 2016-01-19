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
    couleurs.h \
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
    couleurs.cpp \
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
    couleurs.ui \
    histogramme.ui \
    fusion.ui

RESOURCES += \
    res.qrc

