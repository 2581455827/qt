#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initVar();
    initUi();
}
void MainWindow::upPos(){
    chartLineMutex.lock();
    pos_x[i] = i;
    pos_y[i] = qrand()%RAND_NUM;
    series->append(pos_x[i],pos_y[i]);
    ++i;
    //display charty
    series->clear();
    if(pos_x[i-1]>X_WIDTH || pos_y[i-1]>X_WIDTH){
        //区间动态变化
        _char_view->axisX()->setRange(i-X_WIDTH,i);
        if(pos_y[i-1]>X_WIDTH)
            _char_view->axisY()->setRange(pos_y[i-1]-Y_FLOAT,pos_y[i-1]+Y_FLOAT);
    }
    //qDebug()<<"i = "<<i;
        if(i>X_WIDTH){
            //绘制最新数据
            for(int j = i-X_WIDTH;j<i;j++){
                series->append(pos_x[j],pos_y[j]);
                //qDebug()<<series->at(j);

            }
        }
        else{   //绘制前若干个数据
            for(int j = 0;j<i;j++){
                series->append(pos_x[j],pos_y[j]);
                //qDebug()<<series->at(j);
            }
        }
    chartLineMutex.unlock();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initVar()
{
    i = 0;
    //随机数种子
    qsrand(NULL);
    //添加view
    _char_view = new QChart;

    series = new QLineSeries();
    Axis_x= new QValueAxis;
    Axis_y = new QValueAxis;
}

void MainWindow::initUi()
{
    //折线图显示
    ui->widget->setChart(_char_view);
    //添加折线
    _char_view->addSeries(series);
    //主题背景
    _char_view->setTheme(QChart::ChartThemeBrownSand);
    //曲线名称
    series->setName("test");
    //设置chart标题
    _char_view->setTitle("chart for test");
    //x坐标信息
    Axis_x->setTitleText("x");
    Axis_x->setMax(200);
    _char_view->setAxisX(Axis_x,series);
    //Y坐标信息
    Axis_y->setTitleText("y");
    Axis_y->setMax(200);
    _char_view->setAxisY(Axis_y,series);
    _char_view->legend()->setVisible(true);
    //每100ms添加数据并更新折线图
    chartTimer = new QTimer(this);
    connect(chartTimer,SIGNAL(timeout()),this,SLOT(upPos()));
    chartTimer->start(UPDATE_TIME);
}
