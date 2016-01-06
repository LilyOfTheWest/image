#include "Image_Viewer.h"

ImageViewer::ImageViewer()
{ int status_off = 1;
  imageLabel = new QLabel;
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);
  current_qimage = new QImage();
  matrixMode = 0;

  setCentralWidget(imageLabel);    
  createActions();
  createMenus();
  updateStatus(status_off);
  setWindowTitle(tr("Canny Edge"));  
  resize(500, 400);  
}

ImageViewer::ImageViewer(int status_off)
{ 
  int webcam_on = 0;
  imageLabel = new QLabel;
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);
  current_qimage = new QImage();

  setCentralWidget(imageLabel);    
  createActions();
  createMenus();
  updateStatus(status_off);
  updateStatusWebcam(webcam_on);
  setWindowTitle(tr("Canny Edge"));  
  resize(500, 400);  
}

ImageViewer::~ImageViewer()
{
  delete imageLabel;
}

void ImageViewer::loadImage()
{
  int status_off = 0;
  imageLabel->setPixmap(QPixmap::fromImage(*current_qimage));
  imageLabel->resize(current_qimage->width(),current_qimage->height());  
  resize(current_qimage->width(),current_qimage->height());
  updateStatus(status_off);
}	

void ImageViewer::open()
{ 
  fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());

  if (!fileName.isEmpty()) {
    *current_qimage = QImage(fileName);
    if (current_qimage->isNull()) {
      QMessageBox::information(this, tr("Canny Edge"),
          tr("Cannot load %1.").arg(fileName));
      return;
    }
    loadImage();
  }
}

void ImageViewer::saveas()
{
  // construct a filter of all supported formats
  QString filter;
  QList<QByteArray> formats = QImageWriter::supportedImageFormats();
  foreach (QString format, formats)
  {
    filter += QString("%1 files (*.%2);;").arg(format.toUpper()).arg(format);
  }

  // remove unnecessary chars from the end of the filter
  if (filter.endsWith(";;"))
  {
    filter.chop(2);
  }

  // get save file name
  QString selectedFilter;
  QString fileName = QFileDialog::getSaveFileName(this,"Save image as", QDir::currentPath(), filter, &selectedFilter);

  if (!fileName.isEmpty())
  {
    // check for the selected format
    QString format = selectedFilter.split(" ").at(0);
    QFileInfo fi(fileName);
    if (!fi.suffix().endsWith(format, Qt::CaseInsensitive))
    {
      // remove possible incorrect suffix
      fileName.chop(fi.suffix().length());

      // set correct suffix
      fileName += "." + format.toLower();
    }

    // save image in the selected format
    if (!current_qimage->save(fileName, format.toAscii().constData()))
    {
      QMessageBox::information(this, "Canny Edge", QString("Unable to save %1.").arg(fileName));
    }
  }
}

void ImageViewer::close_current()
{ int status_off = 1;
  current_qimage = new QImage;
  imageLabel->setPixmap(QPixmap::fromImage(*current_qimage));
  imageLabel->resize(500,400);
  resize(500,400);
  updateStatus(status_off);
}

void ImageViewer::about()
{
  QMessageBox::about(this, tr("About Canny Edge"),
      tr("<p>This graphical user interface shows how to combine Qt and"
        " OpenCV. It makes image processing by doing blur filter with "
        " Gaussian convolution, edges detection with Sobel operators."
        " This Canny Edge chain is also applied to webcam streaming</p>"
        ));
}

void ImageViewer::createActions()
{ 
  int webcam_off = 1; 

  QSignalMapper* mapper0 = new QSignalMapper(this);  
  QSignalMapper* mapper1 = new QSignalMapper(this);  
  QSignalMapper* mapper2 = new QSignalMapper(this);  
  QSignalMapper* mapper3 = new QSignalMapper(this);  
  QSignalMapper* mapper4 = new QSignalMapper(this);      
  QSignalMapper* mapper5 = new QSignalMapper(this);  
  QSignalMapper* mapper6 = new QSignalMapper(this);  

  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcut(tr("Ctrl+O"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  saveasAct = new QAction(tr("&Save As..."), this);
  saveasAct->setShortcut(tr("Ctrl+S"));
  connect(saveasAct, SIGNAL(triggered()), this, SLOT(saveas()));  

  closeAct = new QAction(tr("&Close"), this);
  closeAct->setShortcut(tr("Ctrl+F"));
  connect(closeAct, SIGNAL(triggered()), this, SLOT(close_current())); 

  exitAct = new QAction(tr("&Exit"), this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close())); 

  invertAct = new QAction(tr("&Invert Colors"), this);
  invertAct->setShortcut(tr("Ctrl+I"));
  connect(invertAct, SIGNAL(triggered()), mapper0, SLOT(map()));
  mapper0->setMapping(invertAct,webcam_off);  
  connect(mapper0, SIGNAL(mapped(int)), this, SLOT(invertvalues(int)));

  cannyedgeAct = new QAction(tr("&Canny Edge"), this);
  cannyedgeAct->setShortcut(tr("Ctrl+E"));
  connect(cannyedgeAct, SIGNAL(triggered()), mapper1, SLOT(map()));
  mapper1->setMapping(cannyedgeAct,webcam_off);  
  connect(mapper1, SIGNAL(mapped(int)), this, SLOT(cannyedge(int)));

  rgbtolumAct = new QAction(tr("&RGB to Luminance"), this);
  rgbtolumAct->setShortcut(tr("Ctrl+L"));
  connect(rgbtolumAct, SIGNAL(triggered()), mapper2, SLOT(map()));
  mapper2->setMapping(rgbtolumAct,webcam_off);  
  connect(mapper2, SIGNAL(mapped(int)), this, SLOT(rgbtolum(int)));

  gaussianfilterAct = new QAction(tr("&Gaussian Filter"), this);
  gaussianfilterAct->setShortcut(tr("Ctrl+G"));
  connect(gaussianfilterAct, SIGNAL(triggered()), mapper3, SLOT(map()));
  mapper3->setMapping(gaussianfilterAct,webcam_off);  
  connect(mapper3, SIGNAL(mapped(int)), this, SLOT(gaussianfilter(int)));

  hrgradientAct = new QAction(tr("&Horizontal Gradient"), this);
  hrgradientAct->setShortcut(tr("Ctrl+H"));
  connect(hrgradientAct, SIGNAL(triggered()), mapper4, SLOT(map()));
  mapper4->setMapping(hrgradientAct,webcam_off);  
  connect(mapper4, SIGNAL(mapped(int)), this, SLOT(hrgradient(int)));

  vtgradientAct = new QAction(tr("&Vertical Gradient"), this);
  vtgradientAct->setShortcut(tr("Ctrl+V"));
  connect(vtgradientAct, SIGNAL(triggered()), mapper5, SLOT(map()));
  mapper5->setMapping(vtgradientAct,webcam_off);    
  connect(mapper5, SIGNAL(mapped(int)), this, SLOT(vtgradient(int)));

  borderdetectAct = new QAction(tr("&Border Detection"), this);
  borderdetectAct->setShortcut(tr("Ctrl+B"));
  connect(borderdetectAct, SIGNAL(triggered()), mapper6, SLOT(map()));
  mapper6->setMapping(borderdetectAct,webcam_off);    
  connect(mapper6, SIGNAL(mapped(int)), this, SLOT(border_detect(int)));

  startwebcamAct = new QAction(tr("&Start Webcam"), this);
  connect(startwebcamAct, SIGNAL(triggered()), this, SLOT(start_webcam()));  

  stopwebcamAct = new QAction(tr("&Stop Webcam"), this);
  connect(stopwebcamAct, SIGNAL(triggered()), this, SLOT(stop_webcam()));    

  matrixAct = new QAction(tr("&Matrix Mode"), this);
  connect(matrixAct, SIGNAL(triggered()), this, SLOT(matrix_mode()));    

  invertwebcamAct = new QAction(tr("&Invert Colors"), this);
  connect(invertwebcamAct, SIGNAL(triggered()), this, SLOT(invert_webcam()));

  aboutAct = new QAction(tr("&About"), this);
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));      
}

void ImageViewer::createMenus()
{
  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(openAct);
  fileMenu->addSeparator();  
  fileMenu->addAction(saveasAct);  
  fileMenu->addSeparator();
  fileMenu->addAction(closeAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);


  filterMenu = new QMenu(tr("&Filter"), this);
  filterMenu->addAction(cannyedgeAct);
  filterMenu->addSeparator();
  filterMenu->addAction(invertAct);
  filterMenu->addSeparator();
  filterMenu->addAction(rgbtolumAct);
  filterMenu->addAction(gaussianfilterAct);
  filterMenu->addAction(hrgradientAct);
  filterMenu->addAction(vtgradientAct);    
  filterMenu->addAction(borderdetectAct);

  webcamMenu = new QMenu(tr("&Webcam"), this);
  webcamMenu->addAction(startwebcamAct);
  webcamMenu->addAction(stopwebcamAct);
  webcamMenu->addAction(matrixAct);
  webcamMenu->addAction(invertwebcamAct);

  aboutMenu = new QMenu(tr("&About"), this);
  aboutMenu->addAction(aboutAct);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(filterMenu);
  menuBar()->addMenu(webcamMenu);
  menuBar()->addMenu(aboutMenu);  
}

void ImageViewer::updateStatus( int close) 
{ 
  if(close) {
    closeAct->setEnabled(false);
    saveasAct->setEnabled(false); 
    filterMenu->menuAction()->setEnabled(false);       
    startwebcamAct->setEnabled(true);
    stopwebcamAct->setEnabled(false);
    matrixAct->setEnabled(false);
    invertwebcamAct->setEnabled(false);
  }
  else {
    closeAct->setEnabled(true);
    saveasAct->setEnabled(true);        
    filterMenu->menuAction()->setEnabled(true);       
    if (not current_qimage->isGrayscale())
    { rgbtolumAct->setEnabled(true);
      invertAct->setEnabled(false);
    }
    else
    {
      rgbtolumAct->setEnabled(false);
      invertAct->setEnabled(true);
    }
  }
}

void ImageViewer::updateStatusWebcam( int webcam_on) 
{ 
  if(webcam_on) {
    fileMenu->menuAction()->setEnabled(false);
    filterMenu->menuAction()->setEnabled(false);
    startwebcamAct->setEnabled(false);
    stopwebcamAct->setEnabled(true);    
    matrixAct->setEnabled(true);    
    if (matrixMode)
    { matrixAct->setText("Normal Mode");
      invertwebcamAct->setEnabled(false);
    }
    else
    { matrixAct->setText("Matrix Mode");
      invertwebcamAct->setEnabled(true);
      if (invertWebcam)
        matrixAct->setEnabled(false);
      else matrixAct->setEnabled(true);
    }
  }
  else {
    fileMenu->menuAction()->setEnabled(true);
    filterMenu->menuAction()->setEnabled(true);
    startwebcamAct->setEnabled(true);
    stopwebcamAct->setEnabled(false);        
    matrixAct->setEnabled(false);
    matrixAct->setText("Matrix Mode");
    invertwebcamAct->setEnabled(false);
  }
}    

void ImageViewer::invertvalues(int webcam_off)
{
  int fact=current_qimage->depth()/8;
  int status_off = 0;
  Raw_image= new ImageBuffer(current_qimage->height(),fact*current_qimage->width());
  Raw_image->transfer_to_exim(current_qimage);
  Raw_image->invert_values(fact);

  if(webcam_off) {
    ImageViewer* Image_viewer = new ImageViewer(status_off);
    Image_viewer->show();
    *Image_viewer->current_qimage = current_qimage->copy();
    Raw_image->transfer_to_qim(Image_viewer->current_qimage);  
    Image_viewer->loadImage();
    Image_viewer->repaint();
  }
  else {  
    Raw_image->transfer_to_qim(current_qimage);
  }
  delete Raw_image;        
}

void ImageViewer::cannyedge(int webcam_off)
{
  int fact=current_qimage->depth()/8;
  int status_off = 0;
  Raw_image= new ImageBuffer(current_qimage->height(),fact*current_qimage->width());
  Raw_image->transfer_to_exim(current_qimage);
  if (not current_qimage->isGrayscale())
    Raw_image->rgb_to_lum(fact); 
  Raw_image->gaussian(fact);
  Raw_image->normex(fact);
  Raw_image->normey(fact);
  Raw_image->norme(fact);
  Raw_image->invert_values(fact);

  if(webcam_off) {
    ImageViewer* Image_viewer = new ImageViewer(status_off);
    Image_viewer->show();
    *Image_viewer->current_qimage = current_qimage->copy();
    Raw_image->transfer_to_qim(Image_viewer->current_qimage);  
    Image_viewer->loadImage();
    Image_viewer->repaint();
  }
  else {  
    Raw_image->transfer_to_qim(current_qimage);
  }
  delete Raw_image;        
} 

void ImageViewer::vtgradient(int webcam_off)
{
  int fact=current_qimage->depth()/8;
  int status_off = 0;
  Raw_image= new ImageBuffer(current_qimage->height(),fact*current_qimage->width());
  Raw_image->transfer_to_exim(current_qimage);
  Raw_image->normex(fact);
  Raw_image->transferx();

  if(webcam_off) {
    ImageViewer* Image_viewer = new ImageViewer(status_off);
    Image_viewer->show();
    *Image_viewer->current_qimage = current_qimage->copy();
    Raw_image->transfer_to_qim(Image_viewer->current_qimage);  
    Image_viewer->loadImage();
    Image_viewer->repaint();
  }
  else {  
    Raw_image->transfer_to_qim(current_qimage);
  }
  delete Raw_image;        
} 

void ImageViewer::hrgradient(int webcam_off)
{
  int fact=current_qimage->depth()/8;
  int status_off = 0;
  Raw_image= new ImageBuffer(current_qimage->height(),fact*current_qimage->width());
  Raw_image->transfer_to_exim(current_qimage);
  Raw_image->normey(fact);
  Raw_image->transfery();

  if(webcam_off) {
    ImageViewer* Image_viewer = new ImageViewer(status_off);
    Image_viewer->show();
    *Image_viewer->current_qimage = current_qimage->copy();
    Raw_image->transfer_to_qim(Image_viewer->current_qimage);    
    Image_viewer->loadImage();
    Image_viewer->repaint();
  }
  else {  
    Raw_image->transfer_to_qim(current_qimage);
  }
  delete Raw_image;        
} 

void ImageViewer::gaussianfilter(int webcam_off)
{
  int fact=current_qimage->depth()/8;
  int status_off = 0;
  Raw_image=new ImageBuffer(current_qimage->height(),fact*current_qimage->width());
  Raw_image->transfer_to_exim(current_qimage);
  Raw_image->gaussian(fact);

  if(webcam_off) {
    ImageViewer* Image_viewer = new ImageViewer(status_off);
    Image_viewer->show();
    *Image_viewer->current_qimage = current_qimage->copy();
    Raw_image->transfer_to_qim(Image_viewer->current_qimage);    
    Image_viewer->loadImage();
    Image_viewer->repaint();
  }
  else {  
    Raw_image->transfer_to_qim(current_qimage);
  }
  delete Raw_image;
}

void ImageViewer::rgbtolum(int webcam_off)
{  
  int fact=current_qimage->depth()/8;
  int status_off = 0;
  Raw_image= new ImageBuffer(current_qimage->height(),fact*current_qimage->width());
  Raw_image->transfer_to_exim(current_qimage);
  Raw_image->rgb_to_lum(fact); 

  if(webcam_off) {
    ImageViewer* Image_viewer = new ImageViewer(status_off);
    Image_viewer->show();
    *Image_viewer->current_qimage = current_qimage->copy();
    Raw_image->transfer_to_qim(Image_viewer->current_qimage);
    Image_viewer->loadImage();
    Image_viewer->repaint();
  }
  else {  
    Raw_image->transfer_to_qim(current_qimage);
  }
  delete Raw_image;    
}    

void ImageViewer::border_detect(int webcam_off)
{ 
  int fact=current_qimage->depth()/8;
  int status_off = 0;
  Raw_image= new ImageBuffer(current_qimage->height(),fact*current_qimage->width());
  Raw_image->transfer_to_exim(current_qimage);
  Raw_image->normex(fact);
  Raw_image->normey(fact);
  Raw_image->norme(fact);

  if(webcam_off) {
    ImageViewer* Image_viewer = new ImageViewer(status_off);
    Image_viewer->show();
    *Image_viewer->current_qimage = current_qimage->copy();
    Raw_image->transfer_to_qim(Image_viewer->current_qimage);
    Image_viewer->loadImage();
    Image_viewer->repaint();
  }
  else {  
    Raw_image->transfer_to_qim(current_qimage);
  }
  delete Raw_image;
}

void ImageViewer::start_webcam()
{ 
  webcam_on = 1;
  invertWebcam = 0;
  close_current();  
  updateStatusWebcam(webcam_on);  
  // Init capture
  capture = cvCaptureFromCAM(0);
  first_image = cvQueryFrame(capture);
  // Init current qimage
  current_qimage = new QImage(QSize(first_image->width,first_image->height),QImage::Format_RGB32);
  resize(first_image->width,first_image->height);
  // start QTimer
  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(query_frame()));
  timer->start(0);    
}

void ImageViewer::stop_webcam()
{
  webcam_on = 0;
  matrixMode = 0;
  invertWebcam = 0;
  updateStatusWebcam(webcam_on);  
  timer->stop();
  cvReleaseImage(&first_image );
  cvReleaseImage(&current_image );
  cvReleaseCapture(&capture);
  updateStatusWebcam(webcam_on);
  close_current();  
}

void ImageViewer::query_frame() 
{
  webcam_off = 0;  
  IplImage* frame = cvQueryFrame(capture);
  int w = frame->width;
  int h = frame->height;

  if (matrixMode)
  {
    current_image = cvCreateImage(cvGetSize(frame),8,3); 
    cvCvtColor(frame,current_image,CV_BGR2RGB);
    int cvIndex = 0;
    int cvLineStart = 0;
    unsigned char red,green,blue;

    for(int j = 0; j < h; j++)
    {  
      cvIndex = cvLineStart;
      for(int i = 0; i < w; i++)
      {
        red = 0;
        green = current_image->imageData[cvIndex+1];
        blue = 0;

        current_qimage->setPixel(i,j,qRgb(red, green, blue));
        cvIndex += 3;
      }
      cvLineStart += current_image->widthStep;
    }
  }
  else
  {
    current_image = cvCreateImage(cvGetSize(frame),8,1); 
    cvCvtColor(frame,current_image,CV_BGR2GRAY);

    for(int j = 0; j < h; j++)
    {  
      for(int i = 0; i < w; i++)
      {
        current_qimage->setPixel(i,j,qRgb(current_image->imageData[i+j*w+1],current_image->imageData[i+j*w+1],current_image->imageData[i+j*w+1]));

      }
    }
  }
  gaussianfilter(webcam_off);
  border_detect(webcam_off);
  if (invertWebcam)
    invertvalues(webcam_off);
  cvReleaseImage(&current_image);
  repaint();
}

void ImageViewer::matrix_mode()
{
  matrixMode = !matrixMode;
  updateStatusWebcam(webcam_on);  
}

void ImageViewer::invert_webcam()
{
  invertWebcam = !invertWebcam;
  updateStatusWebcam(webcam_on);  
}

void ImageViewer::paintEvent(QPaintEvent*)
{
  QPainter painter(this); 
  painter.drawImage(QRect(0,0,current_qimage->width(),current_qimage->height()),*current_qimage);
}
