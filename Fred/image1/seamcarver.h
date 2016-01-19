#ifndef SEAMCARVER_H
#define SEAMCARVER_H

#define NB_LIGNES_SEAM_CARVING = 7
#include <QObject>
#include "imageanalyse.h"

class SeamCarver : public QObject
{
    Q_OBJECT
public:
    explicit SeamCarver(QImage *src, QObject *parent = 0);
    ~SeamCarver();
    QPoint leastRouteNextPointAt(QPoint prec, int &strengthValue);
    void init();
    QList<QPolygon *> listLignesMostSuitable;
    QImage * extendWidth(int w_extent);

signals:

public slots:

private:
    QImage *imgOrigine;
    ImageAnalyse *imA;
};

#endif // SEAMCARVER_H
