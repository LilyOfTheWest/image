#include "seamcarver.h"
#include "imageresizer.h"

SeamCarver::SeamCarver(QImage *src, QObject *parent) : QObject(parent)
{
    imA = new ImageAnalyse(src);
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
    double dy_val = qAbs(imA->getDyIndex(y,x));
    double dy_val_cmp;
    if (y>0)
    {
        dy_val_cmp = qAbs(imA->getDyIndex(y-1,x));
        if (dy_val_cmp < dy_val)
        {
            y_most_suitable = y-1;
            dy_val = dy_val_cmp;
        }

    }
    if (y<(imgOrigine->height()-1))
    {
        dy_val_cmp = qAbs(imA->getDyIndex(y+1,x));
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
    QPolygon *polyg;
    for(int h=0;h<imgOrigine->height();h++){
        polyg = new QPolygon();
        item = QPoint(0,h);
        *polyg << item;
        strengthValue = imA->getDyIndex(h,0);
        for (int w=1; w<(imgOrigine->width()-1); w++) {
            item = leastRouteNextPointAt(item,strengthValue);
            *polyg << item;
        }
        *polyg << QPoint(imgOrigine->width()-1,item.y());
        listStrengthValue << strengthValue;
        listOrderedStrengthValue << strengthValue;
        listLignes <<polyg;
    }
    qSort(listOrderedStrengthValue);
    int strLeast;
    int index=1;
    int count=0;
    while((count <= NB_LIGNES_SEAM_CARVING)&&(index>0))
    {
        strLeast = listOrderedStrengthValue.takeFirst();
        index = listStrengthValue.indexOf(strLeast);
        listStrengthValue.takeAt(index);
        listLignesMostSuitable << listLignes.takeAt(index);
        count++;
    }

    qDeleteAll(listLignes);
    count=0;
}

QImage * SeamCarver::extendWidth(int w_extent){

    QPolygon *ligneBest;// = listLignesMostSuitable.first();
    QRgb color1,color2;
    QRgb ligneColor = qRgb(255,255,255);
    int y_ligneBest;
    QPoint pp;
    QImage *dataRet = new QImage(imgOrigine->width(),imgOrigine->height()+(w_extent+2)*listLignesMostSuitable.size(),imgOrigine->format());
    ImageResizer *resizer = new ImageResizer;
    int delta_y,tmp_lect;
    QList<int> list_y_val;
    QListIterator<QPolygon *> qit(listLignesMostSuitable);

    for (int x=0; x < imgOrigine->width() ; x++)
    {
        qit.toFront();
        list_y_val.clear();
        while (qit.hasNext())
        {
            ligneBest=qit.next();
            list_y_val << (ligneBest->takeFirst()).y();
        }
        qSort(list_y_val);
        list_y_val << imgOrigine->height() + 1000;
        y_ligneBest = list_y_val.takeFirst();

        //        pp=ligneBest->takeFirst();
        //y_ligneBest=pp.y();
        delta_y=0;
        for (int y=0; y < imgOrigine->height() ; y++) {
            color1=imgOrigine->pixel(x,y);
            if (y != y_ligneBest)
            {
                dataRet->setPixel(x,y+delta_y,color1);
            } else
            {
                do {
                    dataRet->setPixel(x,y_ligneBest+delta_y,ligneColor);
                    dataRet->setPixel(x,y_ligneBest+w_extent+2+delta_y,ligneColor);
                    color2=imgOrigine->pixel(x,y+1);
                    resizer->interpol(dataRet,x,y_ligneBest+1+delta_y,w_extent,color1,color2,false);
                    delta_y += w_extent+2;
                    tmp_lect = list_y_val.takeFirst();
                } while (tmp_lect == y_ligneBest);
                y_ligneBest = tmp_lect;
            }
        }
    }
    return dataRet;
}
