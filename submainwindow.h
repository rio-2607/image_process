#ifndef SUBMAINWINDOW_H
#define SUBMAINWINDOW_H

#include <QMainWindow>
class QAction;
class QMenu;
class QLabel;
class QScrollArea;
class QImage;
class subMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit subMainWindow(QWidget *parent = 0);
    void setImage(QImage image);
signals:
    
public slots:
private:
    QMenu *menu;
    QAction *saveFile;              //����ͼƬ
    QAction *exit;                  //�˳�

    void createMenu();


    QLabel *subImageLabel;             //��ʾͼƬ��label�ؼ�
    QScrollArea *subScrollArea;        //����ؼ�
    QImage subImageToOperation;        //ʵ��Ҫ�����ͼƬ
    QImage backImage;                   //����ͼƬ,�����ж�ͼƬ�Ƿ���Ҫ����
    bool noSave;                        //�ж�ͼƬ�Ƿ���Ҫ����
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);     //�����¼�  ����
private slots:
    void saveImage();                   //����ͼƬ �ۺ���

    
};

#endif // SUBMAINWINDOW_H
