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


    QMenu *fileMenu;                            //���ļ����˵�
    QMenu *pointOperatorMenu;                   //��ͼ���������˵�
    QMenu *geometryTansformMenu;                //�����α任���˵�
//    QMenu *fourierTansformMenu;                 //������Ҷ�任���˵�
    QMenu *imageEnhanceMenu;                    //��ͼ����ǿ���˵�
    QMenu *edgeDetectMenu;                      //����Ե�����˵�
    QMenu *aboutMenu;                           //�����ڡ��˵�
//    QMenu *subZoomMenu;                         //�����˵� ���� �˵�
    QMenu *subSharpenMenu;                      //�����˵� ͼ����
    QMenu *subMirroredMenu;                     //ͼ����任�Ӳ˵�

    QAction *openAction;                        //���ļ�
    QAction *rgb2Gray;                          //��ɫͼƬת���ɻҶ�ͼƬ
//    QAction *saveAction;                        //�������
    QAction *exitAction;                        //�˳�

    QAction *histogramAction;                   //�Ҷ�ֱ��ͼ
    QAction *linerTransformAction;              //�Ҷȵ����Ա任
    QAction *extendAction;                      //�Ҷ�����
    QAction *equalAction;                       //�ҶȾ���
    QAction *thresholdAction;                   //��ֵ�任

//    QAction *fourierAction;                     //����Ҷ�任

    QAction *translationAction;                 //ͼ���ƽ��
    QAction *hMirroredAction;                   //ͼ���ˮƽ����任
    QAction *vMirroredAction;                   //ͼ��Ĵ�ֱ����任
    QAction *transpositionAction;               //ͼ���ת��
//    QAction *zoomInAction;                      //ͼ����С
//    QAction *zoomOutAction;                     //ͼ��Ŵ�
//    QAction *rotateAction;                      //ͼ�����ת
    QAction *zoomAction;                          //ͼ������

//    QAction *maskOperationAction;               //ģ�����
    QAction *smoothAction;                      //ͼ���ƽ��
    QAction *middleFilterAction;                //��ֵ�˲�
    QAction *gradientSharpenAction;             //ͼ�����:�ݶ���
    QAction *laplaceSharpenAction;              //ͼ���񻯣�������˹��

     QAction *roberts;                          //roberts���ӱ�Ե���
     QAction *sobel;                            //sobel���ӱ�Ե���
     QAction *prewitt;                          //prewitt���ӱ�Ե���
     QAction *krisch;                           //krisch���ӱ�Ե���
//     QAction *gaslap;

    QAction *aboutAuthorAction;                 //����

    void createMenus();                          //���ɲ���
    void createActions();                       //���ɲ˵�

    QLabel *imageLabel;                         //��ʾͼƬ�ؼ�
    QScrollArea *scrollArea;                    //���ؼ�
    //QPixmap imageToOperation;
    QImage imageToOperation;                    //��Ҫ�����ͼƬ
    QImage imageOperation;                      //ʵ�ʲ�����ͼƬ
    QImage *imageTransposition;                 //ת�ú��ͼƬ
    QImage grayImage;                           //����ת����ĻҶ�ͼƬ
    QImage zoomImage;                           //�������ź��ͼƬ
    drawHistogram *drawHisWindow;               //���ƻҶ�ֱ��ͼ
    subMainWindow *subWindow;                   //��ʾ������ͼƬ�Ĵ���
    parameterDialog *paraDialog;                //����ƽ�Ʋ����Ի���
    templateSetting *templateDialog;            //ģ�����öԻ���
    setThreshold *thresholdSetDialog;           //��ֵ���öԻ���
    linerTransformSettingDialog *linerTransformDilaog;          //���Ա任�������öԻ���
    grayExtendDialog *graySettingDialog;        //�Ҷ��������öԻ���
    zoomDialog *dialogOfZoom;                    //���Ų������öԻ���
//    int templateSelect;                         //����ѡ�е�ģ��
//    int threshold;                              //���õ���ֵ
    int xOffset;                                //ˮƽƽ�Ʋ���
    int yOffset;                                //��ֱƽ�Ʋ���
protected:
    void paintEvent(QPaintEvent * /*event*/);
protected slots:
    void onOpenFile();                          //�򿪲˵� ��Ӧ����
    void onAbout();                             //���ڲ˵� ��Ӧ����
    void onHistogramAction();                   //�Ҷ�ֱ��ͼ ��Ӧ����
    void thresholdChangeAction();               //��ֵ�任 ��Ӧ����
    void onTranslationAction();                 //ͼ��ƽ�� ��Ӧ����
    void onHMirroredTran();                     //ͼ��ˮƽ����任 ��Ӧ����
    void onVMirroredTran();                     //ͼ��ֱ����任 ��Ӧ����
    void onTranposition();                      //ͼ��ת�� ��Ӧ����
    void onGradientSharpen();                   //�ݶ��� ��Ӧ����
    void onLaplaceSharpen();                    //������˹�� ��Ӧ����
    void onSmoothOperation();                   //ͼ��ƽ�� ��Ӧ����
    void onMiddleFilterAction();                //��ֵ�˲� ��Ӧ����
    void onRobertsEdgeDect();                   //Roberts���ӱ�Ե��� ��Ӧ����
    void onSobelEdgeDect();                     //Sobel���ӱ�Ե��� ��Ӧ����
    void onPrewittEdgeDect();                   //Prewitt���ӱ�Ե��� ��Ӧ����
//    void onGasLapEdgeDect();                    //��˹������˹���ӱ�Ե��� ��Ӧ����
    void onRgb2Gray();                          //ת���ɻҶ�ͼƬ ��Ӧ����
    void onKrischEdgeDect();                    //Krisch���ӱ�Ե��� ��Ӧ����
    void onEqualAction();                       //ͼ����⻯ ��Ӧ����
    void onLinearTransform();                   //�Ҷȵ����Ա任 ��Ӧ����
    void onGrayExtend();                        //�Ҷ����� ��Ӧ����
    void onZoomImage();                         //����ͼƬ ��Ӧ����
private slots:
    void getParameterAndProcess(int x,int y);   //��ȡƽ�Ʋ��������д���
    void getTemplateSelectAndProcess(int select);                //��ȡ�û�ѡ���ģ�岢���д���
    void getThresholdAndProcess(int value);               //��ȡ���õ���ֵ�����д���
    //��ȡ���õ����Ա任���������д���
    void getLinerTransformParamerAndProcess(int gradient,int intercept);
    //��ȡ�Ҷ�����Ĳ���������ʵ�ʵ�ͼ����
    void getCoorsAndProcess(int coor1_x,int coor1_y,int coor2_x,int coor2_y);
    void getScaleAndProcess(float scale);

private:
    LONG grayCount[256];                        //����Ҷ�ֵ
    ImageProcessing imageProcess;               //ͼ������
    void setMenuEnabled(bool enable);           //ʹ�ܲ˵�
private:
    void showResult(QImage image);              //��ʾ������

};

#endif // MAINWINDOW_H


