/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Nouveau;
    QAction *action_Ouvrir;
    QAction *action_Fermer;
    QAction *action_Enregistrer;
    QAction *action_Enregistrer_sous;
    QAction *action_Imprimer;
    QAction *actionExit;
    QAction *action_Annuler;
    QAction *action_Couper;
    QAction *action_Copier;
    QAction *action_Coller;
    QAction *actionZoom_avant;
    QAction *action_Zoom_arriere;
    QAction *actionRotation_90_Horaire;
    QAction *action_Rotation_90_antihoraire;
    QAction *actionRotation_180;
    QAction *action_Flou_gaussien;
    QAction *action_Flou_moyenneur;
    QAction *action_Personnalis_flou;
    QAction *action_Filtre_Prewitt;
    QAction *action_Personnalis_Detec;
    QAction *actionFusion;
    QAction *actionBarre_d_outil;
    QAction *actionBarre_de_menu;
    QAction *actionCouleurs;
    QAction *actionHistogramme;
    QAction *action_Taille_filtre;
    QAction *action_Selection;
    QAction *actionDeplacement;
    QAction *actionCrop;
    QAction *actionFlou;
    QAction *actionSeamCarving;
    QAction *actionPipette;
    QAction *actionInverseCoul;
    QAction *actionImageGris;
    QAction *actionFusion_2;
    QAction *actionRecadrer;
    QAction *actionValider;
    QAction *actionHistogramme_2;
    QAction *actionSupprimer;
    QAction *actionContour;
    QAction *actionRehaussement;
    QAction *actionEtalement;
    QAction *actionEgalisation;
    QAction *actionFiltre_Scharr;
    QAction *actionFiltre_Sobel;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuTest;
    QMenu *menu_Edition;
    QMenu *menu_Affichage;
    QMenu *menu_Image;
    QMenu *menu_Effet;
    QMenu *menu_Flou;
    QMenu *menu_Datetction_de_contours;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        action_Nouveau = new QAction(MainWindow);
        action_Nouveau->setObjectName(QStringLiteral("action_Nouveau"));
        action_Nouveau->setEnabled(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Edition/Menu Edition/new file.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Nouveau->setIcon(icon);
        action_Ouvrir = new QAction(MainWindow);
        action_Ouvrir->setObjectName(QStringLiteral("action_Ouvrir"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Edition/Menu Edition/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Ouvrir->setIcon(icon1);
        action_Fermer = new QAction(MainWindow);
        action_Fermer->setObjectName(QStringLiteral("action_Fermer"));
        action_Fermer->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Edition/Menu Edition/Close file.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Fermer->setIcon(icon2);
        action_Enregistrer = new QAction(MainWindow);
        action_Enregistrer->setObjectName(QStringLiteral("action_Enregistrer"));
        action_Enregistrer->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Edition/Menu Edition/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Enregistrer->setIcon(icon3);
        action_Enregistrer_sous = new QAction(MainWindow);
        action_Enregistrer_sous->setObjectName(QStringLiteral("action_Enregistrer_sous"));
        action_Enregistrer_sous->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Edition/Menu Edition/Save as.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Enregistrer_sous->setIcon(icon4);
        action_Imprimer = new QAction(MainWindow);
        action_Imprimer->setObjectName(QStringLiteral("action_Imprimer"));
        action_Imprimer->setEnabled(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Edition/Menu Edition/Print.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Imprimer->setIcon(icon5);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        action_Annuler = new QAction(MainWindow);
        action_Annuler->setObjectName(QStringLiteral("action_Annuler"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/File/Menu File/Undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Annuler->setIcon(icon6);
        action_Couper = new QAction(MainWindow);
        action_Couper->setObjectName(QStringLiteral("action_Couper"));
        action_Couper->setEnabled(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/File/Menu File/couper.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Couper->setIcon(icon7);
        action_Copier = new QAction(MainWindow);
        action_Copier->setObjectName(QStringLiteral("action_Copier"));
        action_Copier->setEnabled(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/File/Menu File/copier.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Copier->setIcon(icon8);
        action_Coller = new QAction(MainWindow);
        action_Coller->setObjectName(QStringLiteral("action_Coller"));
        action_Coller->setEnabled(true);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/File/Menu File/Paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Coller->setIcon(icon9);
        actionZoom_avant = new QAction(MainWindow);
        actionZoom_avant->setObjectName(QStringLiteral("actionZoom_avant"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Affichage/Menu Afichage/Zoom avant.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_avant->setIcon(icon10);
        action_Zoom_arriere = new QAction(MainWindow);
        action_Zoom_arriere->setObjectName(QStringLiteral("action_Zoom_arriere"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Affichage/Menu Afichage/Zoom arriere.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Zoom_arriere->setIcon(icon11);
        actionRotation_90_Horaire = new QAction(MainWindow);
        actionRotation_90_Horaire->setObjectName(QStringLiteral("actionRotation_90_Horaire"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/Image/Menu Image/Rotation clock.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotation_90_Horaire->setIcon(icon12);
        action_Rotation_90_antihoraire = new QAction(MainWindow);
        action_Rotation_90_antihoraire->setObjectName(QStringLiteral("action_Rotation_90_antihoraire"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Image/Menu Image/Rotation otherclock.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Rotation_90_antihoraire->setIcon(icon13);
        actionRotation_180 = new QAction(MainWindow);
        actionRotation_180->setObjectName(QStringLiteral("actionRotation_180"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/Image/Menu Image/Rotation 180.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotation_180->setIcon(icon14);
        action_Flou_gaussien = new QAction(MainWindow);
        action_Flou_gaussien->setObjectName(QStringLiteral("action_Flou_gaussien"));
        action_Flou_moyenneur = new QAction(MainWindow);
        action_Flou_moyenneur->setObjectName(QStringLiteral("action_Flou_moyenneur"));
        action_Personnalis_flou = new QAction(MainWindow);
        action_Personnalis_flou->setObjectName(QStringLiteral("action_Personnalis_flou"));
        action_Filtre_Prewitt = new QAction(MainWindow);
        action_Filtre_Prewitt->setObjectName(QStringLiteral("action_Filtre_Prewitt"));
        action_Personnalis_Detec = new QAction(MainWindow);
        action_Personnalis_Detec->setObjectName(QStringLiteral("action_Personnalis_Detec"));
        actionFusion = new QAction(MainWindow);
        actionFusion->setObjectName(QStringLiteral("actionFusion"));
        actionFusion->setCheckable(true);
        actionFusion->setChecked(true);
        actionBarre_d_outil = new QAction(MainWindow);
        actionBarre_d_outil->setObjectName(QStringLiteral("actionBarre_d_outil"));
        actionBarre_d_outil->setCheckable(true);
        actionBarre_de_menu = new QAction(MainWindow);
        actionBarre_de_menu->setObjectName(QStringLiteral("actionBarre_de_menu"));
        actionBarre_de_menu->setCheckable(true);
        actionCouleurs = new QAction(MainWindow);
        actionCouleurs->setObjectName(QStringLiteral("actionCouleurs"));
        actionCouleurs->setCheckable(true);
        actionHistogramme = new QAction(MainWindow);
        actionHistogramme->setObjectName(QStringLiteral("actionHistogramme"));
        actionHistogramme->setCheckable(true);
        action_Taille_filtre = new QAction(MainWindow);
        action_Taille_filtre->setObjectName(QStringLiteral("action_Taille_filtre"));
        action_Selection = new QAction(MainWindow);
        action_Selection->setObjectName(QStringLiteral("action_Selection"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/Barre outil/Tool bar/Selection.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Selection->setIcon(icon15);
        actionDeplacement = new QAction(MainWindow);
        actionDeplacement->setObjectName(QStringLiteral("actionDeplacement"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/Barre outil/Tool bar/Deplacement.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeplacement->setIcon(icon16);
        actionCrop = new QAction(MainWindow);
        actionCrop->setObjectName(QStringLiteral("actionCrop"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/Barre outil/Tool bar/Crop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCrop->setIcon(icon17);
        actionFlou = new QAction(MainWindow);
        actionFlou->setObjectName(QStringLiteral("actionFlou"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/Barre outil/Tool bar/Flou.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFlou->setIcon(icon18);
        actionSeamCarving = new QAction(MainWindow);
        actionSeamCarving->setObjectName(QStringLiteral("actionSeamCarving"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/Barre outil/Tool bar/Seamcarving.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSeamCarving->setIcon(icon19);
        actionPipette = new QAction(MainWindow);
        actionPipette->setObjectName(QStringLiteral("actionPipette"));
        actionPipette->setEnabled(true);
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/group1/pipette-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPipette->setIcon(icon20);
        actionInverseCoul = new QAction(MainWindow);
        actionInverseCoul->setObjectName(QStringLiteral("actionInverseCoul"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/Barre outil/Tool bar/negatif.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInverseCoul->setIcon(icon21);
        actionImageGris = new QAction(MainWindow);
        actionImageGris->setObjectName(QStringLiteral("actionImageGris"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/Barre outil/Tool bar/imagegris.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImageGris->setIcon(icon22);
        actionFusion_2 = new QAction(MainWindow);
        actionFusion_2->setObjectName(QStringLiteral("actionFusion_2"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/Barre outil/Tool bar/Fusion.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFusion_2->setIcon(icon23);
        actionRecadrer = new QAction(MainWindow);
        actionRecadrer->setObjectName(QStringLiteral("actionRecadrer"));
        actionValider = new QAction(MainWindow);
        actionValider->setObjectName(QStringLiteral("actionValider"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/Barre outil/Tool bar/valider.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionValider->setIcon(icon24);
        actionHistogramme_2 = new QAction(MainWindow);
        actionHistogramme_2->setObjectName(QStringLiteral("actionHistogramme_2"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/Barre outil/Tool bar/Histogramme.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHistogramme_2->setIcon(icon25);
        actionSupprimer = new QAction(MainWindow);
        actionSupprimer->setObjectName(QStringLiteral("actionSupprimer"));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/Barre outil/Tool bar/Supprimer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSupprimer->setIcon(icon26);
        actionContour = new QAction(MainWindow);
        actionContour->setObjectName(QStringLiteral("actionContour"));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/Barre outil/Tool bar/Contour.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionContour->setIcon(icon27);
        actionRehaussement = new QAction(MainWindow);
        actionRehaussement->setObjectName(QStringLiteral("actionRehaussement"));
        actionEtalement = new QAction(MainWindow);
        actionEtalement->setObjectName(QStringLiteral("actionEtalement"));
        actionEgalisation = new QAction(MainWindow);
        actionEgalisation->setObjectName(QStringLiteral("actionEgalisation"));
        actionFiltre_Scharr = new QAction(MainWindow);
        actionFiltre_Scharr->setObjectName(QStringLiteral("actionFiltre_Scharr"));
        actionFiltre_Sobel = new QAction(MainWindow);
        actionFiltre_Sobel->setObjectName(QStringLiteral("actionFiltre_Sobel"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuTest = new QMenu(menubar);
        menuTest->setObjectName(QStringLiteral("menuTest"));
        menu_Edition = new QMenu(menubar);
        menu_Edition->setObjectName(QStringLiteral("menu_Edition"));
        menu_Affichage = new QMenu(menubar);
        menu_Affichage->setObjectName(QStringLiteral("menu_Affichage"));
        menu_Image = new QMenu(menubar);
        menu_Image->setObjectName(QStringLiteral("menu_Image"));
        menu_Effet = new QMenu(menubar);
        menu_Effet->setObjectName(QStringLiteral("menu_Effet"));
        menu_Flou = new QMenu(menu_Effet);
        menu_Flou->setObjectName(QStringLiteral("menu_Flou"));
        menu_Datetction_de_contours = new QMenu(menu_Effet);
        menu_Datetction_de_contours->setObjectName(QStringLiteral("menu_Datetction_de_contours"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar_2);

        menubar->addAction(menuTest->menuAction());
        menubar->addAction(menu_Edition->menuAction());
        menubar->addAction(menu_Affichage->menuAction());
        menubar->addAction(menu_Image->menuAction());
        menubar->addAction(menu_Effet->menuAction());
        menuTest->addAction(action_Nouveau);
        menuTest->addAction(action_Ouvrir);
        menuTest->addAction(action_Fermer);
        menuTest->addSeparator();
        menuTest->addAction(action_Enregistrer);
        menuTest->addAction(action_Enregistrer_sous);
        menuTest->addSeparator();
        menuTest->addAction(action_Imprimer);
        menuTest->addSeparator();
        menuTest->addAction(actionExit);
        menu_Edition->addAction(action_Annuler);
        menu_Edition->addSeparator();
        menu_Edition->addAction(action_Couper);
        menu_Edition->addAction(action_Copier);
        menu_Edition->addAction(action_Coller);
        menu_Edition->addSeparator();
        menu_Affichage->addAction(actionZoom_avant);
        menu_Affichage->addAction(action_Zoom_arriere);
        menu_Image->addAction(actionRecadrer);
        menu_Image->addSeparator();
        menu_Image->addAction(actionRotation_180);
        menu_Image->addAction(actionRotation_90_Horaire);
        menu_Image->addAction(action_Rotation_90_antihoraire);
        menu_Effet->addAction(menu_Flou->menuAction());
        menu_Effet->addAction(menu_Datetction_de_contours->menuAction());
        menu_Effet->addAction(actionEtalement);
        menu_Effet->addAction(actionEgalisation);
        menu_Effet->addAction(actionRehaussement);
        menu_Flou->addAction(action_Flou_gaussien);
        menu_Flou->addAction(action_Flou_moyenneur);
        menu_Flou->addSeparator();
        menu_Datetction_de_contours->addAction(action_Filtre_Prewitt);
        menu_Datetction_de_contours->addAction(actionFiltre_Sobel);
        menu_Datetction_de_contours->addAction(actionFiltre_Scharr);
        menu_Datetction_de_contours->addSeparator();
        toolBar->addAction(action_Nouveau);
        toolBar->addAction(action_Ouvrir);
        toolBar->addAction(action_Enregistrer);
        toolBar->addSeparator();
        toolBar->addAction(action_Imprimer);
        toolBar->addSeparator();
        toolBar->addAction(action_Couper);
        toolBar->addAction(action_Copier);
        toolBar->addAction(action_Coller);
        toolBar->addAction(action_Annuler);
        toolBar->addAction(actionValider);
        toolBar->addAction(actionSupprimer);
        toolBar_2->addAction(action_Selection);
        toolBar_2->addAction(actionDeplacement);
        toolBar_2->addAction(actionPipette);
        toolBar_2->addAction(actionCrop);
        toolBar_2->addAction(actionFlou);
        toolBar_2->addAction(actionSeamCarving);
        toolBar_2->addAction(actionInverseCoul);
        toolBar_2->addAction(actionImageGris);
        toolBar_2->addAction(actionFusion_2);
        toolBar_2->addAction(actionHistogramme_2);
        toolBar_2->addAction(actionContour);
        toolBar_2->addAction(actionZoom_avant);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Nouveau->setText(QApplication::translate("MainWindow", "&Nouveau", 0));
        action_Nouveau->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        action_Ouvrir->setText(QApplication::translate("MainWindow", "&Ouvrir", 0));
        action_Ouvrir->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        action_Fermer->setText(QApplication::translate("MainWindow", "&Fermer", 0));
        action_Fermer->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0));
        action_Enregistrer->setText(QApplication::translate("MainWindow", "&Enregistrer", 0));
        action_Enregistrer->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        action_Enregistrer_sous->setText(QApplication::translate("MainWindow", "&Enregistrer sous", 0));
        action_Enregistrer_sous->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0));
        action_Imprimer->setText(QApplication::translate("MainWindow", "&Imprimer", 0));
        action_Imprimer->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Quitter", 0));
        action_Annuler->setText(QApplication::translate("MainWindow", "&Annuler", 0));
        action_Annuler->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        action_Couper->setText(QApplication::translate("MainWindow", "&Couper", 0));
        action_Couper->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0));
        action_Copier->setText(QApplication::translate("MainWindow", "&Copier", 0));
        action_Copier->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        action_Coller->setText(QApplication::translate("MainWindow", "&Coller", 0));
        action_Coller->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0));
        actionZoom_avant->setText(QApplication::translate("MainWindow", "Zoom avant", 0));
        actionZoom_avant->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0));
        action_Zoom_arriere->setText(QApplication::translate("MainWindow", "&Zoom arri\303\250re", 0));
        action_Zoom_arriere->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0));
        actionRotation_90_Horaire->setText(QApplication::translate("MainWindow", "Rotation 90\302\260 Horaire", 0));
        action_Rotation_90_antihoraire->setText(QApplication::translate("MainWindow", "&Rotation 90\302\260 antihoraire", 0));
        actionRotation_180->setText(QApplication::translate("MainWindow", "Rotation 180\302\260", 0));
        action_Flou_gaussien->setText(QApplication::translate("MainWindow", "&Flou gaussien ", 0));
        action_Flou_moyenneur->setText(QApplication::translate("MainWindow", "&Flou moyenneur", 0));
        action_Personnalis_flou->setText(QApplication::translate("MainWindow", "&Personnalis\303\251...", 0));
        action_Filtre_Prewitt->setText(QApplication::translate("MainWindow", "&Filtre Prewitt", 0));
        action_Personnalis_Detec->setText(QApplication::translate("MainWindow", "&Personnalis\303\251...", 0));
        actionFusion->setText(QApplication::translate("MainWindow", "Fusion", 0));
        actionBarre_d_outil->setText(QApplication::translate("MainWindow", "Barre d'outil", 0));
        actionBarre_de_menu->setText(QApplication::translate("MainWindow", "Barre de menu", 0));
        actionCouleurs->setText(QApplication::translate("MainWindow", "Couleurs", 0));
        actionHistogramme->setText(QApplication::translate("MainWindow", "Histogramme", 0));
        action_Taille_filtre->setText(QApplication::translate("MainWindow", "&Taille filtre", 0));
        action_Selection->setText(QApplication::translate("MainWindow", "&Selection", 0));
        actionDeplacement->setText(QApplication::translate("MainWindow", "Deplacement", 0));
        actionCrop->setText(QApplication::translate("MainWindow", "Crop", 0));
        actionFlou->setText(QApplication::translate("MainWindow", "Flou", 0));
        actionSeamCarving->setText(QApplication::translate("MainWindow", "SeamCarving", 0));
        actionPipette->setText(QApplication::translate("MainWindow", "Pipette", 0));
        actionInverseCoul->setText(QApplication::translate("MainWindow", "InverseCoul", 0));
        actionImageGris->setText(QApplication::translate("MainWindow", "ImageGris", 0));
        actionFusion_2->setText(QApplication::translate("MainWindow", "Fusion", 0));
        actionRecadrer->setText(QApplication::translate("MainWindow", "Recadrer", 0));
        actionValider->setText(QApplication::translate("MainWindow", "Valider", 0));
        actionHistogramme_2->setText(QApplication::translate("MainWindow", "Histogramme", 0));
        actionSupprimer->setText(QApplication::translate("MainWindow", "Supprimer", 0));
        actionContour->setText(QApplication::translate("MainWindow", "Contour", 0));
        actionRehaussement->setText(QApplication::translate("MainWindow", "Rehaussement ", 0));
        actionEtalement->setText(QApplication::translate("MainWindow", "Etalement", 0));
        actionEgalisation->setText(QApplication::translate("MainWindow", "Egalisation", 0));
        actionFiltre_Scharr->setText(QApplication::translate("MainWindow", "Filtre Scharr", 0));
        actionFiltre_Sobel->setText(QApplication::translate("MainWindow", "Filtre Sobel", 0));
        menuTest->setTitle(QApplication::translate("MainWindow", "&Fichier", 0));
        menu_Edition->setTitle(QApplication::translate("MainWindow", "&Edition", 0));
        menu_Affichage->setTitle(QApplication::translate("MainWindow", "&Affichage", 0));
        menu_Image->setTitle(QApplication::translate("MainWindow", "&Image", 0));
        menu_Effet->setTitle(QApplication::translate("MainWindow", "&Effet", 0));
        menu_Flou->setTitle(QApplication::translate("MainWindow", "&Flou", 0));
        menu_Datetction_de_contours->setTitle(QApplication::translate("MainWindow", "&Detection de contours", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
