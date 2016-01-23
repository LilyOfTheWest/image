#ifndef SEAMCARVER_H
#define SEAMCARVER_H

#define NB_LIGNES_SEAM_CARVING 7
#include <QObject>
#include "imageanalyse.h"

class SeamCarver : public QObject
{
    Q_OBJECT
public:
    explicit SeamCarver(QImage *src, QObject *parent = 0);
    ~SeamCarver();
    QPoint leastRouteNextPointAt(QPoint prec, int &strengthValue);
    void init(int w_extent);
    QList<QPolygon *> listLignesMostSuitable;
    QImage * extendWidth(int w_extent,bool compression);

signals:

public slots:

private:
    QImage *imgOrigine;
    ImageAnalyse *imA;
    bool ** b_Pos_interdit;
    double getPointEnergy(int x, int y);
    void iteration();
};

#endif // SEAMCARVER_H
