#ifndef SEAMCARVER_H
#define SEAMCARVER_H

#define NB_LIGNES_SEAM_CARVING 7
#include <QObject>
#include "imageanalyse.h"

class SeamCarver : public QObject
{
    Q_OBJECT
public:
    explicit SeamCarver(QObject *parent = 0);
    ~SeamCarver();
    void initImage(QImage *src);
    QPoint leastRouteNextPointAt(QPoint prec, int &strengthValue);
    void initStrengthRoutes(int nbLines);
    QList<QPolygon *> getListLignesMostSuitable();
    QImage * extendWidth(int w_extent,bool compression,bool afficheLignes);
    QPolygon *getPointAGarder();
    QPolygon *getPointASup();

signals:

public slots:

private:
    QImage *imgOrigine;
    double **dx_dy;
    QPolygon *pointAGarder;
    QPolygon *pointASup;
    bool ** b_Pos_interdit;
    QList<QPolygon *> listLignesMostSuitable;
    double getPointEnergy(int x, int y);
    void iteration();
};

#endif // SEAMCARVER_H
