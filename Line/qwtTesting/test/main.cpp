#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QFont>
#include <QIcon>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <qwt_plot.h>
#include <qwt_plot_histogram.h>
#include <qwt_series_data.h>
#include <qwt_scale_map.h>
//#include <QtWidgets>
#include "mafenetre.h"
#include "qwt_plot_grid.h"
#include "qwt_interval.h"
#include "qwt_series_data.h"
#include "qwt_series_store.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    /* Pour traduire en FR */
    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;

    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    app.installTranslator(&translator);
    /* Fin */

    MaFenetre w(230,120);

    QwtPlot *myPlot = new QwtPlot();
    myPlot->setCanvasBackground(Qt::gray);
    myPlot->setTitle("");
    myPlot->setFixedHeight(600);
    myPlot->setFixedWidth(800);
    myPlot->setAxisScale( QwtPlot::yLeft, 0, 10000 ); //Scale the y-axis
    myPlot->setAxisScale(QwtPlot::xBottom,0,255); //Scale the x-axis
    QwtPlotHistogram *myHisto = new QwtPlotHistogram("Répartition des pixels");
    myPlot->show();
    return app.exec();
}
