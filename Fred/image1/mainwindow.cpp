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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new PictLabel;
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(imageLabel);

    //ui->scrollAreaPict->setWidget(imageLabel);
    //PictLabel jj = (PictLabel) ui->scrollAreaPict->widget();

    //setCentralWidget(ui->scrollAreaPict);
    pdis =new PicDisplay();
    pdis->setScrollArea(imageLabel);
    setCentralWidget(pdis);
    QObject::connect(imageLabel,SIGNAL(signalNewPixelPicked()),pdis,SLOT(on_refreshPixelProperties()));
    updateActionsWithoutImage();

    //ui->scrollAreaPict->setWidgetResizable(false); AVOIR !!!

    //ui->statusbar->insertWidget(0,new PicDisplay());
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
    scaleFactor = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete imageLabel;
    delete scrollArea;
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
    //const QImage imageCst = *principal;

    //this->setPixmap(QPixmap::fromImage(imageCst));
      //imageLabel->setPixmap(QPixmap::fromImage(image));
    //imageLabel->setPixmap(QPixmap::fromImage(image));

    pdis->resizeScrollArea(imageLabel);

    //printAct->setEnabled(true);
    //fitToWindowAct->setEnabled(true);
    updateActionsWithImage();

    //if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

    setWindowFilePath(fileName);
    return true;
}

bool MainWindow::loadFileToMerge(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);

    QImage image2 = reader.read();
    const QImage image = image2;
    imageLabel->addImageToMerge(&image2);
    pdis->resizeScrollArea(imageLabel);
    //updateActionsWithImage();
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
    QImage *imageInversee = tc->inverseColor(imageLabel->getPrincipal());
    imageLabel->setPrincipal(imageInversee);
    const QImage imageConv = *imageLabel->getPrincipal();
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);
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
    print();
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
    QImage *imageFloutee = tc->flou(imageLabel->getPrincipal());
    imageLabel->setPrincipal(imageFloutee);
    const QImage imageConv = *imageLabel->getPrincipal();
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);
}

void MainWindow::on_actionPipette_triggered()
{
    imageLabel->setMouseListenerState(10);
}

void MainWindow::on_actionSeamCarving_triggered()
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

    while (dialog.exec() == QDialog::Accepted && !loadFileToMerge(dialog.selectedFiles().first())) {}
}

void MainWindow::on_actionDeplacement_triggered()
{
    imageLabel->setMouseListenerState(12);
}

void MainWindow::on_action_Selection_triggered()
{
    imageLabel->setMouseListenerState(11);
}

