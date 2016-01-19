#include "picdisplay.h"
#include "ui_picdisplay.h"
#include "pictlabel.h"
#include "TransfoCouleur.h"
#include <QScrollBar>

PicDisplay::PicDisplay(PictLabel *imageLabel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicDisplay)
{
    ui->setupUi(this);
    ui->scrollAreaP->setWidgetResizable(false);
        ui->scrollAreaP->setWidget(imageLabel);
    this->imageLabel=imageLabel;
        ui->radioButtonRGB->setChecked(true);
}

PicDisplay::~PicDisplay()
{
    delete ui;
}

int PicDisplay:: getResizedWidthRequired()
{
    int ret=imageLabel->getSelectedImage()->width();
    QLineEdit *q1=ui->lineEdit_Width;
    if (!q1->text().isEmpty())
        ret=q1->text().toInt();
    return ret;
}

int PicDisplay::getResizedHeightRequired()
{
    int ret=imageLabel->getSelectedImage()->height();
    QLineEdit *q1=ui->lineEdit_Height;
    if (!q1->text().isEmpty())
        ret=q1->text().toInt();
    return ret;
}


void PicDisplay::refreshPixelProperties()
{
    //PictLabel *jj = static_cast<PictLabel*>(ui->scrollAreaP->widget());
    QRgb color = this->imageLabel->getColorPicked();
    QPoint position = this->imageLabel->getPixelPicked();
    QString valx= QString::number(position.x());
    ui->valPosX->setText(valx);
    QString valy= QString::number(position.y());
    ui->valPosY->setText(valy);
    QString val1,val2,val3;

    if (ui->radioButtonRGB->isChecked())
    {
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

/*void PicDisplay::setScrollArea(PictLabel *imageLabel)
{
    ui->scrollAreaP->setWidgetResizable(false);
    ui->scrollAreaP->setWidget(imageLabel);
}*/

void PicDisplay::resizePictureArea()
{
    this->imageLabel->adjustSize();
    QImage *imgMax = this->imageLabel->getPrincipal();
    ui->scrollAreaP->resize(imgMax->width()+5,imgMax->height()+5);
    this->adjustSize();
    this->imageLabel->adjustSize();
    this->imageLabel->drawImage();
}

void PicDisplay::scaleImage(double factor)
{
    /*Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());*/

      //adjustScrollBar( ui->scrollAreaP->horizontalScrollBar(), factor);
       //adjustScrollBar( ui->scrollAreaP->verticalScrollBar(), factor);
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
    refreshPixelProperties();
}

void PicDisplay::on_resizingRequired()
{
    /*ui->libTailleWidth->setText("W:"+QString::number(imageLabel->getSelectedImage()->width()));
    ui->libTailleHeigtht->setText("H:"+QString::number(imageLabel->getSelectedImage()->height()));
    ui->radioButtonImg1->setChecked(imageLabel->getSelectedImage()==imageLabel->getImage1());
    ui->radioButtonImg2->setChecked(imageLabel->getSelectedImage()!=imageLabel->getImage1());
    ui->radioButtonImg2->setVisible(imageLabel->getImage2()!=NULL);

    resizePictureArea();*/
}

void PicDisplay::on_displayRedefined()
{
    updateDisplay();
}

void PicDisplay::updateDisplay()
{
    if (imageLabel->getSelectedImage() != NULL)
    {
        ui->libTailleGeneral->setVisible(true);
        ui->libTailleHeigtht->setText("H:"+QString::number(imageLabel->getSelectedImage()->height()));
        ui->libTailleHeigtht->setVisible(true);
        ui->libTailleWidth->setText("W:"+QString::number(imageLabel->getSelectedImage()->width()));
        ui->libTailleWidth->setVisible(true);
        ui->lineEdit_Width->setVisible(true);
        ui->lineEdit_Height->setVisible(true);

        if (imageLabel->getImage2() == NULL)
        {
            ui->radioButtonImg1->setVisible(false);
            ui->radioButtonImg2->setVisible(false);
        } else
        {
            ui->radioButtonImg1->setVisible(true);
            ui->radioButtonImg2->setVisible(true);
        }

    } else
    {
        ui->libTailleGeneral->setVisible(false);
        ui->libTailleHeigtht->setVisible(false);
        ui->libTailleWidth->setVisible(false);
        ui->lineEdit_Width->setVisible(false);
        ui->lineEdit_Height->setVisible(false);
        ui->radioButtonImg1->setVisible(false);
        ui->radioButtonImg2->setVisible(false);
    }
}
