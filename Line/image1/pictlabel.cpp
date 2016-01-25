#include "pictlabel.h"
#include <QMouseEvent>
#include <QRubberBand>
#include <QPainter>
#include <QImage>
#include <QRgb>

PictLabel::PictLabel(QWidget *parent) :
    QLabel(parent),colorPicked(qRgb(0,0,0))
{
    principal = NULL;
    firstImg = NULL;
    secondImg = NULL;
    selectedImg = NULL;
    scaleFactor = 1;
    setInitialContext();
    sc = new SeamCarver(this);
    resizer = new ImageResizer(this);
    setSeamLinesDisplayMode(false);
}

PictLabel::~PictLabel()
{
    delete principal;
    qDeleteAll(undo);
    delete sc;
    delete resizer;
}

void PictLabel::setInitialContext()
{
    origin_select.setX(0);
    origin_select.setY(0);
    mouseListenerState=0;
    alphaImg1=100;
    alphaImg2=100;
    if (secondImg != NULL)
    {
        delete secondImg;
        secondImg = NULL;
    }
    setSecondImgAsSelect(false);
    setCouperMode(false);
    if (end_select != NULL)
    {
        delete end_select;
        end_select = NULL;
    }
    position_firstImg.setX(0);
    position_firstImg.setY(0);
    position_secondImg.setX(0);
    position_secondImg.setY(0);
}

void PictLabel::addImageToMerge(QImage *src)
{
    firstImgSelected=false;
    position_firstImg.setX(0);
    position_firstImg.setY(0);
    end_select = NULL;

    // Install background ; principal devient firstImg
    int totalWidth = firstImg->width() + src->width();
    int totalHeight = firstImg->height() + src->height();
    QRgb backgroundColor = qRgb(255,255,255);
    if (principal != NULL)
        delete principal;
    principal = new QImage(totalWidth,totalHeight,principal->format());
    for (int i=0; i< principal->height() ; i++) {
        for (int j=0; j<principal->width() ; j++) {
            principal->setPixel(j,i,backgroundColor);
        }
    }

    secondImg = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            secondImg->setPixel(j,i,src->pixel(j,i));
        }
    }
    position_secondImg.setX(0);
    position_secondImg.setY(0);
    mouse_origin.setX(0);
    mouse_origin.setY(0);
    setMouseListenerState(12);
    drawImage();
}


void PictLabel::setPrincipal(QImage *src)
{
    saveTemp(firstImg);
    setPrincipalWithoutPrevSaved(src);
}

void PictLabel::setPrincipalWithoutPrevSaved(QImage *src)
{
    // Install background ; principal devient firstImg
    QRgb backgroundColor = qRgb(255,255,255);
    if (principal != NULL)
        delete principal;
    principal = new QImage(src->width(),src->height(),src->format());
    firstImg = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            firstImg->setPixel(j,i,src->pixel(j,i));
            principal->setPixel(j,i,backgroundColor);
        }
    }
    setInitialContext();
    drawImage();
    signalResizingRequired();
    signalRedisplayRequired();
}

QImage *PictLabel::getPrincipal()
{
    return principal;
}

QImage *PictLabel::getSelectedImage()
{
    return selectedImg;
}

QImage *PictLabel::getImage1()
{
    return firstImg;
}

QImage *PictLabel::getImage2()
{
    return secondImg;
}

void PictLabel::setSelectedImage(QImage *selectImgPar)
{
    if (selectedImg == secondImg)
    {
        secondImg = new QImage(selectImgPar->width(),selectImgPar->height(),selectImgPar->format());
        selectedImg = secondImg;

    } else {
        firstImg = new QImage(selectImgPar->width(),selectImgPar->height(),selectImgPar->format());
        selectedImg = firstImg;
    }
    for (int i=0; i< selectedImg->height() ; i++) {
        for (int j=0; j<selectedImg->width() ; j++) {
            firstImg->setPixel(j,i,selectImgPar->pixel(j,i));
        }
    }
    drawImage();
    signalRedisplayRequired();
}

int PictLabel::getAlphaImg1()
{
    return alphaImg1;
}

void PictLabel::setAlphaImg1(int value)
{
    alphaImg1=value;
    if (firstImg != NULL)
    {
        QRgb color;
        TransfoCouleur *tc = new TransfoCouleur;
        for (int i=0; i< firstImg->height() ; i++) {
            for (int j=0; j<firstImg->width() ; j++) {
                color=firstImg->pixel(j,i);
                firstImg->setPixel(j,i,tc->changeAlphaColor(color,value));
            }
        }
    }
}

int PictLabel::getAlphaImg2()
{
    return alphaImg1;
}

void PictLabel::setAlphaImg2(int value)
{
    alphaImg2=value;
    QRgb color;
    TransfoCouleur *tc = new TransfoCouleur;
    if (secondImg != NULL)
    {
        for (int i=0; i< secondImg->height() ; i++) {
            for (int j=0; j<secondImg->width() ; j++) {
                color=secondImg->pixel(j,i);
                secondImg->setPixel(j,i,tc->changeAlphaColor(color,value));
            }
        }
    }
}

SeamCarver *PictLabel::getSeamCarver()
{
    return sc;
}

void PictLabel::mouseMoveEvent ( QMouseEvent * event )
{
    QPoint mouse_position;
    switch(mouseListenerState){
    case 10: // Pipette

        break;
    case 11: // Select
        //rubberBand->setGeometry(QRect(resizeWithScaling(origin_select), event->pos()).normalized());
        rubberBand->setGeometry(QRect(rubberBand->geometry().topLeft(), event->pos()).normalized());
        break;
    case 12: // Deplace première image
        break;
    case 31: // Sélection des zones à garder seam carver.
        mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg);
        if (mouse_position.x() != -1) {
            *sc->getPointAGarder() << mouse_position;
        }
        break;
    case 32: // Sélection des zones à supprimer seam carver.
        mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg);
        if (mouse_position.x() != -1) {
            *sc->getPointASup() << mouse_position;
        }
        break;
    case 110: // Crop select
        //rubberBand->setGeometry(QRect(resizeWithScaling(origin_select), event->pos()).normalized());
        rubberBand->setGeometry(QRect(rubberBand->geometry().topLeft(), event->pos()).normalized());
        break;
    }


}

void PictLabel::mousePressEvent ( QMouseEvent * event )
{
    QPoint mouse_position = resizeWithScaling(event->pos());
    QPoint rep;
    switch(mouseListenerState){
    case 10: // Pipette
        mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg);
        if (mouse_position.x() != -1) {
            mouse_origin = mouse_position;
            colorPicked = firstImg->pixel(mouse_position);
            signalNewPixelPicked();
        }
        break;
    case 11: // Select
        origin_select = mouse_position;
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(event->pos(), QSize()));
        rubberBand->show();
        break;
    case 12: // Deplace selected image
        mouse_origin = resizeWithScaling(event->pos());
        if (getSecondImgAsSelect())
        {
            mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),secondImg,&position_secondImg);
            if (mouse_position.x() == -1)
            {
                mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg);
                if (mouse_position.x() != -1) {
                    setSecondImgAsSelect(false);
                } else
                {
                    mouse_origin = mouse_position;
                }
            }
        } else {
            mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg);
            if (mouse_position.x() == -1)
            {
                mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),secondImg,&position_secondImg);
                if (mouse_position.x() != -1) {
                    setSecondImgAsSelect(true);
                } else
                {
                    mouse_origin = mouse_position;
                }
            }
        }

        break;
    case 31: // Sélection garde seam carver.
        mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg);
        if (mouse_position.x() != -1) {
            *sc->getPointAGarder() << mouse_position;
        }
        break;
    case 32: // Sélection garde seam carver.
        mouse_position = resizer->isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg);
        if (mouse_position.x() != -1) {
            *sc->getPointASup() << mouse_position;
        }
        break;
    case 110: // Crop select
        origin_select = mouse_position;
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(event->pos(), QSize()));
        rubberBand->show();
        break;
    }
}

void PictLabel::mouseReleaseEvent ( QMouseEvent * event )
{
    QPoint *mouse_end = new QPoint(resizeWithScaling(event->pos()));
    switch(mouseListenerState){
    case 10:

        break;
    case 11: // Select
        setSelection(event);
        break;
    case 12: // Deplace première image
        if (mouse_origin.x() != -1)
            if (getSecondImgAsSelect())
            {
                moveSelection(mouse_end,selectedImg,position_secondImg);
            } else
            {
                moveSelection(mouse_end,selectedImg,position_firstImg);
            }
        break;
    case 31: // Sélection garde seam carver.
        drawImage();
        break;
    case 32: // Sélection garde seam carver.
        drawImage();
        break;
    case 110: // Crop select
        setSelection(event);
        break;
    }
}

void PictLabel::setSelection(QMouseEvent * event)
{
    end_select = new QPoint(resizeWithScaling(event->pos()));
    rubberBand->hide();
    secondImg=NULL;
    delete rubberBand;
    drawImage();
}

void PictLabel::pasteSelection()
{
    if (end_select != NULL) {
        ImageResizer *resizer = new ImageResizer;
        secondImg =resizer->extractSubImage(firstImg,&origin_select,end_select);
        position_secondImg.setX(0);
        position_secondImg.setY(0);
        drawImage();
        mouseListenerState=18;
    }
    signalRedisplayRequired();
}

void PictLabel::moveSelection(QPoint *mouse_end,QImage *imgToMove,QPoint &positionRelative)
{
    int x_pos = positionRelative.x() + mouse_end->x() - mouse_origin.x();
    int y_pos = positionRelative.y() + mouse_end->y() - mouse_origin.y();
    if (x_pos < -imgToMove->width())
        x_pos = 3-imgToMove->width();
    if (y_pos < -imgToMove->height())
        y_pos = 3-imgToMove->height();
    int xMax = principal->width()-3;
    int yMax = principal->height()-3;
    if (x_pos > xMax)
        x_pos = xMax;
    if (y_pos > yMax)
        y_pos = yMax;
    if (mouse_origin.x() == -1)
        return;
    positionRelative.setX(x_pos);
    positionRelative.setY(y_pos);
    drawImage();
}

void PictLabel::saveTemp(QImage *svgFirstImg) {
    if (svgFirstImg == NULL)
        return;
    //const QPixmap *dd = this->pixmap();
    //QImage image2=dd->toImage();
    undo.append(svgFirstImg);//image2);
}

void PictLabel::undoLast() {
    if (undo.count()>0)
    {
        setPrincipalWithoutPrevSaved(undo.last());
        undo.removeLast();
    }
}

void PictLabel::setMouseListenerState(int mouseListenerStateVal)
{
    mouseListenerState=mouseListenerStateVal;
}

int PictLabel::getMouseListenerState()
{
    return mouseListenerState;
}


QRgb PictLabel::getColorPicked()
{
    return colorPicked;
}

QPoint PictLabel::getPixelPicked()
{
    return mouse_origin;
}

void PictLabel::setScaleFactor(double scaleFactor)
{
    this->scaleFactor = scaleFactor;
}

QPoint PictLabel::resizeWithScaling(QPoint mousePointed)
{
    QPoint ret;
    int scaled = mousePointed.x()/scaleFactor;
    ret.setX(scaled);
    scaled = mousePointed.y()/scaleFactor;
    ret.setY(scaled);
    return ret;
}

void PictLabel::setCouperMode(bool couperMode)
{
    this->couperMode=couperMode;
}

void PictLabel::setSecondImgAsSelect(bool secondImgAsSelect)
{
    selectedImg=(secondImgAsSelect)?secondImg:firstImg;
    this->firstImgSelected=!secondImgAsSelect;
}

bool PictLabel::getSecondImgAsSelect()
{
    return !this->firstImgSelected;
}


void PictLabel::drawImage()
{
    QPainter p;
    //const QPixmap *dd = this->pixmap();
    QImage image2=*principal;//dd->toImage();
    p.begin(&image2);
    p.setPen(QColor(Qt::color0));
    p.setBrush(Qt::NoBrush);
    if (firstImg != NULL)
    {
        const QImage imageFirstFirstImg = *firstImg;
        p.drawPixmap(position_firstImg.x(),
                     position_firstImg.y(),
                     firstImg->width(),
                     firstImg->height(),
                     QPixmap::fromImage(imageFirstFirstImg));
    }

    if (end_select != NULL)
        p.drawRect(QRect(origin_select,*end_select));
    if (secondImg != NULL)
    {
        const QImage imageSecondImge = *secondImg;
        p.drawPixmap(position_secondImg.x(),
                     position_secondImg.y(),
                     secondImg->width(),
                     secondImg->height(),
                     QPixmap::fromImage(imageSecondImge));
    }
    if (visuSeamLines)
    {
        QList<QPolygon *> listStrengthLines = this->sc->getListLignesMostSuitable();
        if (!listStrengthLines.isEmpty())
        {
            int colorLines=255;
            QListIterator<QPolygon *> qit(listStrengthLines);
            int counterExtractLignes = nbSeamLinesToDisplay;
            while ((qit.hasNext()) && (counterExtractLignes >0))
            {
                QRgb ligneColor = qRgb(colorLines,colorLines,colorLines);
                p.setPen(ligneColor);
                //colorLines--;
                p.drawPoints(*qit.next());
                counterExtractLignes--;
            }
        }
        QPolygon *lignesAGarder = sc->getPointAGarder();
        if ((lignesAGarder != NULL) && (!lignesAGarder->isEmpty()))
        {
            p.setPen(QColor(Qt::yellow));
            p.drawPoints(*lignesAGarder);
        }
        QPolygon *lignesASup = sc->getPointASup();
        if ((lignesASup != NULL) && (!lignesASup->isEmpty()))
        {
            p.setPen(QColor(Qt::red));
            p.drawPoints(*lignesASup);
        }
    }
    p.end();
    const QImage image = image2;
    //    this->setPixmap(QPixmap::fromImage(image));
    this->setPixmap(QPixmap::fromImage(image));
    signalRedisplayRequired();
}

void PictLabel::validateTransfo()
{
    ImageResizer *resizer = new ImageResizer;
    QImage *newImage;
    switch(mouseListenerState){
    case 12: // Deplace première image
        newImage =resizer->displaceImage(principal,firstImg,position_firstImg,secondImg,position_secondImg);
        setPrincipal(newImage);
        break;
    case 110: // Crop select
        newImage =resizer->extractSubImage(firstImg,&origin_select,end_select);
        setPrincipal(newImage);
        break;
    }
}

QString PictLabel::getNomImg(){
    return nomImg;
}

void PictLabel::setNomImg(QString nom){
    nomImg = nom;
}

void PictLabel::setNbSeamLinesToDisplay(int value)
{
    nbSeamLinesToDisplay = value;
}

void PictLabel::setSeamLinesDisplayMode(bool value)
{
    visuSeamLines = value;
}

