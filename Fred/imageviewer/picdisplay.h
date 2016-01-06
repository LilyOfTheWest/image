#ifndef PICDISPLAY_H
#define PICDISPLAY_H

#include <QWidget>

namespace Ui {
class PicDisplay;
}

class PicDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PicDisplay(QWidget *parent = 0);
    ~PicDisplay();

private slots:
    void on_radioButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::PicDisplay *ui;
};

#endif // PICDISPLAY_H
