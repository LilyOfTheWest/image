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
    int getYUVMode();

    void updateDisplay();

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

private:
    Ui::PicDisplay *ui;
    PictLabel *imageLabel;
    void refreshPixelProperties();
    void displayImage2Selector(bool visible);
    void displayFlouProperties(bool visible);
    void displayRehausProperties(bool visible);
    void displayEtalProperties(bool visible);
    void displayFiltreProperties(bool visible);
    //void adjustScrollBar(QScrollBar *scrollBar, double factor);
};

#endif // PICDISPLAY_H
