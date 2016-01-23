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
    displayImage2Selector(false);
    displayFlouProperties(false);
    displayRehausProperties(false);
    displayEtalProperties(false);
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

int PicDisplay::getYUVMode()
{
    int ret = (this->ui->radioButton_YUV->isChecked()) ? 1 : 0;
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
    QString val1,val2,val3,val4;
    val4= QString::number(qAlpha(color));
    ui->valCoulA->setText(val4);

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
            displayImage2Selector(false);
        } else
        {
            displayImage2Selector(true);
        }

    } else
    {
        ui->libTailleGeneral->setVisible(false);
        ui->libTailleHeigtht->setVisible(false);
        ui->libTailleWidth->setVisible(false);
        ui->lineEdit_Width->setVisible(false);
        ui->lineEdit_Height->setVisible(false);

        displayImage2Selector(false);
    }
}

void PicDisplay::displayImage2Selector(bool visible)
{
    bool image1Selected = !imageLabel->getSecondImgAsSelect();
    if (image1Selected) {
        ui->radioButtonImg1->setChecked(image1Selected);
        ui->radioButtonImg2->setChecked(!image1Selected);
    }
    ui->radioButtonImg1->setVisible(visible);
    ui->radioButtonImg2->setVisible(visible);
    ui->val_alpha_img1->setVisible(visible);
    ui->val_alpha_img2->setVisible(visible);
    ui->horizontalSlider_img1->setVisible(visible);
    ui->horizontalSlider_img2->setVisible(visible);
}

void PicDisplay::displayFlouProperties(bool visible)
{
    //ui->checkBoxFlou->setChecked(visible);
    ui->libFlou1->setVisible(visible);
    ui->comboBoxFlou1->setVisible(visible);
    ui->lineEditFlou1->setVisible(visible);
}

void PicDisplay::displayRehausProperties(bool visible)
{
    ui->checkBox_Rehaus->setChecked(visible);
    ui->lib_Rehaus->setVisible(visible);
    ui->lineEdit_Rehaus->setVisible(visible);
}

void PicDisplay::displayEtalProperties(bool visible)
{
    ui->checkBox_Etal->setChecked(visible);
    ui->lib_Etal1->setVisible(visible);
    ui->lib_Etal2->setVisible(visible);
    ui->lineEdit_Etal1->setVisible(visible);
    ui->lineEdit_Etal2->setVisible(visible);
}

void PicDisplay::displayFiltreProperties(bool visible)
{
    ui->checkBox_Filtre->setChecked(visible);
    ui->lib_Filtre1->setVisible(visible);
    ui->lineEdit_Filtre->setVisible(visible);
    ui->pushButtonFiltreEdition->setVisible(visible);
    ui->pushButton_FiltreLaunch->setVisible(visible);
}

void PicDisplay::on_checkBoxFlou_stateChanged(int arg1)
{
    displayFlouProperties(arg1 != Qt::Unchecked);
}

void PicDisplay::on_checkBox_Rehaus_stateChanged(int arg1)
{
    displayRehausProperties(arg1 != Qt::Unchecked);
}

void PicDisplay::on_checkBox_Etal_stateChanged(int arg1)
{
    displayEtalProperties(arg1 != Qt::Unchecked);
}

void PicDisplay::on_checkBox_Filtre_stateChanged(int arg1)
{
    displayFiltreProperties(arg1 != Qt::Unchecked);
}

void PicDisplay::on_radioButtonImg1_clicked()
{
    this->imageLabel->setSecondImgAsSelect(false);
}

void PicDisplay::on_radioButtonImg2_clicked()
{
    this->imageLabel->setSecondImgAsSelect(true);
}

void PicDisplay::on_horizontalSlider_img1_valueChanged(int value)
{
    ui->val_alpha_img1->setText(QString::number(value));
    this->imageLabel->setAlphaImg1(value);
    this->imageLabel->drawImage();
}

void PicDisplay::on_horizontalSlider_img2_valueChanged(int value)
{
    ui->val_alpha_img2->setText(QString::number(value));
    this->imageLabel->setAlphaImg2(value);
    this->imageLabel->drawImage();
}

void PicDisplay::on_pushButtonFiltreEdition_clicked()
{

}

void PicDisplay::on_pushButton_FiltreLaunch_clicked()
{

}

