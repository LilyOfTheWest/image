#include "imageresizer.h"

ImageResizer::ImageResizer(QObject *parent) : QObject(parent)
{
    /*
     * QVector<QImage> jj;
    QVectorIterator<QImage> hh(jj);
    while (hh.hasNext())
        delete hh.next;
        */

}

QImage *ImageResizer::extractSubImage(QImage *src,QPoint *origin_select,QPoint *end_select)
{
    int x_min = qMin(origin_select->x(),end_select->x());
    x_min = qMax(x_min,0);
    int x_max = qMax(origin_select->x(),end_select->x());
    x_max = qMin(x_max,src->width());
    int y_min = qMin(origin_select->y(),end_select->y());
    y_min = qMax(y_min,0);
    int y_max = qMax(origin_select->y(),end_select->y());
    y_max = qMin(y_max,src->height());
    QRgb color;
    int width = x_max-x_min;
    int height = y_max-y_min;
    QImage *ret = new QImage(width,height,src->format());
    for (int i=0; i<ret->height()  ; i++) {
        for (int j=0; j<ret->width(); j++) {
            color=src->pixel(j+x_min,i+y_min);
            ret->setPixel(j,i,color);
        }
    }
    return ret;
}


QPoint ImageResizer::isPicked(QPoint mousePosition,QImage *imgPicked,QPoint *positionRel)
{
    QPoint ret = QPoint(-1,-1);
    if (imgPicked != NULL)
    {
        int x_in_imgPicked = mousePosition.x()-positionRel->x();
        int y_in_imgPicked = mousePosition.y()-positionRel->y();
        if ((x_in_imgPicked < imgPicked->width()) && (x_in_imgPicked>0) &&
                (y_in_imgPicked < imgPicked->height()) && (y_in_imgPicked>0))
            ret = QPoint(x_in_imgPicked,y_in_imgPicked);
    }
    return ret;
}

QImage *ImageResizer::displaceImage(QImage *principal, QImage *img1,QPoint pos_rel1,
                                    QImage *img2,QPoint pos_rel2,bool couperMode,QPoint origin_select,QPoint *end_select)
{
    int x1_min = qMax(pos_rel1.x(),0);
    int x1_max = qMin(pos_rel1.x()+img1->width(),principal->width());
    int y1_min = qMax(pos_rel1.y(),0);
    int y1_max = qMin(pos_rel1.y()+img1->height(),principal->height());
    int x_min = x1_min;
    int x_max = x1_max;
    int y_min = y1_min;
    int y_max = y1_max;

    int x_couper_min,x_couper_max,y_couper_min,y_couper_max;
    if ((couperMode)&&(end_select != NULL))
    {
        x_couper_min=qMin(origin_select.x(),end_select->x());
        x_couper_max=qMax(origin_select.x(),end_select->x());
        y_couper_min=qMin(origin_select.y(),end_select->y());
        y_couper_max=qMax(origin_select.y(),end_select->y());
    }

    if (img2 != NULL)
    {
        int x2_min = qMax(pos_rel2.x(),0);
        int x2_max = qMin(pos_rel2.x()+img2->width(),principal->width());
        int y2_min = qMax(pos_rel2.y(),0);
        int y2_max = qMin(pos_rel2.y()+img2->height(),principal->height());
        x_min = qMin(x1_min,x2_min);
        x_max = qMax(x1_max,x2_max);
        y_min = qMin(y1_min,y2_min);;
        y_max = qMax(y1_max,y2_max);
    }

    int ret_width = x_max - x_min;
    int ret_height = y_max - y_min;
    int x_in_img1, y_in_img1, x_in_img2, y_in_img2;
    QImage *ret = new QImage(ret_width,ret_height,principal->format());
    QRgb color;

    for (int i=0 ; i<ret_height; i++) {
        for (int j=0 ; j<ret_width ; j++)
        {
            color = qRgba(255,255,255,255);
            x_in_img1 = x_min+j-pos_rel1.x();
            y_in_img1 = y_min+i-pos_rel1.y();
            if ((x_in_img1 < img1->width()) && (x_in_img1  >= 0) && (y_in_img1 < img1->height()) && (y_in_img1  >= 0))
            {
                if ((couperMode)&&(end_select != NULL))
                {
                    if (!((x_in_img1>=x_couper_min)&&
                          (x_in_img1<=x_couper_max)&&
                          (y_in_img1>=y_couper_min)&&
                          (y_in_img1<=y_couper_max)))
                    {
                        color = img1->pixel(x_in_img1,y_in_img1); // BUG TRANSPARENCE ICI
                    }
                }
                else
                {
                    color = img1->pixel(x_in_img1,y_in_img1); // BUG TRANSPARENCE ICI
                }
            }
            if (img2 != NULL)
            {
                x_in_img2 = x_min+j-pos_rel2.x();
                y_in_img2 = y_min+i-pos_rel2.y();
                if ((x_in_img2 < img2->width()) && (x_in_img2 >=0) && (y_in_img2 < img2->height()) && (y_in_img2 >= 0))
                    color=img2->pixel(x_in_img2,y_in_img2); // BUG TRANSPARENCE ICI
            }
            ret->setPixel(j,i,color);
        }
    }
    return ret;
}


QImage *ImageResizer::rotateImage90(QImage *src,bool horaire)
{
    QRgb color;
    QImage *ret = new QImage(src->height(),src->width(),src->format());
    for (int i=0; i<src->height()  ; i++) {
        for (int j=0; j<src->width(); j++) {
            color = src->pixel(j,i);
            if (horaire == true)
                ret->setPixel(src->height()-1-i,j,color);
            else
                ret->setPixel(i,src->width()-1-j,color);
        }
    }
    return ret;
}

QImage *ImageResizer::rotateImage180(QImage *src)
{
    QRgb color;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i<src->height()  ; i++) {
        for (int j=0; j<src->width(); j++) {
            color = src->pixel(j,i);
            ret->setPixel(src->width()-1-j,src->height()-1-i,color);
        }
    }
    return ret;
}

QImage *ImageResizer::resizeImage(QImage *src,int newWidth, int newHeight)
{
    QImage *resized_w = resizeImageSingleDim(src,newWidth,src->height(),true);
    QImage *ret = resizeImageSingleDim(resized_w,newHeight,newWidth,false);
    if (resized_w != NULL)
        delete resized_w;
    return ret;
}

void ImageResizer::interpol(QImage *dest, int wDest,int hDest,int nb_interpo_w,QRgb color1,
                            QRgb  color2,bool width_sens)
{
    int denomin;
    if (nb_interpo_w <= 0)
        return;
    dest->setPixel(wDest,hDest,color1);
    if (nb_interpo_w > 1)
    {
        int r1=qRed(color1);
        int g1=qGreen(color1);
        int b1=qBlue(color1);
        int alpha1=qAlpha(color1);
        int r2=qRed(color2);
        int g2=qGreen(color2);
        int b2=qBlue(color2);
        int alpha2=qAlpha(color2);
        QRgb color_tmp;
        for (int k_mult=1; k_mult<=nb_interpo_w; k_mult++) {
            denomin=nb_interpo_w+1;
            color_tmp = qRgba(r1+(r2-r1)*k_mult/denomin,
                              g1+(g2-g1)*k_mult/denomin,
                              b1+(b2-b1)*k_mult/denomin,
                              alpha1+(alpha2-alpha1)*k_mult/denomin);
            if (width_sens)
                dest->setPixel(wDest+k_mult-1,hDest,color_tmp);
            else
                dest->setPixel(wDest,hDest+k_mult-1,color_tmp);
        }
    }
}

QImage *ImageResizer::resizeImageSingleDim(QImage *src,int renewedDimVal,int otherDimVal,bool widthChanged)
{
    int previousDimValue = (widthChanged) ? src->width() : src->height();
    int wsel_dim_multiple = renewedDimVal / previousDimValue;
    int wsel_dim_added = renewedDimVal % previousDimValue;
    int wsel_dim_added_tmp = wsel_dim_added;
    int wsel_dim_added_mult2 = 0;
    int wsel_dim_added_Non_mult2 = wsel_dim_added;
    int wsel_dim_added_tmp_Non_mult2 = 0;
    int w_Non_mult2_count=0;
    bool every_2=false;
    int mult_2 = 2;
    bool b_Add=true;
    int tmp_add,tmp_nb_points_del,tmp_del=0;
    int wsel_dim_step_Non_mult2 = previousDimValue+8; // cas où les positions mult2 couvrent le besoin
    while ((wsel_dim_added_tmp < (previousDimValue/mult_2)) && (mult_2 <= 32)) {
        mult_2 *= 2;
    }
    if (wsel_dim_added_tmp >= (previousDimValue/mult_2))
    {
        every_2 = true;
        wsel_dim_added_mult2 = previousDimValue/mult_2;
        wsel_dim_added_Non_mult2 -= wsel_dim_added_mult2;
    }
    if (wsel_dim_added_Non_mult2 > 0)
    {
        tmp_add = (previousDimValue-wsel_dim_added_mult2) / wsel_dim_added_Non_mult2;
        tmp_nb_points_del = previousDimValue-wsel_dim_added_mult2-wsel_dim_added_Non_mult2;
        if (tmp_nb_points_del > 0)
            tmp_del = (previousDimValue-wsel_dim_added_mult2) / tmp_nb_points_del;
        if (tmp_del > tmp_add)
        {
            b_Add=false;
            wsel_dim_step_Non_mult2 = tmp_del;
        } else
        {
            b_Add=true;
            wsel_dim_step_Non_mult2 = tmp_add;
        }
    }
    int wsel_dim_index = 0;
    QRgb color1,color2;
    int nb_interpolation=0;
    QImage *ret = (widthChanged) ? new QImage(renewedDimVal,otherDimVal,src->format()) :
                                   new QImage(otherDimVal,renewedDimVal,src->format());
    int otherDimLimit = (widthChanged) ? src->height() : src->width();
    int thisDimLimit = (widthChanged) ? src->width() : src->height();
    for (int otherDimParam=0; otherDimParam < otherDimLimit  ; otherDimParam++) {
        wsel_dim_index = 0;
        w_Non_mult2_count = 0;
        wsel_dim_added_tmp = wsel_dim_added;
        wsel_dim_added_tmp_Non_mult2 = wsel_dim_added - wsel_dim_added_mult2;
        if (!b_Add)
            wsel_dim_added_tmp_Non_mult2 = tmp_nb_points_del;
        for (int thisDimParam = 0; thisDimParam < thisDimLimit; thisDimParam++) {
            nb_interpolation=wsel_dim_multiple;
            if (widthChanged)
            {
                color1 = src->pixel(thisDimParam,otherDimParam);
                if (thisDimParam < (thisDimLimit-1))
                    color2 = src->pixel(thisDimParam+1,otherDimParam);
                else
                    color2 = src->pixel(thisDimParam,otherDimParam);
            } else
            {
                color1 = src->pixel(otherDimParam,thisDimParam);
                if (thisDimParam < (thisDimLimit-1))
                    color2 = src->pixel(otherDimParam,thisDimParam+1);
                else
                    color2 = src->pixel(otherDimParam,thisDimParam);
            }
            if (every_2)
            {
                if ((thisDimParam % mult_2) == 0)
                {
                    if (wsel_dim_added_tmp > 0)
                    {
                        nb_interpolation++;
                        wsel_dim_added_tmp--;
                    }
                }
                else
                {
                    if (((b_Add)&&((w_Non_mult2_count % wsel_dim_step_Non_mult2) == 0)&&(wsel_dim_added_tmp_Non_mult2 > 0))
                            ||((!b_Add)&&(((w_Non_mult2_count % wsel_dim_step_Non_mult2) != 0)||(wsel_dim_added_tmp_Non_mult2<=0))))
                        if (wsel_dim_added_tmp > 0)
                        {
                            nb_interpolation++;
                            wsel_dim_added_tmp_Non_mult2--;
                            wsel_dim_added_tmp--;
                        }
                    w_Non_mult2_count++;
                }
            }
            else
            {
                if ((thisDimParam % wsel_dim_step_Non_mult2) == 0)
                    if (wsel_dim_added_tmp > 0)
                    {
                        nb_interpolation++;
                        wsel_dim_added_tmp--;
                    }
            }
            if (widthChanged)
                interpol(ret,wsel_dim_index,otherDimParam,nb_interpolation,color1,color2,widthChanged);
            else
                interpol(ret,otherDimParam,wsel_dim_index,nb_interpolation,color1,color2,widthChanged);
            wsel_dim_index += nb_interpolation;
        }
    }
    return ret;
}
