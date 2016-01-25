#ifndef PICDISPLAY_H
#define PICDISPLAY_H

#include <QWidget>

namespace Ui {
class PicDisplay;
class PictLabel;
class QScrollBar;
}

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QScrollBar;
class QScrollArea;
class PictLabel;
class QLabel;
class QKernelConv;
class KernelDialog;
class PicDisplay;
class QWidget;
QT_END_NAMESPACE


class PicDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PicDisplay(PictLabel *imageLabel, QWidget *parent = 0);
    ~PicDisplay();
    void resizePictureArea();
    void scaleImage(double factor);
    int getResizedWidthRequired();
    int getResizedHeightRequired();
    int getFlouMode();
    int getFlouTaille();
    double getRehaussCoef();
    double getEtalAlpha();
    double getEtalBeta();
    int getFiltrePersoTaille();
    int getYUVMode();
    void updateDisplay();
    void setSeamDisplay(int nbRoutes);

private slots:
    void on_refreshPixelProperties();
    void on_resizingRequired();
    void on_displayRedefined();
    void on_radioButtonRGB_clicked();
    void on_radioButton_YUV_clicked();

    void on_checkBoxFlou_stateChanged(int arg1);

    void on_checkBox_Rehaus_stateChanged(int arg1);

    void on_checkBox_Etal_stateChanged(int arg1);

    void on_radioButtonImg1_clicked();

    void on_radioButtonImg2_clicked();

    void on_horizontalSlider_img1_valueChanged(int value);

    void on_horizontalSlider_img2_valueChanged(int value);

    void on_pushButton_FiltreLaunch_clicked();

    void on_pushButtonFiltreEdition_clicked();

    void on_checkBox_Filtre_stateChanged(int arg1);

    void on_checkBoxSeam_stateChanged(int arg1);

    void on_horizontalSliderSeamSize_valueChanged(int value);

    void on_horizontalSliderSeamSize_sliderReleased();

    void on_checkSeamVisu_stateChanged(int arg1);

    void on_checkBoxSeamCompress_stateChanged(int arg1);

    void on_comboBoxSeamActions_currentIndexChanged(int index);

private:
    Ui::PicDisplay *ui;
    PictLabel *imageLabel;
    void refreshPixelProperties();
    void displayImage2Selector(bool visible);
    void displayFlouProperties(bool visible);
    void displayRehausProperties(bool visible);
    void displayEtalProperties(bool visible);
    void displayFiltreProperties(bool visible);
    void displaySeamProperties(bool visible);
    void displaySeamCarvedImage();
    //void adjustScrollBar(QScrollBar *scrollBar, double factor);
};

#endif // PICDISPLAY_H
