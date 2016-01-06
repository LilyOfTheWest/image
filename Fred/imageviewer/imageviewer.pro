QT += widgets
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer.h \
    picdisplay.h \
    qkernelconv.h
SOURCES       = imageviewer.cpp \
                main.cpp \
    picdisplay.cpp \
    qkernelconv.cpp

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
