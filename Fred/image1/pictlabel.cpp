#include "pictlabel.h"
#include <QMouseEvent>
#include <QRubberBand>
#include <QPainter>
#include <QImage>

void PictLabel::setPrincipal(QImage *principal)
{
    principal = principal;
}

QImage *PictLabel::getPrincipal()
{
    return principal;
}

/*void PictLabel::enterEvent ( QEvent * event )
{
}

void PictLabel::leaveEvent ( QEvent * event )
{
}*/

void PictLabel::mouseMoveEvent ( QMouseEvent * event )
{
    rubberBand->setGeometry(QRect(origin_select, event->pos()).normalized());
}

void PictLabel::mousePressEvent ( QMouseEvent * event )
{
    origin_select = event->pos();
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    rubberBand->setGeometry(QRect(origin_select, QSize()));
    rubberBand->show();
}

void PictLabel::mouseReleaseEvent ( QMouseEvent * event )
{
    end_select = event->pos();
    rubberBand->hide();
    delete rubberBand;
    QPainter p;
    const QPixmap *dd = this->pixmap();
    QImage image2=dd->toImage();
    p.begin(&image2);
    p.setPen(QColor(Qt::color0));
    p.setBrush(Qt::NoBrush);
    p.drawRect(QRect(origin_select,end_select));
    p.end();
    const QImage image = image2;
    this->setPixmap(QPixmap::fromImage(image));
}

void PictLabel::saveTemp() {
    if (undo == NULL)
            undo = new QStack<QImage>();
    const QPixmap *dd = this->pixmap();
    QImage image2=dd->toImage();
    undo->push(image2);
}

void PictLabel::undoLast() {
    if (undo == NULL)
            return;
    if (undo->isEmpty())
            return;
    const QImage image = undo->pop();
    this->setPixmap(QPixmap::fromImage(image));
}


