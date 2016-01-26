#include <QApplication>
#include "Image_Viewer.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  ImageViewer MainViewer;
  MainViewer.show();
  return app.exec();
}
