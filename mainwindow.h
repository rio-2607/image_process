#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QMenu;
class QAction;
class QLabel;
class QScrollArea;
class QImage;
class QPixmap;
#include"imageprocessing.h"
//#include"ImageProcessing/imageprocessing.h"
#include"drawhistogram.h"
//#include"drawHistogram/drawhistogram.h"
#include"submainwindow.h"
//#include"subMainWindow/submainwindow.h"
#include"parameterdialog.h"
//#include"parameterDialog/parameterdialog.h"
#include"templatesetting.h"
#include"setthreshold.h"
#include"linertransformsettingdialog.h"
#include"grayextenddialog.h"
#include"zoomdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;


    QMenu *fileMenu;                            //“文件”菜单
    QMenu *pointOperatorMenu;                   //“图像点操作”菜单
    QMenu *geometryTansformMenu;                //“几何变换”菜单
//    QMenu *fourierTansformMenu;                 //“傅里叶变换”菜单
    QMenu *imageEnhanceMenu;                    //“图像增强”菜单
    QMenu *edgeDetectMenu;                      //“边缘”检测菜单
    QMenu *aboutMenu;                           //“关于”菜单
//    QMenu *subZoomMenu;                         //二级菜单 缩放 菜单
    QMenu *subSharpenMenu;                      //二级菜单 图像锐化
    QMenu *subMirroredMenu;                     //图像镜像变换子菜单

    QAction *openAction;                        //打开文件
    QAction *rgb2Gray;                          //彩色图片转换成灰度图片
//    QAction *saveAction;                        //保存操作
    QAction *exitAction;                        //退出

    QAction *histogramAction;                   //灰度直方图
    QAction *linerTransformAction;              //灰度的线性变换
    QAction *extendAction;                      //灰度拉伸
    QAction *equalAction;                       //灰度均衡
    QAction *thresholdAction;                   //阈值变换

//    QAction *fourierAction;                     //傅里叶变换

    QAction *translationAction;                 //图像的平移
    QAction *hMirroredAction;                   //图像的水平镜像变换
    QAction *vMirroredAction;                   //图像的垂直镜像变换
    QAction *transpositionAction;               //图像的转置
//    QAction *zoomInAction;                      //图像缩小
//    QAction *zoomOutAction;                     //图像放大
//    QAction *rotateAction;                      //图像的旋转
    QAction *zoomAction;                          //图像缩放

//    QAction *maskOperationAction;               //模板操作
    QAction *smoothAction;                      //图像的平滑
    QAction *middleFilterAction;                //中值滤波
    QAction *gradientSharpenAction;             //图像的锐化:梯度锐化
    QAction *laplaceSharpenAction;              //图像锐化：拉普拉斯锐化

     QAction *roberts;                          //roberts算子边缘检测
     QAction *sobel;                            //sobel算子边缘检查
     QAction *prewitt;                          //prewitt算子边缘检测
     QAction *krisch;                           //krisch算子边缘检测
//     QAction *gaslap;

    QAction *aboutAuthorAction;                 //关于

    void createMenus();                          //生成操作
    void createActions();                       //生成菜单

    QLabel *imageLabel;                         //显示图片控件
    QScrollArea *scrollArea;                    //主控件
    //QPixmap imageToOperation;
    QImage imageToOperation;                    //想要处理的图片
    QImage imageOperation;                      //实际操作的图片
    QImage *imageTransposition;                 //转置后的图片
    QImage grayImage;                           //保存转换后的灰度图片
    QImage zoomImage;                           //保存缩放后的图片
    drawHistogram *drawHisWindow;               //绘制灰度直方图
    subMainWindow *subWindow;                   //显示处理后的图片的窗口
    parameterDialog *paraDialog;                //设置平移参数对话框
    templateSetting *templateDialog;            //模板设置对话框
    setThreshold *thresholdSetDialog;           //阈值设置对话框
    linerTransformSettingDialog *linerTransformDilaog;          //线性变换参数设置对话框
    grayExtendDialog *graySettingDialog;        //灰度拉伸设置对话框
    zoomDialog *dialogOfZoom;                    //缩放参数设置对话框
//    int templateSelect;                         //保存选中的模板
//    int threshold;                              //设置的阈值
    int xOffset;                                //水平平移参量
    int yOffset;                                //垂直平移参量
protected:
    void paintEvent(QPaintEvent * /*event*/);
protected slots:
    void onOpenFile();                          //打开菜单 响应函数
    void onAbout();                             //关于菜单 响应函数
    void onHistogramAction();                   //灰度直方图 响应函数
    void thresholdChangeAction();               //阈值变换 响应函数
    void onTranslationAction();                 //图像平移 响应函数
    void onHMirroredTran();                     //图像水平镜像变换 响应函数
    void onVMirroredTran();                     //图像垂直镜像变换 响应函数
    void onTranposition();                      //图像转置 响应函数
    void onGradientSharpen();                   //梯度锐化 响应函数
    void onLaplaceSharpen();                    //拉普拉斯锐化 响应函数
    void onSmoothOperation();                   //图像平滑 响应函数
    void onMiddleFilterAction();                //中值滤波 响应函数
    void onRobertsEdgeDect();                   //Roberts算子边缘检测 响应函数
    void onSobelEdgeDect();                     //Sobel算子边缘检测 响应函数
    void onPrewittEdgeDect();                   //Prewitt算子边缘检测 响应函数
//    void onGasLapEdgeDect();                    //高斯拉普拉斯算子边缘检测 响应函数
    void onRgb2Gray();                          //转换成灰度图片 响应函数
    void onKrischEdgeDect();                    //Krisch算子边缘检测 响应函数
    void onEqualAction();                       //图像均衡化 响应函数
    void onLinearTransform();                   //灰度的线性变换 响应函数
    void onGrayExtend();                        //灰度拉伸 响应函数
    void onZoomImage();                         //缩放图片 响应函数
private slots:
    void getParameterAndProcess(int x,int y);   //获取平移参量并进行处理
    void getTemplateSelectAndProcess(int select);                //获取用户选择的模板并进行处理
    void getThresholdAndProcess(int value);               //获取设置的阈值并进行处理
    //获取设置的线性变换参数并进行处理
    void getLinerTransformParamerAndProcess(int gradient,int intercept);
    //获取灰度拉伸的参数并进行实际的图像处理
    void getCoorsAndProcess(int coor1_x,int coor1_y,int coor2_x,int coor2_y);
    void getScaleAndProcess(float scale);

private:
    LONG grayCount[256];                        //保存灰度值
    ImageProcessing imageProcess;               //图像处理类
    void setMenuEnabled(bool enable);           //使能菜单
private:
    void showResult(QImage image);              //显示处理结果

};

#endif // MAINWINDOW_H


