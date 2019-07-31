#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include <Qtcharts/QChartView>
#include <QValueAxis>
#include <QTimer>

#define X_WIDTH 200 //x轴宽度
#define Y_FLOAT 100 //Y轴数据浮动大小
#define UPDATE_TIME 100 //每100ms更新一次数据
#define RAND_NUM 50 //随机数取值范围
using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public:
    void updateChart();//更新折线图
    void initVar();//初始化变量
    void initUi();//初始化UI
private slots:
 void upPos();//更新折线图及坐标
private:
    Ui::MainWindow *ui;
    QLineSeries* series;//折线图
    QValueAxis* Axis_x;//x轴
    QValueAxis* Axis_y;//Y轴
    QChart* _char_view;//图表
    int i;              //有i个数据
    int pos_x[1000];    //数据的x坐标
    int pos_y[1000];    //数据的Y坐标
    QTimer *chartTimer; //定时器
    QMutex chartLineMutex;//互斥锁
};

#endif // MAINWINDOW_H
