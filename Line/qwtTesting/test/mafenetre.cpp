#include "mafenetre.h"
#include <qwt_plot.h>

MaFenetre::MaFenetre(int l, int h) : QWidget()
{
    setFixedSize(l,h);

//    m_lcd = new QLCDNumber(this);
//    m_lcd->setSegmentStyle(QLCDNumber::Flat);
//    m_lcd->move(50,20);

//    m_slider = new QSlider(Qt::Horizontal, this);
//    m_slider->setGeometry(10,60,150,20);
//    m_slider->setRange(200,600);

//    m_vertical = new QSlider(Qt::Vertical, this);
//    m_vertical->setGeometry(170,10,20,90);
//    m_vertical->setRange(100,600);

//    m_bar = new QProgressBar(this);
//    m_bar->setGeometry(10,90, 150,20);

//    m_bouton = new QPushButton("Reset", this);
//    m_bouton->move(70,130);

//    connect(m_slider, SIGNAL(valueChanged(int)), m_lcd, SLOT(display(int)));
//    connect(m_slider, SIGNAL(valueChanged(int)), m_bar, SLOT(setValue(int)));
//    connect(m_bouton, SIGNAL(clicked()), m_bar, SLOT(reset()));

//    connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changerLargeur(int)));
//    connect(m_vertical, SIGNAL(valueChanged(int)), this, SLOT(changerHauteur(int)));


    m_bouton = new QPushButton("Ouvrir", this);
    m_bouton->move(40,50);

    QObject::connect(m_bouton, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
}

void MaFenetre::ouvrirDialogue()
{
//    QMessageBox::information(this, "Info", "What's up biatch ?!");
//    QMessageBox::warning(this, "Attention", "<strong>Kess'ta !!!</strong>");
//    QMessageBox::critical(this,"OMG", "T'es un grand <strong> MALADE </strong");
//    int rep = QMessageBox::question(this, "Dis moi", "T'es un malade ou pas ?");
//    if(rep == QMessageBox::Yes)
//        QMessageBox::information(this, "Dis moi", "Donc t'es un grand malade !");
//    else if(rep == QMessageBox::No)
//        QMessageBox::information(this, "Dis moi", "Ah bon ça va alors !");
    bool ok = false;
//    QString pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo?", QLineEdit::Normal, QString(), &ok);
//    if(ok && !pseudo.isEmpty())
//    {
//        QMessageBox::information(this, "Pseudo", "Bonjou "+pseudo+", bien ou bien ?");
//        m_bouton->setText(pseudo);
//    }
//    else
//        QMessageBox::critical(this, "Pseudo", "Vous n'avez pas donné votre nom !!!");
//    QFont police = QFontDialog::getFont(&ok, m_bouton->font(), this, "Choisissez une police");

//    if(ok)
//        m_bouton->setFont(police);
//    QColor c = QColorDialog::getColor(Qt::white, this);

//    QPalette palette;

//    palette.setColor(QPalette::ButtonText, c);
//    m_bouton->setPalette(palette);
//    QString dossier = QFileDialog::getExistingDirectory(this);
//    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
//    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
}

//void MaFenetre::changerLargeur(int largeur)
//{
//    setFixedSize(largeur,this->height());

//    if(largeur == 600){
//        emit agrandissementMax();
//    }
//}

//void MaFenetre::changerHauteur(int hauteur)
//{
//    setFixedSize(this->width(), hauteur);

//    if(hauteur == 600){
//        emit agrandissementMax();
//    }
//}
