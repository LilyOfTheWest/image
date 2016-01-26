#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include "Image_Buffer.h"

class ImageViewer : public QMainWindow
{
  Q_OBJECT

  public:
    ImageViewer();
    ImageViewer(int);
    ~ImageViewer();

    private slots:

    void open();
    void saveas();
    void close_current();
    void about();

    void  cannyedge(int);
    void  invertvalues(int);
    void  rgbtolum(int);
    void  gaussianfilter(int);
    void  hrgradient(int);
    void  vtgradient(int);
    void  border_detect(int);    

    void  start_webcam(); 
    void  stop_webcam(); 
    void  query_frame(); 
    void  matrix_mode(); 
    void  invert_webcam();

  private:

    void loadImage();
    void createActions();
    void createMenus();
    void updateStatusWebcam(int);
    void updateStatus(int);
    void paintEvent(QPaintEvent*);

    QLabel *imageLabel;

    IplImage* first_image; // First ImageViewer for capture
    IplImage* current_image; // ImageViewer for cvCreateImage
    CvCapture* capture; // Current capture
    QImage* current_qimage; // Current QImage 
    ImageBuffer* Raw_image; // Raw Image class
    QTimer* timer; // QTimer for repaint function
    ImageViewer* Image_viewer; // Current Window class
    QString fileName;

    int webcam_on;
    int webcam_off;
    int rgblum_status;
    int matrixMode;
    int invertWebcam;
    bool locked_draw;

    QAction *openAct;
    QAction *saveasAct;
    QAction *closeAct;
    QAction *exitAct;

    QAction *cannyedgeAct;
    QAction *invertAct;
    QAction *rgbtolumAct;
    QAction *gaussianfilterAct;
    QAction *hrgradientAct;
    QAction *vtgradientAct;
    QAction *borderdetectAct;
    QAction *startwebcamAct;
    QAction *stopwebcamAct;
    QAction *matrixAct;
    QAction *invertwebcamAct;
    QAction *aboutAct;

    QMenu *fileMenu;
    QMenu *filterMenu;
    QMenu *webcamMenu;
    QMenu *aboutMenu;
};

