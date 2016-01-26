#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>

class MaFenetre : public QWidget
{
    Q_OBJECT

    public:
    MaFenetre(int l, int h);

    public slots:
    void ouvrirDialogue();

signals:
    void agrandissementMax();

    private:
    QPushButton *m_bouton;

};

#endif // MAFENETRE_H
