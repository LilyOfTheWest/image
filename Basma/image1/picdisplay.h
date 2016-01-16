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

private slots:
    void on_refreshPixelProperties();
    void on_pushButton_clicked();
    void on_radioButtonRGB_clicked();

    void on_radioButton_YUV_clicked();

private:
    Ui::PicDisplay *ui;
    PictLabel *imageLabel;
    void refreshPixelProperties();
    //void adjustScrollBar(QScrollBar *scrollBar, double factor);
};

#endif // PICDISPLAY_H
