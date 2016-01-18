#include "imageresizer.h"
#include "transfocouleur.h"

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
                ret->setPixel(i,src->width()-1-j,color);
            else
                ret->setPixel(src->height()-1-i,j,color);
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
    newWidth = 168;
    int width_multiple = newWidth / src->width();
    int width_added = newWidth % src->width();
    int width_step = src->width();
    if (width_added > 0)
        width_step = src->width() / width_added;
    int width_index = 0;
    int r,g,b;
    int width_added_tmp = width_step;
    QRgb color;
    TransfoCouleur *tc = new TransfoCouleur;
    QImage *ret = new QImage(newWidth,newHeight,src->format());
    for (int i=0; i<src->height()  ; i++) {
        width_index = 0;
        width_added_tmp = width_added;
        for (int j=0; j<src->width(); j++) {
            color = src->pixel(j,i);
            r=tc->get_RVal_Pixel_FromYuv(color);
            g=tc->get_GVal_Pixel_FromYuv(color);
            b=tc->get_BVal_Pixel_FromYuv(color);
            for (int k_mult=0; k_mult<width_multiple; k_mult++) {
                if (width_index < newWidth) {
                    ret->setPixel(width_index,i,color);
                    width_index++;
                } else
                    continue;
            }
            if (width_index >= newWidth) {
                continue;
            }
            if ((width_added_tmp > 0) && ((j % width_step) == 0))
            {
                ret->setPixel(width_index,i,color);
                width_index++;
                width_added_tmp--;
            }
        }
    }
    return ret;
}

