/********************************************************************************
** Form generated from reading UI file 'picdisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICDISPLAY_H
#define UI_PICDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PicDisplay
{
public:
    QScrollArea *scrollAreaP;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonRGB;
    QRadioButton *radioButton_YUV;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *libCoul1;
    QLabel *valCoul1;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *libCoul2;
    QLabel *valCoul2;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *libCoul3;
    QLabel *valCoul3;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *libPosX;
    QLabel *valPosX;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *libPosY;
    QLabel *valPosY;
    QLabel *libTailleGeneral;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *libTailleHeigtht;
    QLineEdit *lineEdit_Height;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *libTailleWidth;
    QLineEdit *lineEdit_Width;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *libCoulA;
    QLabel *valCoulA;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_13;
    QRadioButton *radioButtonImg1;
    QLabel *val_alpha_img1;
    QSlider *horizontalSlider_img1;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *radioButtonImg2;
    QLabel *val_alpha_img2;
    QSlider *horizontalSlider_img2;
    QPushButton *pushButtonResize;
    QLabel *label;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *checkBoxFlou;
    QLabel *libFlou1;
    QLineEdit *lineEditFlou1;
    QComboBox *comboBoxFlou1;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_Rehaus;
    QLabel *lib_Rehaus;
    QLineEdit *lineEdit_Rehaus;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *checkBox_Etal;
    QLabel *lib_Etal1;
    QLineEdit *lineEdit_Etal1;
    QLabel *lib_Etal2;
    QLineEdit *lineEdit_Etal2;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *checkBox_Filtre;
    QLabel *lib_Filtre1;
    QLineEdit *lineEdit_Filtre;
    QPushButton *pushButtonFiltreEdition;
    QPushButton *pushButton_FiltreLaunch;
    QWidget *layoutWidget9;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *checkBoxSeam;
    QCheckBox *checkSeamVisu;
    QComboBox *comboBoxSeamActions;
    QCheckBox *checkBoxSeamCompress;
    QLineEdit *lineEditSeamSize;
    QSlider *horizontalSliderSeamSize;

    void setupUi(QWidget *PicDisplay)
    {
        if (PicDisplay->objectName().isEmpty())
            PicDisplay->setObjectName(QStringLiteral("PicDisplay"));
        PicDisplay->resize(933, 467);
        scrollAreaP = new QScrollArea(PicDisplay);
        scrollAreaP->setObjectName(QStringLiteral("scrollAreaP"));
        scrollAreaP->setGeometry(QRect(130, 140, 16, 16));
        scrollAreaP->setMinimumSize(QSize(0, 0));
        scrollAreaP->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 16, 16));
        scrollAreaP->setWidget(scrollAreaWidgetContents);
        groupBox = new QGroupBox(PicDisplay);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 101, 441));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 10, 93, 19));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioButtonRGB = new QRadioButton(layoutWidget);
        radioButtonRGB->setObjectName(QStringLiteral("radioButtonRGB"));

        horizontalLayout->addWidget(radioButtonRGB);

        radioButton_YUV = new QRadioButton(layoutWidget);
        radioButton_YUV->setObjectName(QStringLiteral("radioButton_YUV"));

        horizontalLayout->addWidget(radioButton_YUV);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(2, 38, 81, 16));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        libCoul1 = new QLabel(layoutWidget1);
        libCoul1->setObjectName(QStringLiteral("libCoul1"));

        horizontalLayout_2->addWidget(libCoul1);

        valCoul1 = new QLabel(layoutWidget1);
        valCoul1->setObjectName(QStringLiteral("valCoul1"));

        horizontalLayout_2->addWidget(valCoul1);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(2, 58, 81, 20));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        libCoul2 = new QLabel(layoutWidget2);
        libCoul2->setObjectName(QStringLiteral("libCoul2"));

        horizontalLayout_3->addWidget(libCoul2);

        valCoul2 = new QLabel(layoutWidget2);
        valCoul2->setObjectName(QStringLiteral("valCoul2"));

        horizontalLayout_3->addWidget(valCoul2);

        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(2, 88, 81, 16));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        libCoul3 = new QLabel(layoutWidget_2);
        libCoul3->setObjectName(QStringLiteral("libCoul3"));

        horizontalLayout_4->addWidget(libCoul3);

        valCoul3 = new QLabel(layoutWidget_2);
        valCoul3->setObjectName(QStringLiteral("valCoul3"));

        horizontalLayout_4->addWidget(valCoul3);

        layoutWidget_3 = new QWidget(groupBox);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 140, 50, 15));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        libPosX = new QLabel(layoutWidget_3);
        libPosX->setObjectName(QStringLiteral("libPosX"));

        horizontalLayout_5->addWidget(libPosX);

        valPosX = new QLabel(layoutWidget_3);
        valPosX->setObjectName(QStringLiteral("valPosX"));

        horizontalLayout_5->addWidget(valPosX);

        layoutWidget_4 = new QWidget(groupBox);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(0, 160, 50, 15));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        libPosY = new QLabel(layoutWidget_4);
        libPosY->setObjectName(QStringLiteral("libPosY"));

        horizontalLayout_6->addWidget(libPosY);

        valPosY = new QLabel(layoutWidget_4);
        valPosY->setObjectName(QStringLiteral("valPosY"));

        horizontalLayout_6->addWidget(valPosY);

        libTailleGeneral = new QLabel(groupBox);
        libTailleGeneral->setObjectName(QStringLiteral("libTailleGeneral"));
        libTailleGeneral->setGeometry(QRect(0, 190, 84, 16));
        layoutWidget_5 = new QWidget(groupBox);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(0, 240, 101, 22));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        libTailleHeigtht = new QLabel(layoutWidget_5);
        libTailleHeigtht->setObjectName(QStringLiteral("libTailleHeigtht"));

        horizontalLayout_8->addWidget(libTailleHeigtht);

        lineEdit_Height = new QLineEdit(layoutWidget_5);
        lineEdit_Height->setObjectName(QStringLiteral("lineEdit_Height"));

        horizontalLayout_8->addWidget(lineEdit_Height);

        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 210, 101, 22));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        libTailleWidth = new QLabel(layoutWidget3);
        libTailleWidth->setObjectName(QStringLiteral("libTailleWidth"));

        horizontalLayout_7->addWidget(libTailleWidth);

        lineEdit_Width = new QLineEdit(layoutWidget3);
        lineEdit_Width->setObjectName(QStringLiteral("lineEdit_Width"));

        horizontalLayout_7->addWidget(lineEdit_Width);

        layoutWidget4 = new QWidget(groupBox);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(0, 110, 81, 16));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        libCoulA = new QLabel(layoutWidget4);
        libCoulA->setObjectName(QStringLiteral("libCoulA"));

        horizontalLayout_12->addWidget(libCoulA);

        valCoulA = new QLabel(layoutWidget4);
        valCoulA->setObjectName(QStringLiteral("valCoulA"));

        horizontalLayout_12->addWidget(valCoulA);

        layoutWidget5 = new QWidget(groupBox);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(0, 310, 88, 102));
        verticalLayout = new QVBoxLayout(layoutWidget5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        radioButtonImg1 = new QRadioButton(layoutWidget5);
        radioButtonImg1->setObjectName(QStringLiteral("radioButtonImg1"));

        horizontalLayout_13->addWidget(radioButtonImg1);

        val_alpha_img1 = new QLabel(layoutWidget5);
        val_alpha_img1->setObjectName(QStringLiteral("val_alpha_img1"));

        horizontalLayout_13->addWidget(val_alpha_img1);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalSlider_img1 = new QSlider(layoutWidget5);
        horizontalSlider_img1->setObjectName(QStringLiteral("horizontalSlider_img1"));
        horizontalSlider_img1->setMaximum(255);
        horizontalSlider_img1->setValue(255);
        horizontalSlider_img1->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_img1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        radioButtonImg2 = new QRadioButton(layoutWidget5);
        radioButtonImg2->setObjectName(QStringLiteral("radioButtonImg2"));

        horizontalLayout_14->addWidget(radioButtonImg2);

        val_alpha_img2 = new QLabel(layoutWidget5);
        val_alpha_img2->setObjectName(QStringLiteral("val_alpha_img2"));

        horizontalLayout_14->addWidget(val_alpha_img2);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalSlider_img2 = new QSlider(layoutWidget5);
        horizontalSlider_img2->setObjectName(QStringLiteral("horizontalSlider_img2"));
        horizontalSlider_img2->setMaximum(255);
        horizontalSlider_img2->setValue(255);
        horizontalSlider_img2->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_img2);

        pushButtonResize = new QPushButton(groupBox);
        pushButtonResize->setObjectName(QStringLiteral("pushButtonResize"));
        pushButtonResize->setGeometry(QRect(0, 270, 91, 23));
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget_2->raise();
        layoutWidget_3->raise();
        layoutWidget_4->raise();
        libTailleGeneral->raise();
        layoutWidget_5->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        pushButtonResize->raise();
        label = new QLabel(PicDisplay);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 0, 47, 13));
        groupBox_2 = new QGroupBox(PicDisplay);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(130, 10, 801, 111));
        layoutWidget6 = new QWidget(groupBox_2);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 20, 261, 22));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        checkBoxFlou = new QCheckBox(layoutWidget6);
        checkBoxFlou->setObjectName(QStringLiteral("checkBoxFlou"));

        horizontalLayout_9->addWidget(checkBoxFlou);

        libFlou1 = new QLabel(layoutWidget6);
        libFlou1->setObjectName(QStringLiteral("libFlou1"));

        horizontalLayout_9->addWidget(libFlou1);

        lineEditFlou1 = new QLineEdit(layoutWidget6);
        lineEditFlou1->setObjectName(QStringLiteral("lineEditFlou1"));

        horizontalLayout_9->addWidget(lineEditFlou1);

        comboBoxFlou1 = new QComboBox(layoutWidget6);
        comboBoxFlou1->setObjectName(QStringLiteral("comboBoxFlou1"));

        horizontalLayout_9->addWidget(comboBoxFlou1);

        layoutWidget7 = new QWidget(groupBox_2);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(10, 50, 242, 22));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        checkBox_Rehaus = new QCheckBox(layoutWidget7);
        checkBox_Rehaus->setObjectName(QStringLiteral("checkBox_Rehaus"));

        horizontalLayout_10->addWidget(checkBox_Rehaus);

        lib_Rehaus = new QLabel(layoutWidget7);
        lib_Rehaus->setObjectName(QStringLiteral("lib_Rehaus"));

        horizontalLayout_10->addWidget(lib_Rehaus);

        lineEdit_Rehaus = new QLineEdit(layoutWidget7);
        lineEdit_Rehaus->setObjectName(QStringLiteral("lineEdit_Rehaus"));

        horizontalLayout_10->addWidget(lineEdit_Rehaus);

        layoutWidget8 = new QWidget(groupBox_2);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(290, 20, 271, 22));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        checkBox_Etal = new QCheckBox(layoutWidget8);
        checkBox_Etal->setObjectName(QStringLiteral("checkBox_Etal"));

        horizontalLayout_11->addWidget(checkBox_Etal);

        lib_Etal1 = new QLabel(layoutWidget8);
        lib_Etal1->setObjectName(QStringLiteral("lib_Etal1"));

        horizontalLayout_11->addWidget(lib_Etal1);

        lineEdit_Etal1 = new QLineEdit(layoutWidget8);
        lineEdit_Etal1->setObjectName(QStringLiteral("lineEdit_Etal1"));

        horizontalLayout_11->addWidget(lineEdit_Etal1);

        lib_Etal2 = new QLabel(layoutWidget8);
        lib_Etal2->setObjectName(QStringLiteral("lib_Etal2"));

        horizontalLayout_11->addWidget(lib_Etal2);

        lineEdit_Etal2 = new QLineEdit(layoutWidget8);
        lineEdit_Etal2->setObjectName(QStringLiteral("lineEdit_Etal2"));

        horizontalLayout_11->addWidget(lineEdit_Etal2);

        layoutWidget_6 = new QWidget(groupBox_2);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(290, 50, 401, 25));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        checkBox_Filtre = new QCheckBox(layoutWidget_6);
        checkBox_Filtre->setObjectName(QStringLiteral("checkBox_Filtre"));

        horizontalLayout_15->addWidget(checkBox_Filtre);

        lib_Filtre1 = new QLabel(layoutWidget_6);
        lib_Filtre1->setObjectName(QStringLiteral("lib_Filtre1"));

        horizontalLayout_15->addWidget(lib_Filtre1);

        lineEdit_Filtre = new QLineEdit(layoutWidget_6);
        lineEdit_Filtre->setObjectName(QStringLiteral("lineEdit_Filtre"));

        horizontalLayout_15->addWidget(lineEdit_Filtre);

        pushButtonFiltreEdition = new QPushButton(layoutWidget_6);
        pushButtonFiltreEdition->setObjectName(QStringLiteral("pushButtonFiltreEdition"));

        horizontalLayout_15->addWidget(pushButtonFiltreEdition);

        pushButton_FiltreLaunch = new QPushButton(layoutWidget_6);
        pushButton_FiltreLaunch->setObjectName(QStringLiteral("pushButton_FiltreLaunch"));

        horizontalLayout_15->addWidget(pushButton_FiltreLaunch);

        layoutWidget9 = new QWidget(groupBox_2);
        layoutWidget9->setObjectName(QStringLiteral("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(12, 80, 681, 24));
        horizontalLayout_16 = new QHBoxLayout(layoutWidget9);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        checkBoxSeam = new QCheckBox(layoutWidget9);
        checkBoxSeam->setObjectName(QStringLiteral("checkBoxSeam"));

        horizontalLayout_16->addWidget(checkBoxSeam);

        checkSeamVisu = new QCheckBox(layoutWidget9);
        checkSeamVisu->setObjectName(QStringLiteral("checkSeamVisu"));

        horizontalLayout_16->addWidget(checkSeamVisu);

        comboBoxSeamActions = new QComboBox(layoutWidget9);
        comboBoxSeamActions->setObjectName(QStringLiteral("comboBoxSeamActions"));

        horizontalLayout_16->addWidget(comboBoxSeamActions);

        checkBoxSeamCompress = new QCheckBox(layoutWidget9);
        checkBoxSeamCompress->setObjectName(QStringLiteral("checkBoxSeamCompress"));

        horizontalLayout_16->addWidget(checkBoxSeamCompress);

        lineEditSeamSize = new QLineEdit(layoutWidget9);
        lineEditSeamSize->setObjectName(QStringLiteral("lineEditSeamSize"));
        lineEditSeamSize->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditSeamSize->sizePolicy().hasHeightForWidth());
        lineEditSeamSize->setSizePolicy(sizePolicy);
        lineEditSeamSize->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_16->addWidget(lineEditSeamSize);

        horizontalSliderSeamSize = new QSlider(layoutWidget9);
        horizontalSliderSeamSize->setObjectName(QStringLiteral("horizontalSliderSeamSize"));
        horizontalSliderSeamSize->setOrientation(Qt::Horizontal);

        horizontalLayout_16->addWidget(horizontalSliderSeamSize);

        scrollAreaP->raise();
        label->raise();
        groupBox_2->raise();
        groupBox->raise();

        retranslateUi(PicDisplay);

        QMetaObject::connectSlotsByName(PicDisplay);
    } // setupUi

    void retranslateUi(QWidget *PicDisplay)
    {
        PicDisplay->setWindowTitle(QApplication::translate("PicDisplay", "Form", 0));
        groupBox->setTitle(QApplication::translate("PicDisplay", "Couleur", 0));
        radioButtonRGB->setText(QApplication::translate("PicDisplay", "RGB", 0));
        radioButton_YUV->setText(QApplication::translate("PicDisplay", "YUV", 0));
        libCoul1->setText(QApplication::translate("PicDisplay", "R", 0));
        valCoul1->setText(QApplication::translate("PicDisplay", "0", 0));
        libCoul2->setText(QApplication::translate("PicDisplay", "G", 0));
        valCoul2->setText(QApplication::translate("PicDisplay", "0", 0));
        libCoul3->setText(QApplication::translate("PicDisplay", "B", 0));
        valCoul3->setText(QApplication::translate("PicDisplay", "0", 0));
        libPosX->setText(QApplication::translate("PicDisplay", "X:", 0));
        valPosX->setText(QApplication::translate("PicDisplay", "0", 0));
        libPosY->setText(QApplication::translate("PicDisplay", "Y:", 0));
        valPosY->setText(QApplication::translate("PicDisplay", "0", 0));
        libTailleGeneral->setText(QApplication::translate("PicDisplay", "Taille de l' image :", 0));
        libTailleHeigtht->setText(QApplication::translate("PicDisplay", "libTaille", 0));
        libTailleWidth->setText(QApplication::translate("PicDisplay", "libTaille", 0));
        libCoulA->setText(QApplication::translate("PicDisplay", "Alpha:", 0));
        valCoulA->setText(QApplication::translate("PicDisplay", "0", 0));
        radioButtonImg1->setText(QApplication::translate("PicDisplay", "image 1", 0));
        val_alpha_img1->setText(QApplication::translate("PicDisplay", "255", 0));
        radioButtonImg2->setText(QApplication::translate("PicDisplay", "image 2", 0));
        val_alpha_img2->setText(QApplication::translate("PicDisplay", "255", 0));
        pushButtonResize->setText(QApplication::translate("PicDisplay", "Change", 0));
        label->setText(QString());
        groupBox_2->setTitle(QApplication::translate("PicDisplay", "Param\303\250tres :", 0));
        checkBoxFlou->setText(QApplication::translate("PicDisplay", "Flou", 0));
        libFlou1->setText(QApplication::translate("PicDisplay", "Taille noyau :", 0));
        comboBoxFlou1->clear();
        comboBoxFlou1->insertItems(0, QStringList()
         << QApplication::translate("PicDisplay", "Moyenneur", 0)
         << QApplication::translate("PicDisplay", "Gaussien", 0)
        );
        checkBox_Rehaus->setText(QApplication::translate("PicDisplay", "Rehaussement", 0));
        lib_Rehaus->setText(QApplication::translate("PicDisplay", "Coeff de rendu :", 0));
        checkBox_Etal->setText(QApplication::translate("PicDisplay", "Etalement", 0));
        lib_Etal1->setText(QApplication::translate("PicDisplay", "Alpha :", 0));
        lineEdit_Etal1->setText(QString());
        lib_Etal2->setText(QApplication::translate("PicDisplay", "Beta :", 0));
        checkBox_Filtre->setText(QApplication::translate("PicDisplay", "Filtre personalis\303\251", 0));
        lib_Filtre1->setText(QApplication::translate("PicDisplay", "Taille noyau :", 0));
        lineEdit_Filtre->setText(QString());
        pushButtonFiltreEdition->setText(QApplication::translate("PicDisplay", "Edition", 0));
        pushButton_FiltreLaunch->setText(QApplication::translate("PicDisplay", "Filtre", 0));
        checkBoxSeam->setText(QApplication::translate("PicDisplay", "Seam Carving", 0));
        checkSeamVisu->setText(QApplication::translate("PicDisplay", "Visu lignes", 0));
        comboBoxSeamActions->clear();
        comboBoxSeamActions->insertItems(0, QStringList()
         << QApplication::translate("PicDisplay", "-- Actions en option --", 0)
         << QApplication::translate("PicDisplay", "D\303\251f. zones \303\240 prot\303\251ger", 0)
         << QApplication::translate("PicDisplay", "D\303\251f. zones \303\240 supprimer", 0)
         << QApplication::translate("PicDisplay", "Recalcul lignes d'\303\251nergie", 0)
        );
        checkBoxSeamCompress->setText(QApplication::translate("PicDisplay", "Compression", 0));
    } // retranslateUi

};

namespace Ui {
    class PicDisplay: public Ui_PicDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICDISPLAY_H
