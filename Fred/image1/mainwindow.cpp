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

    //ui->scrollAreaPict->setWidgetResizable(false); AVOIR !!!

    //ui->statusbar->insertWidget(0,new PicDisplay());
    createActions();
    createMenus();
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
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

    //Exemple de code de dessin - substitut au calque
    /*QPainter p;
    p.begin(&image2);
    p.setPen(QColor(Qt::color0));
    p.setBrush(Qt::NoBrush);
    p.drawRect(QRect(30,30,400,400));
    p.end();*/
    const QImage image = image2;

    imageLabel->addImage(&image2);
    //const QImage imageCst = *principal;

    //this->setPixmap(QPixmap::fromImage(imageCst));
      //imageLabel->setPixmap(QPixmap::fromImage(image));
    //imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    pdis->resizeScrollArea(imageLabel);

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

    setWindowFilePath(fileName);
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
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}
void MainWindow::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    ui->scrollAreaPict->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
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
void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    inverseColorAct = new QAction(tr("Inverseur des couleurs"), this);
    inverseColorAct->setShortcut(tr("Ctrl+N"));
    inverseColorAct->setEnabled(false);
    connect(inverseColorAct, SIGNAL(triggered()), this, SLOT(inverseColor()));

    prodConvAct = new QAction(tr("Produit convolution Moyenneur rudimentaire"), this);
    prodConvAct->setShortcut(tr("Ctrl+W"));
    prodConvAct->setEnabled(false);
    connect(prodConvAct, SIGNAL(triggered()), this, SLOT(prodConv()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(inverseColorAct);
    viewMenu->addAction(prodConvAct);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::updateActions()
{
    inverseColorAct->setEnabled(!fitToWindowAct->isChecked());
    prodConvAct->setEnabled(!fitToWindowAct->isChecked());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    //adjustScrollBar(ui->scrollAreaPict->horizontalScrollBar(), factor);
    //adjustScrollBar(ui->scrollAreaPict->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
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

void MainWindow::prodConv()
{
    /**imageL = kernelConv->produitConv(imageLabel->setPrincipal();
    const QImage imageConv = *imageL;
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);*/
}

void MainWindow::on_actionFlouter_triggered()
{
    TransfoCouleur *tc = new TransfoCouleur;
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaPict->widget());
    QImage *imageFloutee = tc->flou(imageLabel->getPrincipal());
    imageLabel->setPrincipal(imageFloutee);
    const QImage imageConv = *imageLabel->getPrincipal();
    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
    scaleFactor = 1.0;//scaleImage(1.5);
}

void MainWindow::on_action_Open_triggered()
{
    open();
}

void MainWindow::on_actionPick_Color_triggered()
{
    imageLabel->setMouseListenerState(10);
}

void MainWindow::on_actionSelect_triggered()
{
    imageLabel->setMouseListenerState(11);
}
