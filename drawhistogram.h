#ifndef DRAWHISTOGRAM_H
#define DRAWHISTOGRAM_H
//该类为画直方图的控件

#include <QWidget>
#include<QDialog>
typedef quint8  BYTE; //BYTE表示8位无符号整数，一个字节
typedef qint32  LONG; //LONG表示32位整数，四个字节
class QPixmap;
class QPushButton;
class QLineEdit;
class QLabel;

class drawHistogram : public QDialog
{
    Q_OBJECT
public:
    explicit drawHistogram(QWidget *parent = 0);
    drawHistogram(LONG *);
    void setData(LONG *data);
signals:
    
public slots:
private:
    QPixmap *board;                 //画直方图控件
    QPushButton *okButton;          //确定按钮
    QPushButton *cancelButton;      //取消按钮
    QLineEdit *lowLineEdit;         //显示下限
    QLineEdit *highLineEdit;        //显示上限
    QLabel *lowLabel;               //下限标签
    QLabel *highLabel;              //上限标签
    LONG *data;                     //data指向grayCount,也就是指向灰度直方图数据


    void init();                    //初始化变量
protected:
    void paintEvent(QPaintEvent *);
};

#endif // DRAWHISTOGRAM_H
