#include "seamcarver.h"

SeamCarver::SeamCarver(QImage *src, QObject *parent) : QObject(parent)
{
    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    imA->calculgradient();
    imgOrigine = imA->getDataRGB();
    //listLignesMostSuitable;
}

SeamCarver::~SeamCarver()
{
    if (imA != NULL)
        delete imA;
    if (!listLignesMostSuitable.isEmpty())
    {
        qDeleteAll(listLignesMostSuitable);
    }

}

QPoint SeamCarver::leastRouteNextPointAt(QPoint prec, int &strengthValue) {
    int x=prec.x()+1;
    int y=prec.y();
    int y_most_suitable=y;
    double dy_val = qAbs(imA->getDyIndex(x,y));
    double dy_val_cmp;
    if (y>0)
    {
        dy_val_cmp = qAbs(imA->getDyIndex(x,y-1));
        if (dy_val_cmp < dy_val)
        {
            y_most_suitable = y-1;
            dy_val = dy_val_cmp;
        }

    }
    if (y<(imgOrigine->height()-1))
    {
        dy_val_cmp = qAbs(imA->getDyIndex(x,y+1));
        if (dy_val_cmp < dy_val)
        {
            y_most_suitable = y+1;
            dy_val = dy_val_cmp;
        }

    }
    strengthValue += dy_val;
    return QPoint(x,y_most_suitable);
}

void SeamCarver::init(){
    QList<QPolygon *> listLignes;
    QPoint item;
    int strengthValue;
    QList<int> listStrengthValue;
    QList<int> listOrderedStrengthValue;
    for(int h=0;h<imgOrigine->height();h++){
        listLignes[h] = new QPolygon(imgOrigine->width());
        item = QPoint(0,h);
        *listLignes[h] << item;
       strengthValue=imA->getDyIndex(0,h);
        for (int w=1; w<(imgOrigine->width()-1); w++) {
            item = leastRouteNextPointAt(item,strengthValue);
            *listLignes[h] << item;
        }
        listStrengthValue << strengthValue;
        listOrderedStrengthValue << strengthValue;
    }






}

QImage * SeamCarver::extendWidth(int w_extent){
    return imA->getDataRGB();

}
