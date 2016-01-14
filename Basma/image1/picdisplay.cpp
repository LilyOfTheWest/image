#include "picdisplay.h"
#include "ui_picdisplay.h"
#include "pictlabel.h"
#include "TransfoCouleur.h"
#include <QScrollBar>

PicDisplay::PicDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicDisplay)
{
    ui->setupUi(this);
    ui->radioButtonRGB->setChecked(true);
}

PicDisplay::~PicDisplay()
{
    delete ui;
}

void PicDisplay::refreshPixelProperties()
{
    PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaP->widget());
    QRgb color = jj->getColorPicked();
    QPoint position = jj->getPixelPicked();
    QString valx= QString::number(position.x());
    ui->valPosX->setText(valx);
    QString valy= QString::number(position.y());
    ui->valPosY->setText(valy);
    QString val1,val2,val3;

    if (ui->radioButtonRGB->isChecked())
    {
        ui->libLibre->setText("RGB");
        ui->libCoul1->setText("R:");
        ui->libCoul2->setText("G:");
        ui->libCoul3->setText("B:");
        val1= QString::number(qRed(color));
        ui->valCoul1->setText(val1);
        val2= QString::number(qGreen(color));
        ui->valCoul2->setText(val2);
        val3= QString::number(qBlue(color));
        ui->valCoul3->setText(val3);

    } else
    {
        ui->libLibre->setText("YUV");
        ui->libCoul1->setText("Y:");
        ui->libCoul2->setText("U:");
        ui->libCoul3->setText("V:");
        TransfoCouleur *tc = new TransfoCouleur;
        val1= QString::number(tc->get_YVal_Pixel_FromRgb(color));
        ui->valCoul1->setText(val1);
        val2= QString::number(tc->get_UVal_Pixel_FromRgb(color));
        ui->valCoul2->setText(val2);
        val3= QString::number(tc->get_VVal_Pixel_FromRgb(color));
        ui->valCoul3->setText(val3);
    }
}

void PicDisplay::on_pushButton_clicked()
{
    if (ui->radioButtonRGB->isChecked())
    {
        ui->libLibre->setText("OO");
    } else
    {
        ui->libLibre->setText("FF");
    }
}

void PicDisplay::setScrollArea(PictLabel *imageLabel)
{
    ui->scrollAreaP->setWidgetResizable(false);
    ui->scrollAreaP->setWidget(imageLabel);
    ui->scrollAreaP->setMinimumHeight(500);
    ui->scrollAreaP->setMinimumWidth(10000);
    ui->libLibre->setText("YEAH !");
}

void PicDisplay::resizeScrollArea(PictLabel *imageLabel)
{
    ui->scrollAreaP->setWidgetResizable(false);
    int y = imageLabel->height();
    ui->scrollAreaP->setMinimumHeight(500);
    ui->scrollAreaP->setMinimumWidth(imageLabel->width());
    ui->libLibre->setText("Y§YEAH !");
}

void PicDisplay::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void PicDisplay::scaleImage(double factor)
{
    /*Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());*/

    adjustScrollBar( ui->scrollAreaP->horizontalScrollBar(), factor);
    adjustScrollBar( ui->scrollAreaP->verticalScrollBar(), factor);
/*
    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);*/
}

void PicDisplay::on_radioButtonRGB_clicked()
{
    refreshPixelProperties();
}

void PicDisplay::on_radioButton_YUV_clicked()
{
    refreshPixelProperties();
}

void PicDisplay::on_refreshPixelProperties()
{
    ui->libLibre->setText("AA !");
    refreshPixelProperties();
}
