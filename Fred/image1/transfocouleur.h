#ifndef TRANSFOCOULEUR_H
#define TRANSFOCOULEUR_H

#include <QObject>
#include <QImage>

class TransfoCouleur : public QObject
{
    Q_OBJECT
public:
    explicit TransfoCouleur(QObject *parent = 0);
    QImage *inverseColor(QImage *src);

signals:

public slots:
};

#endif // TRANSFOCOULEUR_H
