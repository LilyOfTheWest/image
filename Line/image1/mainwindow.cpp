#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "picdisplay.h"
#include "pictlabel.h"
#include "TransfoCouleur.h"
#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#endif
#include "kernelconv.h"
#include "seamcarver.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new PictLabel;
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    QScrollArea *scrollArea = new QScrollArea(this);
    pdis =new PicDisplay(imageLabel,this);
    scrollArea->setWidget(pdis);
    setCentralWidget(scrollArea);
    QObject::connect(imageLabel,SIGNAL(signalNewPixelPicked()),pdis,SLOT(on_refreshPixelProperties()));
    QObject::connect(imageLabel,SIGNAL(signalResizingRequired()),pdis,SLOT(on_resizingRequired()));
    QObject::connect(imageLabel,SIGNAL(signalRedisplayRequired()),pdis,SLOT(on_displayRedefined()));
    updateActionsWithoutImage();
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
    scaleFactor = 1;

    //loadFile("C:/Users/Fredd/Pictures/Rafael-icon.png");
    //loadFile("D:/Lily/Bureau/Dossier Line/M1-Info/PROJET/image/Fred/imageviewer/Rio-2-Official-Trailer-3-40.jpg");
    //on_actionSeamCarving_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);

    QImage image2 = reader.read();
    if (image2.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        imageLabel->setPixmap(QPixmap());
        imageLabel->adjustSize();
        return false;
    }

    const QImage image = image2;
    imageLabel->setPrincipal(&image2);
    //imageLabel->adjustSize();
    pdis->resizePictureArea();
    updateActionsWithImage();

    //if (!fitToWindowAct->isChecked())

        //imageLabel->adjustSize();
        //QWidget *uu=ui->centralwidget();
        //uu->resize(image2.width(),image2.height());
        //pdis->adjustSize();

    setWindowFilePath(fileName);
    return true;
}

bool MainWindow::loadFileToMerge(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);

    QImage image2 = reader.read();
    imageLabel->addImageToMerge(&image2);
    pdis->resizePictureArea();
    return true;
}

void MainWindow::open()
{
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void MainWindow::print()
{
    Q_ASSERT(imageLabel->pixmap());
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}

void MainWindow::normalSize()
{
    scaleFactor = 1.0;
    imageLabel->setScaleFactor(scaleFactor);
    imageLabel->adjustSize();
}
void MainWindow::fitToWindow()
{
    //bool fitToWindow = fitToWindowAct->isChecked();
    //ui->scrollAreaPict->setWidgetResizable(fitToWindow);
    //if (!fitToWindow) {
    //    normalSize();
    //}
    updateActionsWithImage();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}
//void MainWindow::createActions()
//{
//    normalSizeAct = new QAction(tr("&Normal Size"), this);
//    normalSizeAct->setShortcut(tr("Ctrl+S"));
//    normalSizeAct->setEnabled(false);
//    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

//    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
//    fitToWindowAct->setEnabled(false);
//    fitToWindowAct->setCheckable(true);
//    fitToWindowAct->setShortcut(tr("Ctrl+F"));
//    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

//    aboutAct = new QAction(tr("&About"), this);
//    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

//    aboutQtAct = new QAction(tr("About &Qt"), this);
//    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
//}


void MainWindow::updateActionsWithoutImage()
{
    ui->action_Fermer->setEnabled(false);
    ui->action_Imprimer->setEnabled(false);
    ui->actionPipette->setVisible(false);
    ui->action_Selection->setVisible(false);
    ui->actionZoom_avant->setEnabled(false);
    ui->action_Zoom_arriere->setEnabled(false);
    ui->actionSeamCarving->setVisible(false);
    ui->action_Copier->setVisible(false);
    ui->action_Couper->setVisible(false);
    ui->action_Coller->setVisible(false);

    this->pdis->updateDisplay();

}


void MainWindow::updateActionsWithImage()
{
    ui->action_Fermer->setEnabled(true);
    ui->action_Imprimer->setEnabled(true);
    ui->actionPipette->setVisible(true);
    ui->action_Selection->setVisible(true);
    ui->actionZoom_avant->setEnabled(true);
    ui->action_Zoom_arriere->setEnabled(true);
    ui->actionSeamCarving->setVisible(true);
    this->pdis->updateDisplay();
//    inverseColorAct->setEnabled(!fitToWindowAct->isChecked());
//    prodConvAct->setEnabled(!fitToWindowAct->isChecked());
//    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
//    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
//    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->setScaleFactor(scaleFactor);
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    //adjustScrollBar(ui->scrollAreaPict->horizontalScrollBar(), factor);
    //adjustScrollBar(ui->scrollAreaPict->verticalScrollBar(), factor);

    ui->actionZoom_avant->setEnabled(scaleFactor < 3.0);
    ui->action_Zoom_arriere->setEnabled(scaleFactor > 0.333);
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

/*void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(zoomInAct);
}*/

void MainWindow::inverseColor()
{
    TransfoCouleur *tc = new TransfoCouleur;
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
    QImage *imageInversee = tc->inverseColor(imageLabel->getSelectedImage());
    imageLabel->setSelectedImage(imageInversee);
    //const QImage imageConv = *imageLabel->getSelectedImage();
    //imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    //scaleFactor = 1.0;//scaleImage(1.5);
}

void MainWindow::on_action_Ouvrir_triggered()
{
    open();
}

void MainWindow::on_action_Fermer_triggered()
{
    close();
}

void MainWindow::on_action_Imprimer_triggered()
{
    //print();
    ui->action_Copier->setVisible(false);
    ui->action_Couper->setVisible(false);
    ui->action_Coller->setVisible(false);
}

void MainWindow::on_actionZoom_avant_triggered()
{
    zoomIn();
}

void MainWindow::on_action_Zoom_arriere_triggered()
{
    zoomOut();
}

void MainWindow::on_actionFlou_triggered()
{
    TransfoCouleur *tc = new TransfoCouleur;
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
    QImage *imageFloutee = tc->flou(imageLabel->getSelectedImage());
    imageLabel->setPrincipal(imageFloutee);
    const QImage imageConv = *imageLabel->getSelectedImage();
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);
}

void MainWindow::on_actionPipette_triggered()
{
    imageLabel->setMouseListenerState(10);
}

void MainWindow::on_actionDeplacement_triggered()
{
    imageLabel->setMouseListenerState(12);
}

void MainWindow::on_action_Selection_triggered()
{
    imageLabel->setMouseListenerState(11);
    ui->action_Copier->setVisible(true);
    ui->action_Couper->setVisible(true);
    ui->action_Coller->setVisible(true);
}


void MainWindow::on_action_Copier_triggered()
{

}

void MainWindow::on_action_Coller_triggered()
{
    imageLabel->pasteSelection();
    imageLabel->setMouseListenerState(12);
    imageLabel->setSecondImgAsSelect(true);
}

void MainWindow::on_action_Couper_triggered()
{
    imageLabel->setCouperMode(true);
}

void MainWindow::on_actionImageGris_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
        QImage *imageGris = tc->gris(imageSrc);
        imageLabel->setPrincipal(imageGris);
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
}

void MainWindow::on_actionInverseCoul_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
        QImage *imageInversee = tc->inverseColor(imageLabel->getSelectedImage());
        imageLabel->setPrincipal(imageInversee);
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
}

void MainWindow::on_actionFusion_2_triggered()
{
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open second File to merge"),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted && !loadFileToMerge(dialog.selectedFiles().first())) {}
}

void MainWindow::on_actionCrop_triggered()
{
    imageLabel->setMouseListenerState(110);
}

void MainWindow::on_actionValider_triggered()
{
    imageLabel->validateTransfo();
    pdis->resizePictureArea();
}

void MainWindow::on_actionRotation_90_Horaire_triggered()
{
    ImageResizer *resizer = new ImageResizer;
    QImage *rotatedImg =resizer->rotateImage90(imageLabel->getSelectedImage(),true);
    imageLabel->setPrincipal(rotatedImg);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
}


void MainWindow::on_action_Rotation_90_antihoraire_triggered()
{
    ImageResizer *resizer = new ImageResizer;
    QImage *rotatedImg =resizer->rotateImage90(imageLabel->getSelectedImage(),false);
    imageLabel->setPrincipal(rotatedImg);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
}


void MainWindow::on_actionRotation_180_triggered()
{
    ImageResizer *resizer = new ImageResizer;
    QImage *rotatedImg =resizer->rotateImage180(imageLabel->getSelectedImage());
    imageLabel->setPrincipal(rotatedImg);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
}

void MainWindow::on_action_Annuler_triggered()
{
    imageLabel->undoLast();
    pdis->resizePictureArea();
}

void MainWindow::on_actionRecadrer_triggered()
{
    //loadFile("C:/Users/Fredd/Pictures/Rafael-icon.png");
    ImageResizer *resizer = new ImageResizer;
    QImage *resizedImg =resizer->resizeImage(imageLabel->getSelectedImage(),pdis->getResizedWidthRequired(),pdis->getResizedHeightRequired());
    imageLabel->setPrincipal(resizedImg);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
}

void MainWindow::on_actionSeamCarving_triggered()
{
    //loadFile("C:/Users/Fredd/Pictures/Rafael-icon.png");
    SeamCarver *sc = new SeamCarver(imageLabel->getSelectedImage(),this);
    sc->init();
    QImage *imageSeamCarved = sc->extendWidth(20);
    imageLabel->setPrincipal(imageSeamCarved);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
}

void MainWindow::on_actionHistogramme_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
        tc->histogramme(imageSrc,pdis->getYUVMode());
    }
}

void MainWindow::on_actionContour_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        // CABLER LE MODE DE CONTOUR
        imageLabel->setPrincipal(tc->contour(imageSrc, 0));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
}


void MainWindow::on_actionHistogramme_2_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
        tc->histogramme(imageSrc,pdis->getYUVMode());
    }
}

void MainWindow::on_actionRehaussement_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        // RECUPERER LA VALEUR DE ALPHA ! rehaussement(imageSrc, alpha)
        imageLabel->setPrincipal(tc->rehaussement(imageSrc, 0.5));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
}

void MainWindow::on_actionEtalement_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        // RECUPERER LES VALEURS DE ALPHA ET BETA ! etalement(imageSrc, alpha, beta)
        imageLabel->setPrincipal(tc->etalement(imageSrc, 1.5, 1));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
}

void MainWindow::on_actionEgalisation_triggered()
{
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        imageLabel->setPrincipal(tc->egalisation(imageSrc));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
}

void MainWindow::on_actionSupprimer_triggered()
{
    imageLabel->setInitialContext();
}
