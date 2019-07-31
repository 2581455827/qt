#include "mainwindow.h"
#include <QApplication>
#include <QtCharts/QChartView>

/*
    运行环境:windows+QT5.7.0
*/

using namespace QtCharts;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    w.show();

    return a.exec();
}
