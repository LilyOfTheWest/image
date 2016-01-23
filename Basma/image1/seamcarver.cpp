#include "seamcarver.h"
#include "imageresizer.h"

SeamCarver::SeamCarver(QImage *src, QObject *parent) : QObject(parent)
{
    imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    imA->calculgradient(1);
    imgOrigine = imA->getDataRGB();
    //listLignesMostSuitable;
    b_Pos_interdit = new bool*[imgOrigine->height()];
    for(int y = 0 ; y < imgOrigine->height() ; y++){
        b_Pos_interdit[y] = new bool[imgOrigine->width()];
    }
    for(int x = 0; x < imgOrigine->width() ; x++){
        b_Pos_interdit[0][x]=true;
        b_Pos_interdit[imgOrigine->height()-1][x]=true;

    }
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

double SeamCarver::getPointEnergy(int y, int x)
{
    return qAbs(imA->getDyIndex(y,x)) + qAbs(imA->getDxIndex(y,x));
}

QPoint SeamCarver::leastRouteNextPointAt(QPoint prec, int &strengthValue) {
    int x=prec.x()+1;
    int y=prec.y();
    int y_most_suitable=-1;
    double dy_val = 20000;
    double dy_val_cmp;
    if (b_Pos_interdit[y-1][x] == false)
    {
        dy_val_cmp = this->getPointEnergy(y-1,x);
        if (dy_val_cmp < dy_val)
        {
            y_most_suitable = y-1;
            dy_val = dy_val_cmp;
        }

    }
    if (b_Pos_interdit[y][x] == false)
    {
        dy_val_cmp = this->getPointEnergy(y,x);
        if (dy_val_cmp < dy_val)
        {
            y_most_suitable = y;
            dy_val = dy_val_cmp;
        }

    }
    if (!b_Pos_interdit[y+1][x])
    {
        dy_val_cmp = this->getPointEnergy(y+1,x);
        if (dy_val_cmp < dy_val)
        {
            y_most_suitable = y+1;
            dy_val = dy_val_cmp;
        }

    }
    strengthValue += dy_val;
    return QPoint(x,y_most_suitable);
}

void SeamCarver::init(int w_extent){

    for (int iter=0 ; iter<w_extent ; iter++)
    {
        iteration();

    }
    int y=0;
}

void SeamCarver::iteration()
{
    QList<QPolygon *> listLignes;
    QPoint item;
    int strengthValue;
    QList<int> listStrengthValue;
    QList<int> listOrderedStrengthValue;
    QPolygon *polyg;
    bool route_bloquee;

    for(int h=0;h<imgOrigine->height();h++){
        route_bloquee=false;
        if (b_Pos_interdit[h][0] == false)
        {
            polyg = new QPolygon();
            item = QPoint(0,h);
            *polyg << item;
            strengthValue = getPointEnergy(h,0);
            for (int w=1; w<(imgOrigine->width()-1); w++) {
                item = leastRouteNextPointAt(item,strengthValue);
                if (item.y() < 0) //Cas 3 routes bloquées
                {
                    w=imgOrigine->width();
                    route_bloquee=true;

                } else
                    *polyg << item;
            }
            if (route_bloquee==false)
            {
                *polyg << QPoint(imgOrigine->width()-1,item.y());
                listStrengthValue << strengthValue;
                listOrderedStrengthValue << strengthValue;
                listLignes <<polyg;
            } else
                delete polyg;
        }
    }
    qSort(listOrderedStrengthValue);
    int strLeast;
    int index=1;
    int count=0;
    strLeast = listOrderedStrengthValue.takeFirst();
    index = listStrengthValue.indexOf(strLeast);
    listStrengthValue.takeAt(index);
    polyg = listLignes.takeAt(index);
    listLignesMostSuitable << polyg;

    QVectorIterator<QPoint> qit(*polyg);
    while (qit.hasNext())
    {
        item=qit.next();
        b_Pos_interdit[item.y()][item.x()]= true;
    }
    qDeleteAll(listLignes);
    count=0;
}

QImage * SeamCarver::extendWidth(int w_extent,bool compression){

    QPolygon *ligneBest;// = listLignesMostSuitable.first();
    QRgb color1,color2;
    QRgb ligneColor = qRgb(255,255,255);
    int y_ligneBest;
    QPoint pp;
    QImage *dataRet = new QImage(imgOrigine->width(),imgOrigine->height()+3*w_extent,imgOrigine->format());
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
                dataRet->setPixel(x,y_ligneBest+delta_y,ligneColor);
                dataRet->setPixel(x,y_ligneBest+delta_y+2,ligneColor);
                color2=imgOrigine->pixel(x,y+1);
                resizer->interpol(dataRet,x,y_ligneBest+1+delta_y,1,color1,color2,false);
                delta_y += 3;
                y_ligneBest = list_y_val.takeFirst();
            }
        }
    }
    return dataRet;
}
