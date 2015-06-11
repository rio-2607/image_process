#ifndef DRAWHISTOGRAM_H
#define DRAWHISTOGRAM_H
//����Ϊ��ֱ��ͼ�Ŀؼ�

#include <QWidget>
#include<QDialog>
typedef quint8  BYTE; //BYTE��ʾ8λ�޷���������һ���ֽ�
typedef qint32  LONG; //LONG��ʾ32λ�������ĸ��ֽ�
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
    QPixmap *board;                 //��ֱ��ͼ�ؼ�
    QPushButton *okButton;          //ȷ����ť
    QPushButton *cancelButton;      //ȡ����ť
    QLineEdit *lowLineEdit;         //��ʾ����
    QLineEdit *highLineEdit;        //��ʾ����
    QLabel *lowLabel;               //���ޱ�ǩ
    QLabel *highLabel;              //���ޱ�ǩ
    LONG *data;                     //dataָ��grayCount,Ҳ����ָ��Ҷ�ֱ��ͼ����


    void init();                    //��ʼ������
protected:
    void paintEvent(QPaintEvent *);
};

#endif // DRAWHISTOGRAM_H
