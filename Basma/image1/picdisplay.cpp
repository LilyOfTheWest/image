#include "picdisplay.h"
#include "ui_picdisplay.h"
#include "pictlabel.h"
#include "TransfoCouleur.h"
#include <QMessageBox>
#include <QDialog>
#include <QScrollBar>
#include <QTableWidget>
#include "kernelconv.h"
#include "kernelconvmoyenneur.h"

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
    displayFiltreProperties(false);
    displaySeamProperties(false);
    ui->checkBoxSeam->setEnabled(false);
    tailleFiltre = 3;
}

PicDisplay::~PicDisplay()
{
    delete ui;
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
    ui->pushButtonResize->setVisible((visible)&&(ui->val_alpha_img1->text().size()>0));
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

void PicDisplay::displaySeamProperties(bool visible)
{
    ui->checkBoxSeam->setChecked(visible);
    ui->checkSeamVisu->setVisible(visible);
    ui->comboBoxSeamActions->setVisible(visible);
    ui->checkBoxSeamCompress->setVisible(visible);
    ui->lineEditSeamSize->setVisible(visible);
    ui->horizontalSliderSeamSize->setVisible(visible);
}

void PicDisplay::on_checkBoxSeam_stateChanged(int arg1)
{
    displaySeamProperties(arg1 != Qt::Unchecked);
}

void PicDisplay::on_horizontalSliderSeamSize_valueChanged(int value)
{
    ui->lineEditSeamSize->setText(QString::number(value));
}

void PicDisplay::displaySeamCarvedImage()
{
    QImage *imageSeamCarved = imageLabel->getSeamCarver()->extendWidth(ui->horizontalSliderSeamSize->value(),
                                                                       ui->checkBoxSeamCompress->isChecked(),
                                                                       ui->checkSeamVisu->isChecked());
    imageLabel->setPrincipal(imageSeamCarved);
    imageLabel->setInitialContext();
    imageLabel->setNbSeamLinesToDisplay(ui->horizontalSliderSeamSize->value());
    ui->comboBoxSeamActions->setCurrentIndex(0);
    imageLabel->drawImage();
    this->resizePictureArea();
}

void PicDisplay::on_horizontalSliderSeamSize_sliderReleased()
{
    displaySeamCarvedImage();
}

void PicDisplay::on_checkSeamVisu_stateChanged(int arg1)
{
    imageLabel->setSeamLinesDisplayMode(arg1);
    displaySeamCarvedImage();
}

void PicDisplay::on_checkBoxSeamCompress_stateChanged(int arg1)
{
    displaySeamCarvedImage();
}

void PicDisplay::setSeamDisplay(int nbRoutes)
{
    ui->horizontalSliderSeamSize->setMaximum(nbRoutes);
    ui->checkBoxSeam->setChecked(true);
    ui->checkBoxSeam->setEnabled(true);

}

void PicDisplay::on_comboBoxSeamActions_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        imageLabel->setMouseListenerState(0);
        break;
    case 1:
        imageLabel->setMouseListenerState(31);
        break;
    case 2:
        imageLabel->setMouseListenerState(32);
        break;
    case 3:
        int maxNbLignes = imageLabel->getSeamCarver()->initStrengthRoutes(imageLabel->getImage1()->height()/8);
        setSeamDisplay(maxNbLignes);
        break;
    }
}

int PicDisplay::getFlouMode(){
    int ret = 1;
    QComboBox *q1=ui->comboBoxFlou1;
    if (!q1->currentText().isEmpty()){
        if(q1->currentText().compare("Moyenneur", Qt::CaseInsensitive) == 0){
            ret = 0;
        }
        else if(q1->currentText().compare("Gaussien", Qt::CaseInsensitive) == 0){
            ret = 1;
        }
    }
    return ret;
}

int PicDisplay::getFlouTaille(){
    int ret = 3;
    QLineEdit *q1=ui->lineEditFlou1;
    if (!q1->text().isEmpty())
        ret=q1->text().toInt();

    // EMPECHER LES TAILLES PAIR
    if(ret%2 == 0){
        ret+=1;
    }
    return ret;
}

double PicDisplay::getRehaussCoef(){
    double ret = 0.5;
    QLineEdit *q1=ui->lineEdit_Rehaus;
    if (!q1->text().isEmpty())
        ret=q1->text().toDouble();
    return ret;
}

double PicDisplay::getEtalAlpha(){
    double ret = 1.5;
    QLineEdit *q1=ui->lineEdit_Etal1;
    if (!q1->text().isEmpty())
        ret=q1->text().toDouble();
    return ret;
}

double PicDisplay::getEtalBeta(){
    double ret = 1.0;
    QLineEdit *q1=ui->lineEdit_Etal2;
    if (!q1->text().isEmpty())
        ret=q1->text().toDouble();
    return ret;
}

int PicDisplay::getFiltrePersoTaille(){
    int ret = 3;
    QRegExp re("\\d*");
    const QString w =  ui->lineEdit_Filtre->text();
    if (w.isEmpty())
        setErrorMsg("Taille de 3 chargée par défaut.");
    else
    {
        if (re.exactMatch(w))
        {
            ret = w.toInt();
            if(ret%2 == 0)
            {
                setErrorMsg("La taille du filtre doit être impaire.");
                ret += 1;
                ui->lineEdit_Filtre->setText(QString::number(ret));
            }
        } else
        {
            setErrorMsg("Taille demandée non numérique entier. Taille de 3 chargée par défaut.");
        }
    }
    return ret;
}

void PicDisplay::on_pushButtonFiltreEdition_clicked()
{
    int taille = getFiltrePersoTaille();
    tailleFiltre = taille;
    QDialog *filtre = new QDialog(this,0);
    filtre->setWindowTitle("Filtre perso");
    filtre->setFixedHeight(60*taille);
    filtre->setFixedWidth(50*taille);
    tab = new QTableWidget(taille, taille, filtre);
    tab->setFixedHeight(50*taille);
    tab->setFixedWidth(50*taille);
    for(int i=0;i<taille;i++){
        for(int j=0;j<taille;j++){
            tab->setItem(i, j, new QTableWidgetItem);
            tab->item(i,j)->setText("1");
            tab->setColumnWidth(j,40);
        }
    }

    QPushButton *valider = new QPushButton("Valider", filtre);
    valider->setGeometry((filtre->pos().x()+filtre->width()/2)-valider->width()/2,(filtre->pos().y()+filtre->height()-15)-valider->height()/2,valider->width(),valider->height());
    filtre->show();
    connect(valider,SIGNAL(clicked(bool)),this,SLOT(genererFiltre()));
    connect(valider, SIGNAL(clicked(bool)), filtre, SLOT(close()));
}

void PicDisplay::on_pushButton_FiltreLaunch_clicked()
{
    if(imageLabel->getSelectedImage()!= NULL){
        TransfoCouleur *tc = new TransfoCouleur;
        if(filtrePerso == NULL){
            filtrePerso = new KernelConvMoyenneur(tailleFiltre);
        }
        QImage *imageCible = tc->convPerso(filtrePerso, imageLabel->getSelectedImage());
        imageLabel->setPrincipal(imageCible);
    }
    //    const QImage imageConv = *imageLabel->getSelectedImage();
    //    imageLabel->setPixmap(QPixmap::fromImage(imageConv));
}

void PicDisplay::on_pushButtonResize_clicked()
{
    int ret_w,ret_h;
    QRegExp re("\\d*");
    const QString w =  ui->lineEdit_Width->text();
    if (w.isEmpty())
        ret_w = -1;
    else
    {
        if (re.exactMatch(w))
            ret_w = w.toInt();
        else
        {
            setErrorMsg("Largeur demandée non numérique entier.");
            return;
        }
    }
    const QString h =  ui->lineEdit_Height->text();
    if (h.isEmpty())
        ret_h = -1;
    else
    {
        if (re.exactMatch(h))
            ret_h = h.toInt();
        else
        {
            setErrorMsg("Hauteur demandée non numérique entier.");
            return;
        }
    }
    imageLabel->resizeSelectedImage(ret_w,ret_h);
    this->resizePictureArea();
    ui->lineEdit_Width->clear();
    ui->lineEdit_Height->setText("");
}

void PicDisplay::on_lineEdit_Width_textChanged(const QString &arg1)
{
    if ((arg1.size() > 0) || (ui->lineEdit_Height->text().size() >0))
        ui->pushButtonResize->setVisible(true);
    else
        ui->pushButtonResize->setVisible(false);
}

void PicDisplay::on_lineEdit_Height_textChanged(const QString &arg1)
{
    if ((arg1.size() > 0) || (ui->lineEdit_Width->text().size() >0))
        ui->pushButtonResize->setVisible(true);
    else
        ui->pushButtonResize->setVisible(false);
}

void PicDisplay::setErrorMsg(QString errorMsgVal)
{
    this->errorMsg=errorMsgVal;
    signalError();
}

QString PicDisplay::getErrorMsg()
{
    return this->errorMsg;
}

void PicDisplay::genererFiltre(){
    filtrePerso = new KernelConv(tailleFiltre);
    for(int i=0;i<tailleFiltre;i++){
        for(int j=0;j<tailleFiltre;j++){
            filtrePerso->setIndex(tab->item(i,j)->text().toInt(),i,j);
        }
    }
}
