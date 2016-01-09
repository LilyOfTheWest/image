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
    void prodConv();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();

    void on_actionFlouter_triggered();

    void on_action_Open_triggered();

    void on_actionPick_Color_triggered();

    void on_actionSelect_triggered();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    PictLabel *imageLabel;
    QScrollArea *scrollArea;
    PicDisplay *pdis;
    double scaleFactor;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *inverseColorAct;
    QAction *prodConvAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

};

#endif // MAINWINDOW_H
