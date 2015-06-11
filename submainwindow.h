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
    QAction *saveFile;              //保存图片
    QAction *exit;                  //退出

    void createMenu();


    QLabel *subImageLabel;             //显示图片的label控件
    QScrollArea *subScrollArea;        //中央控件
    QImage subImageToOperation;        //实际要处理的图片
    QImage backImage;                   //备份图片,用来判断图片是否需要保存
    bool noSave;                        //判断图片是否需要保存
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);     //窗口事件  函数
private slots:
    void saveImage();                   //保存图片 槽函数

    
};

#endif // SUBMAINWINDOW_H
