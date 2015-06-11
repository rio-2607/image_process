#include "drawhistogram.h"
#include<QPixmap>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QVBoxLayout>
#include<QPainter>
#include<QMessageBox>
#include<QDebug>
#include<QPen>
drawHistogram::drawHistogram(QWidget *parent) :
    QDialog(parent)
{
    init();
}

drawHistogram::drawHistogram(LONG */*dataToDraw*/):
    QDialog()
{
}


void drawHistogram::init()
{
    board = new QPixmap(341,321);
    board->fill(Qt::white);
    lowLabel = new QLabel(tr("显示下限"),this);
    lowLabel->setGeometry(QRect(360, 20, 54, 12));
    lowLineEdit = new QLineEdit(this);
    lowLineEdit->setGeometry(QRect(360, 60, 71, 31));
    lowLineEdit->setText("0");

    highLabel = new QLabel(tr("显示上限"),this);
    highLabel->setGeometry(QRect(360, 120, 54, 12));
    highLineEdit = new QLineEdit(this);
    highLineEdit->setGeometry(QRect(360, 160, 71, 31));
    highLineEdit->setText("255");

    okButton = new QPushButton(tr("确定"),this);
    okButton->setGeometry(QRect(360, 230, 75, 31));
    cancelButton = new QPushButton(tr("取消"),this);
    cancelButton->setGeometry(QRect(360, 300, 75, 31));
    setFixedSize(437,340);
    setWindowFlags(windowFlags() &~ Qt::WindowMinMaxButtonsHint);
    setStyleSheet("QWidget{background:rgb(100,200,200)}");
    setWindowTitle(tr("灰度直方图"));
    lowLineEdit->setEnabled(false);
    highLineEdit->setEnabled(false);


}

void drawHistogram::setData(LONG *dataToDraw)
{
    data = dataToDraw;
}
//这段代码有待改善2013.10.13，可以去除多余的painter
void drawHistogram::paintEvent(QPaintEvent *)
{
    board->fill(Qt::white);
    QPainter *painterToDrawAxe = new QPainter(board);               //这个painter用来画坐标轴，等画完坐标轴在释放掉
    QPen penOfHistogram;
    penOfHistogram.setWidthF(0.5);
    penOfHistogram.setColor(Qt::black);
    painterToDrawAxe->setPen(penOfHistogram);
    //画X轴
    painterToDrawAxe->drawLine(7,310,335,310);
    painterToDrawAxe->drawLine(335,310,330,305);
    painterToDrawAxe->drawLine(335,310,330,315);
    //画Y轴
    painterToDrawAxe->drawLine(7,310,7,5);
    painterToDrawAxe->drawLine(7,5,12,10);
    painterToDrawAxe->drawLine(7,5,2,10);
    //painterToDrawAxe->drawLine(317,310,317,315);
    painterToDrawAxe->drawText(7,320,tr("0"));
    for(int i=1;i<6;i++)
    {
        painterToDrawAxe->drawLine((320.0/255.0)*i*50+7,310,(320.0/255.0)*i*50+7,315);
        painterToDrawAxe->drawText((320.0/255.0)*i*50-12,320,tr("%1").arg(i*50));
    }
    painterToDrawAxe->drawLine(312,310,312,315);
    delete(painterToDrawAxe);

    QPainter painter1(board);
    QPen pen2;
    pen2.setColor(Qt::red);
    painter1.setPen(pen2);
    int max = data[0];
    for(int i=1;i<256;i++)
    {
        if(max <data[i])
            max = data[i];
    }
    painter1.drawText(10,10,tr("%1").arg(max));

    for(int i = 0;i<256;i++)
    {
        painter1.drawLine(7+(320.0/255.0)*i,310,7+(320.0/255.0)*i,(310 - (315*data[i])/max));
    }
    QPainter painter(this);
    painter.drawPixmap(10,10,*board);
}
