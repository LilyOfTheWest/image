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
    int x_max = qMax(origin_select->x(),end_select->x());
    int y_min = qMin(origin_select->y(),end_select->y());
    int y_max = qMax(origin_select->y(),end_select->y());
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

QImage *ImageResizer::displaceImage(QImage *principal, QImage *img1,QPoint pos_rel1,QImage *img2,QPoint pos_rel2)
{
    int x1_min = qMax(pos_rel1.x(),0);
    int x1_max = qMin(pos_rel1.x()+img1->width(),principal->width());
    int y1_min = qMax(pos_rel1.y(),0);
    int y1_max = qMin(pos_rel1.y()+img1->height(),principal->height());
    int x_min = x1_min;
    int x_max = x1_max;
    int y_min = y1_min;
    int y_max = y1_max;

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
                color = img1->pixel(x_in_img1,y_in_img1);
            if (img2 != NULL)
            {
                x_in_img2 = x_min+j-pos_rel2.x();
                y_in_img2 = y_min+i-pos_rel2.y();
                if ((x_in_img2 < img2->width()) && (x_in_img2 >=0) && (y_in_img2 < img2->height()) && (y_in_img2 >= 0))
                    color=img2->pixel(x_in_img2,y_in_img2);
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
    QImage *resized_w = resizeImage_w(src,newWidth,src->height());
    QImage *ret = resizeImage_h(resized_w,newWidth,newHeight);
    if (resized_w != NULL)
        delete resized_w;
    return ret;
}

QImage *ImageResizer::resizeImage_w(QImage *src,int newWidth, int height)
{
    int width_multiple = newWidth / src->width();
    int width_added = newWidth % src->width();
    int width_added_tmp = width_added;
    int w_impair_count=0;
    bool every_2=false;
    int mult_2 = 2;
    while ((width_added_tmp < (src->width()/mult_2)) && (mult_2 <= 32)) {
        mult_2 *= 2;
    }

    if (width_added_tmp >= (src->width()/mult_2))
    {
        every_2 = true;
        width_added_tmp -= src->width()/mult_2;
    }
    int width_step = src->width();
    if (width_added_tmp > 0)
        width_step = src->width() / width_added_tmp;
    int width_index = 0;
    //int width_nb
    int r,g,b;
    width_added_tmp = width_step;
    QRgb color1,color2;
    int nb_interpolation=0;
    QImage *ret = new QImage(newWidth,height,src->format());
    for (int h=0; h<src->height()  ; h++) {
        width_index = 0;
        w_impair_count = 0;
        width_added_tmp = width_added;

        for (int w=0; w<src->width(); w++) {
            nb_interpolation=width_multiple;
            color1 = src->pixel(w,h);
            if (w < (src->width()-1))
                color2 = src->pixel(w+1,h);
            else
                color2 = src->pixel(w,h);
            if (every_2)
            {
                if ((w % mult_2) == 0)
                {
                    if (width_added_tmp > 0)
                    {
                        nb_interpolation++;
                        width_added_tmp--;
                    }
                }
                else
                {
                    if ((w_impair_count % width_step) == 0)
                        if (width_added_tmp > 0)
                        {
                            nb_interpolation++;
                            width_added_tmp--;
                        }
                    w_impair_count++;
                }
            }
            else
            {
                if ((w % width_step) == 0)
                    if (width_added_tmp > 0)
                    {
                        nb_interpolation++;
                        width_added_tmp--;
                    }
            }
            interpol(ret,width_index,h,nb_interpolation,color1,color2,true);
            width_index += nb_interpolation;
        }
    }
    return ret;
}

QImage *ImageResizer::resizeImage_h(QImage *src,int width, int newHeight)
{
    int height_multiple = newHeight / src->height();
    int height_added = newHeight % src->height();
    int height_added_tmp = height_added;
    int h_impair_count=0;
    bool every_2=false;
    int mult_2 = 2;
    while ((height_added_tmp < (src->height()/mult_2)) && (mult_2 <= 32)) {
        mult_2 *= 2;
    }
    if (height_added_tmp >= (src->height()/mult_2))
    {
        every_2 = true;
        height_added_tmp -= src->height()/mult_2;
    }
    int height_step = src->height();
    if (height_added_tmp > 0)
        height_step = src->height() / height_added_tmp;
    int height_index = 0;
    //int width_nb
    int r,g,b;
    height_added_tmp = height_step;
    QRgb color1,color2;
    int nb_interpolation=0;
    QImage *ret = new QImage(width,newHeight,src->format());
    for (int w=0; w<src->width(); w++) {
        height_index = 0;
        h_impair_count = 0;
        height_added_tmp = height_added;
        for (int h=0; h<src->height()  ; h++) {
            nb_interpolation=height_multiple;
            color1 = src->pixel(w,h);
            if (h < (src->height()-1))
                color2 = src->pixel(w,h+1);
            else
                color2 = src->pixel(w,h);
            if (every_2)
            {
                if ((h % mult_2) == 0)
                {
                    if (height_added_tmp > 0)
                    {
                        nb_interpolation++;
                        height_added_tmp--;
                    }
                }
                else
                {
                    if ((h_impair_count % height_step) == 0)
                        if (height_added_tmp > 0)
                        {
                            nb_interpolation++;
                            height_added_tmp--;
                        }
                    h_impair_count++;
                }
            }
            else
            {
                if ((h % height_step) == 0)
                    if (height_added_tmp > 0)
                    {
                        nb_interpolation++;
                        height_added_tmp--;
                    }
            }
            interpol(ret,w,height_index,nb_interpolation,color1,color2,false);
            height_index += nb_interpolation;
        }
    }
    return ret;
}

void ImageResizer::interpol(QImage *dest, int wDest,int hDest,int nb_interpo_w,QRgb color1,
                            QRgb  color2,bool width_sens)
{
    int denomin;
    if (nb_interpo_w <= 0)
        return;
    dest->setPixel(wDest,hDest,color1);
    if (nb_interpo_w >=1)
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
