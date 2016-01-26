#include "seamcarver.h"
#include "imageresizer.h"

SeamCarver::SeamCarver(QObject *parent) : QObject(parent)
{
    imgOrigine = NULL;
    pointAGarder = new QPolygon;
    pointASup = new QPolygon;
    b_Pos_interdit = NULL;
}

SeamCarver::~SeamCarver()
{
    if (!listLignesMostSuitable.isEmpty())
    {
        qDeleteAll(listLignesMostSuitable);
    }
    delete pointAGarder;
    delete pointASup;
}

double SeamCarver::getPointEnergy(int y, int x)
{
    return dx_dy [y][x];
}

void SeamCarver::initImage(QImage *src)
{
    QPoint item;
    if (imgOrigine != NULL)
    {
        delete imgOrigine;
    }
    if (src == NULL)
        return;

    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    imA->calculgradient(1);
    imgOrigine = imA->getDataRGB();
    dx_dy = new double *[src->height()];
    for(int y=0;y<src->height();y++){
        dx_dy[y] = new double[src->width()];
        for (int x=0; x<src->width() ; x++) {
            dx_dy[y][x]=qAbs(imA->getDyIndex(y,x)) + qAbs(imA->getDxIndex(y,x));
        }
    }
    delete imA;
    pointAGarder->clear();
    pointASup->clear();

    /*imgOrigine = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            color=src->pixel(j,i);
            imgOrigine->setPixel(j,i,color);
        }
    }*/

    //listLignesMostSuitable;

}

QPolygon *SeamCarver::getPointAGarder()
{
    return pointAGarder;
}

QPolygon *SeamCarver::getPointASup()
{
    return pointASup;
}

QList<QPolygon *> SeamCarver::getListLignesMostSuitable()
{
    return listLignesMostSuitable;
}

QPoint SeamCarver::leastRouteNextPointAt(QPoint prec, int &strengthValue) {
    int x=prec.x()+1;
    int y=prec.y();
    int y_most_suitable=-1;
    double dy_val = 20000;
    double dy_val_cmp;
    double dy_val_prio=30000;
    if (b_Pos_interdit[y][x] == false)
    {
        dy_val_cmp = this->getPointEnergy(y,x);
        if (dy_val_cmp < dy_val)
        {
            y_most_suitable = y;
            dy_val = dy_val_cmp;
            dy_val_prio = dy_val_cmp / 1.5;
        }

    }
    if (b_Pos_interdit[y-1][x] == false)
    {
        dy_val_cmp = this->getPointEnergy(y-1,x);
        if ((dy_val_cmp < dy_val) && (dy_val_cmp < dy_val_prio))
        {
            y_most_suitable = y-1;
            dy_val = dy_val_cmp;
        }

    }
    if (!b_Pos_interdit[y+1][x])
    {
        dy_val_cmp = this->getPointEnergy(y+1,x);
        if ((dy_val_cmp < dy_val) && (dy_val_cmp < dy_val_prio))
        {
            y_most_suitable = y+1;
            dy_val = dy_val_cmp;
        }

    }
    strengthValue += dy_val;
    return QPoint(x,y_most_suitable);
}

int SeamCarver::initStrengthRoutes(int nbLines)
{
    QPoint item;
    if (b_Pos_interdit != NULL)
        delete b_Pos_interdit;
    b_Pos_interdit = new bool*[imgOrigine->height()];
    for(int y = 0 ; y < imgOrigine->height() ; y++){
        b_Pos_interdit[y] = new bool[imgOrigine->width()];
    }
    for(int x = 0; x < imgOrigine->width() ; x++){
        b_Pos_interdit[0][x]=true;
        b_Pos_interdit[imgOrigine->height()-1][x]=true;

    }
    QVectorIterator<QPoint> qit_sup(*this->getPointASup());
    //QList<int> listStrengthValueASup;
    //QPolygon *getPointASupReordered = new QPolygon;
    while (qit_sup.hasNext())
    {
        item=qit_sup.next();
        //listStrengthValueASup << item.y();

        dx_dy[item.y()][item.x()]= -20000;
    }
    /*qSort(listStrengthValueASup);
    int strLeast;
    int index=1;
    if (!listOrderedStrengthValue.isEmpty())
    {
        strLeast = listOrderedStrengthValue.takeFirst();
        index = listStrengthValue.indexOf(strLeast);
        listStrengthValue.takeAt(index);
        item = *this->getPointASup().takeAt(index);
        listLignesMostSuitable << polyg;
    }*/


    QVectorIterator<QPoint> qit_garde(*this->getPointAGarder());
    while (qit_garde.hasNext())
    {
        item=qit_garde.next();
        b_Pos_interdit[item.y()][item.x()]= true;
    }
    qDeleteAll(listLignesMostSuitable);
    listLignesMostSuitable.clear();
    for (int iter=0 ; iter<nbLines ; iter++)
    {
        iteration();
        if (iter == 77)
            int u = 7;
    }
    int y=0;
    return listLignesMostSuitable.size();
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
    if (!listOrderedStrengthValue.isEmpty())
    {
        strLeast = listOrderedStrengthValue.takeFirst();
        index = listStrengthValue.indexOf(strLeast);
        listStrengthValue.takeAt(index);
        polyg = listLignes.takeAt(index);
        listLignesMostSuitable << polyg;
    }
    if (polyg != NULL)
    {
        QVectorIterator<QPoint> qit(*polyg);
        while (qit.hasNext())
        {
            item=qit.next();
            b_Pos_interdit[item.y()][item.x()]= true;
        }
    }
    qDeleteAll(listLignes);
    count=0;
}

QImage * SeamCarver::extendWidth(int w_extent,bool compression,bool afficheLignes)
{
    QPolygon *ligneBest;// = listLignesMostSuitable.first();
    QRgb color1,color2;
    int y_ligneBest;
    QPoint pp;
    int extendedSize = 0;//2*w_extent;
    if (!afficheLignes)
        extendedSize = (compression) ? -w_extent : w_extent;
    QImage *dataRet = new QImage(imgOrigine->width(),imgOrigine->height()+extendedSize,imgOrigine->format());
    ImageResizer *resizer = new ImageResizer;
    int delta_y,tmp_lect;
    QList<int> list_y_val;
    int counterExtractLignes = w_extent;
    QListIterator<QPolygon *> qit(listLignesMostSuitable);

    for (int x=0; x < imgOrigine->width() ; x++)
    {
        qit.toFront();
        list_y_val.clear();
        counterExtractLignes = w_extent;
        while ((qit.hasNext()) && (counterExtractLignes >0))
        {
            ligneBest=qit.next();
            list_y_val << (ligneBest->point(x)).y();
            counterExtractLignes--;
        }
        qSort(list_y_val);
        list_y_val << imgOrigine->height() + 1000;
        y_ligneBest = list_y_val.takeFirst();

        //        pp=ligneBest->takeFirst();
        //y_ligneBest=pp.y();
        delta_y=0;
        for (int y=0; y < imgOrigine->height() ; y++) {
            color1=imgOrigine->pixel(x,y);
            if ((afficheLignes) || (y != y_ligneBest))
            {
                int w_newPosition = y+delta_y;
                if (w_newPosition < dataRet->height())
                    dataRet->setPixel(x,w_newPosition,color1);
            } else
            {
                if (compression)
                {
                    delta_y -= 1;
                } else
                {
                    dataRet->setPixel(x,y_ligneBest+delta_y,color1);
                    color2=imgOrigine->pixel(x,y+1);
                    resizer->interpol(dataRet,x,y_ligneBest+delta_y+1,1,color1,color2,false);
                    delta_y += 1;
                }
                y_ligneBest = list_y_val.takeFirst();
            }
        }
    }
    return dataRet;
}
