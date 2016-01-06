#include "picdisplay.h"
#include "ui_picdisplay.h"

PicDisplay::PicDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicDisplay)
{
    ui->setupUi(this);
}

PicDisplay::~PicDisplay()
{
    delete ui;
}

void PicDisplay::on_radioButton_clicked()
{

}

void PicDisplay::on_pushButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        ui->label_3->setText("OO");
    } else
    {
        ui->label_3->setText("FF");
    }
}
