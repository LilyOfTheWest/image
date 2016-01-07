#ifndef PICTLABEL_H
#define PICTLABEL_H

#include <QWidget>
#include <QLabel>
#include <QRubberBand>
#include <QImage>
#include <QStack>

class PictLabel : public QLabel
{
    Q_OBJECT

public:
    void undoLast();
    void setPrincipal(QImage *principal);
    QImage *getPrincipal();

signals:

public slots:

protected:
    /*virtual void enterEvent ( QEvent * event ) Q_DECL_OVERRIDE;
    virtual void leaveEvent ( QEvent * event ) Q_DECL_OVERRIDE;*/
    virtual void mouseMoveEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    virtual void mousePressEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    void saveTemp();

    QRubberBand *rubberBand;
    QPoint origin_select;
    QPoint end_select;
    QStack<QImage> *undo;
    QImage *principal;
    QImage *second;
    QPoint origin_position_relative_second;
};

#endif // PICTLABEL_H
