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
#include <QDialog>


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
    QObject::connect(imageLabel,SIGNAL(signalUndoVivibility()),this,SLOT(on_UndoVivibilityRedefined()));
    QObject::connect(imageLabel,SIGNAL(signalValidateCancelVivibility()),this,SLOT(on_UndoValidateCancelRedefined()));
    QObject::connect(pdis,SIGNAL(signalError()),this,SLOT(displayErrorMessage()));
    updateActionsIconDisplay(false);
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
    scaleFactor = 1;

    //loadFile("C:/Users/Fredd/Pictures/Rafael-icon.png");
    loadFile("C:/Users/Fredd/Pictures/lac.jpg");
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
    QString nom = fileName;
    imageLabel->setNomImg(nom);
    //imageLabel->adjustSize();
    pdis->resizePictureArea();
    updateActionsIconDisplay(true);

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
    QFileDialog dialog(this, tr("Ouvrir"),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void MainWindow::saveas(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);

    QImage *img = imageLabel->getImage1();
    QFileDialog dialog(this, tr("Enregistrer sous..."),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QString nomImg = dialog.getSaveFileName(this, tr("Enregistrer sous..."),
                                            imageLabel->getNomImg(),
                                            tr("Images (*.bmp);;Images (*.jpg; *.jpeg);;Images (*.png);;Images (*.ppm; *.xbm; *.xpm);;Images (*.tif))"));

    if(nomImg.isNull())
        return;

    QString ext = QFileInfo(nomImg).suffix();
    img->save(nomImg, ext.toUtf8());
}

void MainWindow::save(){
    QImage *img = imageLabel->getImage1();

    QString nomImg = imageLabel->getNomImg();

    if(nomImg.isNull())
        return;

    QString ext = QFileInfo(nomImg).suffix();
    img->save(nomImg, ext.toUtf8());
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
    updateActionsIconDisplay(true);
}

void MainWindow::updateActionsIconDisplay(bool visible)
{
    ui->action_Nouveau->setVisible(false);
    ui->action_Coller->setVisible(false);
    pdis->setResizerMode(false);
    ui->action_Fermer->setEnabled(visible);
    ui->action_Imprimer->setEnabled(visible);
    ui->actionPipette->setVisible(visible);
    ui->action_Selection->setVisible(visible);
    ui->actionZoom_avant->setEnabled(visible);
    ui->action_Zoom_arriere->setEnabled(visible);
    ui->actionSeamCarving->setVisible(visible);
    ui->actionDeplacement->setVisible(visible);
    ui->actionCrop->setVisible(visible);
    ui->actionFlou->setVisible(visible);
    ui->actionInverseCoul->setVisible(visible);
    ui->actionImageGris->setVisible(visible);
    ui->actionFusion_2->setVisible(visible);
    ui->actionHistogramme_2->setVisible(visible);
    ui->actionContour->setVisible(visible);
    ui->actionZoom_avant->setVisible(visible);
    ui->actionRotation_90_Horaire->setEnabled(visible);
    ui->action_Rotation_90_antihoraire->setEnabled(visible);
    ui->actionRotation_180->setEnabled(visible);
    ui->action_Copier->setVisible(visible);
    ui->action_Couper->setVisible(visible);
    ui->action_Enregistrer_sous->setEnabled(visible);
    ui->action_Enregistrer->setEnabled(visible);
    this->on_UndoVivibilityRedefined();
    this->on_UndoValidateCancelRedefined();
    this->pdis->updateDisplay();
}


void MainWindow::updateActionsIconAccess(bool access)
{
    ui->action_Fermer->setEnabled(access);
    ui->action_Imprimer->setEnabled(access);
    ui->actionPipette->setEnabled(access);
    ui->action_Selection->setEnabled(access);
    ui->actionZoom_avant->setEnabled(access);
    ui->action_Zoom_arriere->setEnabled(access);
    ui->actionSeamCarving->setEnabled(access);
    ui->actionDeplacement->setEnabled(access);
    ui->actionCrop->setEnabled(access);
    ui->actionFlou->setEnabled(access);
    ui->actionInverseCoul->setEnabled(access);
    ui->actionImageGris->setEnabled(access);
    ui->actionFusion_2->setEnabled(access);
    ui->actionHistogramme_2->setEnabled(access);
    ui->actionContour->setEnabled(access);
    ui->actionZoom_avant->setEnabled(access);
    ui->actionRotation_90_Horaire->setEnabled(access);
    ui->action_Rotation_90_antihoraire->setEnabled(access);
    ui->actionRotation_180->setEnabled(access);
    ui->action_Enregistrer_sous->setEnabled(access);
    ui->action_Enregistrer->setEnabled(access);
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
    updateActionsIconAccess(false);
    TransfoCouleur *tc = new TransfoCouleur;
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
    QImage *imageInversee = tc->inverseColor(imageLabel->getSelectedImage());
    imageLabel->setSelectedImage(imageInversee);
    //const QImage imageConv = *imageLabel->getSelectedImage();
    //imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    //scaleFactor = 1.0;//scaleImage(1.5);
    updateActionsIconAccess(true);
}

void MainWindow::on_action_Ouvrir_triggered()
{
    open();
}

void MainWindow::on_action_Fermer_triggered()
{
    imageLabel->closeImages();
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
    updateActionsIconAccess(false);
    TransfoCouleur *tc = new TransfoCouleur();
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());

    QImage *imageFloutee = tc->flou(imageLabel->getSelectedImage(), pdis->getFlouMode(), pdis->getFlouTaille());
    imageLabel->setPrincipal(imageFloutee);
    const QImage imageConv = *imageLabel->getSelectedImage();
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);
    delete tc;
    updateActionsIconAccess(true);
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
    ui->action_Coller->setVisible(false);
}


void MainWindow::on_action_Copier_triggered()
{
    updateActionsIconAccess(false);
    imageLabel->pasteSelection();
    imageLabel->setMouseListenerState(12);
    imageLabel->setSecondImgAsSelect(true);
    updateActionsIconAccess(true);
}

void MainWindow::on_action_Coller_triggered()
{

}

void MainWindow::on_action_Couper_triggered()
{
    updateActionsIconAccess(false);
    imageLabel->setCouperMode(true);
    imageLabel->pasteSelection();
    imageLabel->setMouseListenerState(12);
    imageLabel->setSecondImgAsSelect(true);
    updateActionsIconAccess(true);
}

void MainWindow::on_actionImageGris_triggered()
{
    updateActionsIconAccess(false);
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
    updateActionsIconAccess(true);
}

void MainWindow::on_actionInverseCoul_triggered()
{
    updateActionsIconAccess(false);
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
    updateActionsIconAccess(true);
}

void MainWindow::on_actionFusion_2_triggered()
{
    updateActionsIconAccess(false);
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
    updateActionsIconAccess(true);
}

void MainWindow::on_actionCrop_triggered()
{
    imageLabel->setMouseListenerState(110);
}

void MainWindow::on_actionValider_triggered()
{
    updateActionsIconAccess(false);
    imageLabel->validateTransfo();
    pdis->resizePictureArea();
    updateActionsIconAccess(true);
}

void MainWindow::on_actionRotation_90_Horaire_triggered()
{
    updateActionsIconAccess(false);
    ImageResizer *resizer = new ImageResizer;
    QImage *rotatedImg =resizer->rotateImage90(imageLabel->getSelectedImage(),true);
    imageLabel->setPrincipal(rotatedImg);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
    updateActionsIconAccess(true);
}


void MainWindow::on_action_Rotation_90_antihoraire_triggered()
{
    updateActionsIconAccess(false);
    ImageResizer *resizer = new ImageResizer;
    QImage *rotatedImg =resizer->rotateImage90(imageLabel->getSelectedImage(),false);
    imageLabel->setPrincipal(rotatedImg);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
    updateActionsIconAccess(true);
}


void MainWindow::on_actionRotation_180_triggered()
{
    updateActionsIconAccess(false);
    ImageResizer *resizer = new ImageResizer;
    QImage *rotatedImg =resizer->rotateImage180(imageLabel->getSelectedImage());
    imageLabel->setPrincipal(rotatedImg);
    imageLabel->setInitialContext();
    pdis->resizePictureArea();
    updateActionsIconAccess(true);
}

void MainWindow::on_action_Annuler_triggered()
{
    updateActionsIconAccess(false);
    imageLabel->undoLast();
    pdis->resizePictureArea();
    updateActionsIconAccess(true);
}

void MainWindow::on_actionRecadrer_triggered()
{
    updateActionsIconAccess(false);
    pdis->setResizerMode(true);
    updateActionsIconAccess(true);
}

void MainWindow::on_actionHistogramme_triggered()
{
    updateActionsIconAccess(false);
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
        tc->histogramme(imageSrc,pdis->getYUVMode());
    }
    updateActionsIconAccess(true);
}

void MainWindow::actionContour(int mode)
{
    updateActionsIconAccess(false);
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;

        imageLabel->setPrincipal(tc->contour(imageSrc, mode));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
    updateActionsIconAccess(true);
}

void MainWindow::on_actionContour_triggered()
{
    updateActionsIconAccess(false);
    actionContour(1);
    updateActionsIconAccess(true);
}


void MainWindow::on_actionHistogramme_2_triggered()
{
    updateActionsIconAccess(false);
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
        tc->histogramme(imageSrc,pdis->getYUVMode());
    }
    updateActionsIconAccess(true);
}

void MainWindow::on_actionRehaussement_triggered()
{
    updateActionsIconAccess(false);
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        imageLabel->setPrincipal(tc->rehaussement(imageSrc, pdis->getRehaussCoef()));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
    updateActionsIconAccess(true);
}

void MainWindow::on_actionEtalement_triggered()
{
    updateActionsIconAccess(false);
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;

        imageLabel->setPrincipal(tc->etalement(imageSrc, pdis->getEtalAlpha(), pdis->getEtalBeta()));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
    updateActionsIconAccess(true);
}

void MainWindow::on_actionEgalisation_triggered()
{
    updateActionsIconAccess(false);
    QImage *imageSrc = imageLabel->getSelectedImage();
    if (imageSrc != NULL)
    {
        TransfoCouleur *tc = new TransfoCouleur;
        imageLabel->setPrincipal(tc->egalisation(imageSrc));
        const QImage imageConv = *imageLabel->getSelectedImage();
        imageLabel->setPixmap(QPixmap::fromImage(imageConv));
        scaleFactor = 1.0;//scaleImage(1.5);
    }
    updateActionsIconAccess(true);
}

void MainWindow::on_actionSupprimer_triggered()
{
    updateActionsIconAccess(false);
    imageLabel->setInitialContext();
}

void MainWindow::on_action_Enregistrer_sous_triggered()
{
    updateActionsIconAccess(false);
    saveas();
    updateActionsIconAccess(true);
}

void MainWindow::on_action_Enregistrer_triggered()
{
    updateActionsIconAccess(false);
    save();
    updateActionsIconAccess(true);
}

void MainWindow::on_actionFiltre_Scharr_triggered()
{
    updateActionsIconAccess(false);
    actionContour(2);
    updateActionsIconAccess(true);
}

void MainWindow::on_actionFiltre_Sobel_triggered()
{
    updateActionsIconAccess(false);
    actionContour(1);
    updateActionsIconAccess(true);
}

void MainWindow::on_action_Filtre_Prewitt_triggered()
{
    updateActionsIconAccess(false);
    actionContour(0);
    updateActionsIconAccess(true);
}

void MainWindow::on_UndoVivibilityRedefined()
{
    bool visibility = imageLabel->getUndoVisibility();
    ui->action_Annuler->setVisible(visibility);
}

void MainWindow::on_UndoValidateCancelRedefined()
{
    bool visibility = imageLabel->getValidateCancelVisibility();
    ui->actionValider->setVisible(visibility);
    ui->actionSupprimer->setVisible(visibility);
    ui->action_Copier->setVisible(imageLabel->getCutCopyVisibility());
    ui->action_Couper->setVisible(imageLabel->getCutCopyVisibility());
}

void MainWindow::on_action_Flou_moyenneur_triggered()
{
    updateActionsIconAccess(false);
    TransfoCouleur *tc = new TransfoCouleur;
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());

    QImage *imageFloutee = tc->flou(imageLabel->getSelectedImage(), 0, pdis->getFlouTaille());
    imageLabel->setPrincipal(imageFloutee);
    const QImage imageConv = *imageLabel->getSelectedImage();
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);
    updateActionsIconAccess(true);
}

void MainWindow::on_action_Flou_gaussien_triggered()
{
    updateActionsIconAccess(false);
    TransfoCouleur *tc = new TransfoCouleur;
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());

    QImage *imageFloutee = tc->flou(imageLabel->getSelectedImage(), 1, pdis->getFlouTaille());
    imageLabel->setPrincipal(imageFloutee);
    const QImage imageConv = *imageLabel->getSelectedImage();
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);
    updateActionsIconAccess(true);
}

void MainWindow::on_actionSeamCarving_triggered()
{
    updateActionsIconAccess(false);
    imageLabel->getSeamCarver()->initImage(imageLabel->getImage1());
    int maxNbLignes = imageLabel->getSeamCarver()->initStrengthRoutes(imageLabel->getImage1()->height()/2);
    pdis->setSeamDisplay(maxNbLignes);
    updateActionsIconAccess(true);
}

void MainWindow::displayErrorMessage()
{
    QMessageBox msgBox;
    msgBox.setText(pdis->getErrorMsg());
    msgBox.exec();
}
