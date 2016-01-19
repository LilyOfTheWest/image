#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif


namespace Ui {
class MainWindow;
}
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QScrollArea;
class PictLabel;
class QScrollBar;
class QLabel;
class QKernelConv;

class PicDisplay;
class QWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool loadFile(const QString &);

private slots:
    void open();
    void print();
    void inverseColor();
    void updateActionsWithoutImage();
    void updateActionsWithImage();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();

    void on_action_Ouvrir_triggered();

    void on_action_Fermer_triggered();

    void on_action_Imprimer_triggered();

    void on_actionZoom_avant_triggered();

    void on_action_Zoom_arriere_triggered();

    void on_actionFlou_triggered();

    void on_actionPipette_triggered();

    void on_actionSeamCarving_triggered();

    void on_action_Selection_triggered();

    void on_actionDeplacement_triggered();


    void on_action_Copier_triggered();

    void on_action_Coller_triggered();

    void on_action_Couper_triggered();

    void on_actionImageGris_triggered();

    void on_actionInverseCoul_triggered();

    void on_actionFusion_2_triggered();

    void on_actionCrop_triggered();

    void on_actionRecadrer_triggered();

    void on_actionValider_triggered();

    void on_actionRotation_90_Horaire_triggered();

    void on_action_Rotation_90_antihoraire_triggered();

    void on_actionRotation_180_triggered();

    void on_action_Annuler_triggered();

    void on_actionHistogramme_triggered();

    void on_actionContour_triggered();

private:
    Ui::MainWindow *ui;
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    bool loadFileToMerge(const QString &fileName);
    PictLabel *imageLabel;
    //QScrollArea *scrollArea;
    PicDisplay *pdis;
    double scaleFactor;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

};

#endif // MAINWINDOW_H
