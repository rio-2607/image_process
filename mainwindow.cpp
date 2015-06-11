#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenu>
#include<QAction>
#include<QPixmap>
#include<QLabel>
#include<QScrollArea>
#include<QImage>
#include<QPainter>
#include<QPaintEvent>
#include<QPixmap>
#include<QFileDialog>
#include<QMessageBox>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::NoRole);
    imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    imageLabel->setScaledContents(true); //选择自动适应框的变化，就是无论将对话框，缩小放大都不影响像素，作用在看图片的时候，图片的像素会跟着相框调整

    scrollArea = new QScrollArea;       //滚动区域
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);


    setCentralWidget(scrollArea);
    createActions();
    createMenus();
    resize(600,500);
    setWindowTitle(tr("Digital Image Processing"));

    setMenuEnabled(false);




//    for(int i=0;i<256;i++)
//        grayCount[i] = 0;
    drawHisWindow = new drawHistogram(this);
    subWindow = new subMainWindow(this);

    xOffset = 0;
    yOffset = 0;
    paraDialog = new parameterDialog(this);
    connect(paraDialog,SIGNAL(sendParameter(int,int)),this,SLOT(getParameterAndProcess(int,int)));
    templateDialog = new templateSetting(this);
    connect(templateDialog,SIGNAL(sendSelect(int)),this,SLOT(getTemplateSelectAndProcess(int)));
    thresholdSetDialog = new setThreshold(this);
    connect(thresholdSetDialog,SIGNAL(sendThreshold(int)),this,SLOT(getThresholdAndProcess(int)));
    linerTransformDilaog = new linerTransformSettingDialog(this);
    connect(linerTransformDilaog,SIGNAL(sendParamer(int,int)),\
            this,SLOT(getLinerTransformParamerAndProcess(int,int)));
    graySettingDialog = new grayExtendDialog(this);
    connect(graySettingDialog,SIGNAL(sendParamer(int,int,int,int)),this,SLOT(getCoorsAndProcess(int,int,int,int)));
    dialogOfZoom = new zoomDialog(this);
    connect(dialogOfZoom,SIGNAL(sendParamer(float)),this,SLOT(getScaleAndProcess(float)));
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("打开文件"),this);
    connect(openAction,SIGNAL(triggered()),this,SLOT(onOpenFile()));
    openAction->setShortcut(QKeySequence::New);

    rgb2Gray = new QAction(tr("转换成灰度图片"),this);
    connect(rgb2Gray,SIGNAL(triggered()),this,SLOT(onRgb2Gray()));
    rgb2Gray->setEnabled(false);
    exitAction = new QAction(tr("退出"),this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    histogramAction = new QAction(tr("灰度直方图"),this);
    connect(histogramAction,SIGNAL(triggered()),this,SLOT(onHistogramAction()));
    linerTransformAction = new QAction(tr("灰度的线性变换"),this);
    connect(linerTransformAction,SIGNAL(triggered()),this,SLOT(onLinearTransform()));
    extendAction = new QAction(tr("灰度拉伸"),this);
    connect(extendAction,SIGNAL(triggered()),this,SLOT(onGrayExtend()));
    equalAction = new QAction(tr("灰度均衡"),this);
    connect(equalAction,SIGNAL(triggered()),this,SLOT(onEqualAction()));
    thresholdAction = new QAction(tr("阈值变换"),this);
    connect(thresholdAction,SIGNAL(triggered()),this,SLOT(thresholdChangeAction()));

    translationAction = new QAction(tr("图像的平移 "),this);
    connect(translationAction,SIGNAL(triggered()),this,SLOT(onTranslationAction()));
    hMirroredAction = new QAction(tr("图像的水平镜像变换"),this);
    connect(hMirroredAction,SIGNAL(triggered()),this,SLOT(onHMirroredTran()));
    vMirroredAction = new QAction(tr("图像的垂直镜像变换"),this);
    connect(vMirroredAction,SIGNAL(triggered()),this,SLOT(onVMirroredTran()));
    transpositionAction = new QAction(tr("图像转置"),this);
    connect(transpositionAction,SIGNAL(triggered()),this,SLOT(onTranposition()));
    zoomAction = new QAction(tr("图像缩放"),this);
    connect(zoomAction,SIGNAL(triggered()),this,SLOT(onZoomImage()));


    smoothAction = new QAction(tr("图像平滑"),this);
    connect(smoothAction,SIGNAL(triggered()),this,SLOT(onSmoothOperation()));
    middleFilterAction = new QAction(tr("中值滤波"),this);
    connect(middleFilterAction,SIGNAL(triggered()),this,SLOT(onMiddleFilterAction()));
    gradientSharpenAction = new QAction(tr("梯度锐化"),this);
    connect(gradientSharpenAction,SIGNAL(triggered()),this,SLOT(onGradientSharpen()));
    laplaceSharpenAction = new QAction(tr("拉普拉斯锐化"),this);
    connect(laplaceSharpenAction,SIGNAL(triggered()),this,SLOT(onLaplaceSharpen()));

    roberts = new QAction(tr("Roberts算子"),this);
    connect(roberts,SIGNAL(triggered()),this,SLOT(onRobertsEdgeDect()));
    sobel = new QAction(tr("Sobel算子"),this);
    connect(sobel,SIGNAL(triggered()),this,SLOT(onSobelEdgeDect()));
    prewitt = new QAction(tr("prewitt算子"),this);
    connect(prewitt,SIGNAL(triggered()),this,SLOT(onPrewittEdgeDect()));
    krisch = new QAction(tr("krisch算子"),this);
    connect(krisch,SIGNAL(triggered()),this,SLOT(onKrischEdgeDect()));
//    gaslap = new QAction(tr("高斯拉普拉斯算子"),this);
//    connect(gaslap,SIGNAL(triggered()),this,SLOT(onGasLapEdgeDect()));
    aboutAuthorAction = new QAction(tr("作者"),this);
    connect(aboutAuthorAction,SIGNAL(triggered()),this,SLOT(onAbout()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(rgb2Gray);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    pointOperatorMenu = menuBar()->addMenu(tr("图像点操作"));
    pointOperatorMenu->addAction(histogramAction);
    pointOperatorMenu->addAction(linerTransformAction);
    pointOperatorMenu->addAction(extendAction);
    pointOperatorMenu->addAction(equalAction);
    pointOperatorMenu->addAction(thresholdAction);

    geometryTansformMenu = menuBar()->addMenu(tr("几何变换"));
    geometryTansformMenu->addAction(translationAction);
    subMirroredMenu = geometryTansformMenu->addMenu(tr("镜像变换"));
    subMirroredMenu->addAction(hMirroredAction);
    subMirroredMenu->addAction(vMirroredAction);
    geometryTansformMenu->addAction(transpositionAction);
    geometryTansformMenu->addAction(zoomAction);
//    subZoomMenu = geometryTansformMenu->addMenu(tr("图像缩放"));
//    subZoomMenu->addAction(zoomInAction);
//    subZoomMenu->addAction(zoomOutAction);
//    geometryTansformMenu->addAction(rotateAction);

//    fourierTansformMenu = menuBar()->addMenu(tr("傅里叶变换"));
//    fourierTansformMenu->addAction(fourierAction);

    imageEnhanceMenu = menuBar()->addMenu(tr("图像增强"));
    imageEnhanceMenu->addAction(smoothAction);
    imageEnhanceMenu->addAction(middleFilterAction);
    subSharpenMenu = imageEnhanceMenu->addMenu(tr("图像锐化"));
    subSharpenMenu->addAction(gradientSharpenAction);
    subSharpenMenu->addAction(laplaceSharpenAction);

    edgeDetectMenu = menuBar()->addMenu(tr("边缘检测"));
//    edgeDetectMenu->addAction(edgeAction);
    edgeDetectMenu->addAction(roberts);
    edgeDetectMenu->addAction(sobel);
    edgeDetectMenu->addAction(krisch);
    edgeDetectMenu->addAction(prewitt);
//    edgeDetectMenu->addAction(gaslap);

    aboutMenu = menuBar()->addMenu(tr("关于"));
    aboutMenu->addAction(aboutAuthorAction);
}


void MainWindow::paintEvent(QPaintEvent */*event*/)
{
    imageLabel->setPixmap(QPixmap::fromImage(imageToOperation));
    imageLabel->adjustSize();
}

void MainWindow::onOpenFile()
{
    QString loadFileName = QFileDialog::getOpenFileName(this, tr("打开图片"),\
                                                     ".", tr("jpg文件(*.jpg);;png文件(*.png);;bmp文件(*.bmp);;jpeg文件(*.jpeg);;所有文件(*.*)"));

    if( loadFileName.isEmpty() )
    {
        return;
    }



    imageToOperation.load(loadFileName);
    imageOperation = imageToOperation;
    imageProcess.getImageInfo(imageToOperation);
    rgb2Gray->setEnabled(true);
    if (!imageToOperation.load(loadFileName))
    {
        QMessageBox::critical(NULL, tr("打开文件错误"), \
                             tr("打开文件bmp格式文件,失败!"));
        return;
    }
    setMenuEnabled(true);
    setWindowTitle(loadFileName);
    update();
}



void MainWindow::onAbout()
{
    QMessageBox authorBox;
    authorBox.setWindowTitle(tr("数字图像处理"));
    authorBox.addButton(tr("确定"),QMessageBox::ActionRole);
    authorBox.setIconPixmap(QPixmap(":/res/res/qt.ico"));
    authorBox.setText(tr("数字图像处理学习软件\n作者:唐门黄老邪 uestc\n邮箱:huanglaoxie2607@gmail.com"));
    authorBox.exec();
}

//绘制灰度直方图
void MainWindow::onHistogramAction()
{
    imageProcess.countOfEachPixel(imageToOperation.bits(),grayCount);
    drawHisWindow->setData(grayCount);
    if(drawHisWindow->isHidden())
    {
        drawHisWindow->show();
        drawHisWindow->update();
    }
    else
    {
        drawHisWindow->raise();
        drawHisWindow->activateWindow();
        drawHisWindow->update();
    }
}


//图像平移 菜单响应函数
void MainWindow::onTranslationAction()
{
    if(paraDialog->isHidden())
        paraDialog->exec();
}


void MainWindow::getParameterAndProcess(int x, int y)
{
    xOffset = x;
    yOffset = y;
    if(x > imageOperation.width() || y > imageOperation.height())
    {
        QMessageBox::critical(this,tr("参数错误"),tr("平移参数超过了图片的长度或者宽度"));
        return;
    }
    if(x < 0 || y < 0)
    {
        QMessageBox::critical(this,tr("参数错误"),tr("平移参量不能为负数"));
        return;
    }
    imageProcess.translationImage(imageToOperation.bits(),imageOperation.bits(),xOffset,yOffset);
    subWindow->setImage(imageOperation);
    subWindow->show();
}


void MainWindow::setMenuEnabled(bool enable)
{
    pointOperatorMenu->setEnabled(enable);
    geometryTansformMenu->setEnabled(enable);
//    fourierTansformMenu->setEnabled(enable);
    imageEnhanceMenu->setEnabled(enable);
    edgeDetectMenu->setEnabled(enable);
//    subZoomMenu->setEnabled(enable);
    subSharpenMenu->setEnabled(enable);
}


void MainWindow::onHMirroredTran()
{
    imageProcess.miirroredTran(imageToOperation.bits(),imageOperation.bits(),true);
    showResult(imageOperation);
}

void MainWindow::onVMirroredTran()
{
    imageProcess.miirroredTran(imageToOperation.bits(),imageOperation.bits(),false);
    showResult(imageOperation);
}


//图像转置 处理函数
void MainWindow::onTranposition()
{
    //生成转置后的图像，也就是给转职后的图像分配内存空间
    imageTransposition = new QImage(imageOperation.height(),imageOperation.width(),imageOperation.format());
    imageProcess.transpositionImage(imageToOperation.bits(),imageTransposition->bits());//转置 处理
    showResult(*imageTransposition);
}


//梯度锐化响应函数
void MainWindow::onGradientSharpen()
{
    imageProcess.gradientSharpen(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}

//拉普拉斯锐化响应函数
void MainWindow::onLaplaceSharpen()
{
    imageProcess.laplaceSharpen(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//显示图像处理结果函数
void MainWindow::showResult(QImage image)
{
    subWindow->setImage(image);
    subWindow->update();
    subWindow->show();
    subWindow->raise();
}

//图像平滑 响应函数
void MainWindow::onSmoothOperation()
{
    if(templateDialog->isHidden())
    {
        templateDialog->show();
    }
}


void MainWindow::getTemplateSelectAndProcess(int select)
{
    float cof;
    int mask_[9];
    if(1 == select)
    {
        for(int i = 0;i < 9;i++)
            mask_[i] = 1;
        cof = 1.0 / 9.0;
    }

    if(2 == select)
    {
        mask_[0] = 1;
        mask_[1] = 2;
        mask_[2] = 1;
        mask_[3] = 2;
        mask_[4] = 4;
        mask_[5] = 2;
        mask_[6] = 1;
        mask_[7] = 2;
        mask_[8] = 1;
        cof = 1.0 / 16.0;
    }


    if(3 == select)
    {
        mask_[0] = 0;
        mask_[1] = 1;
        mask_[2] = 0;
        mask_[3] = 1;
        mask_[4] = 1;
        mask_[5] = 1;
        mask_[6] = 0;
        mask_[7] = 1;
        mask_[8] = 0;
        cof = 1.0 / 4.0;
    }
    if(4 == select)
    {
        mask_[0] = 1;
        mask_[1] = 1;
        mask_[2] = 1;
        mask_[3] = 1;
        mask_[4] = 0;
        mask_[5] = 1;
        mask_[6] = 1;
        mask_[7] = 1;
        mask_[8] = 1;
        cof = 1.0 / 8.0;
    }
    if(5 == select)
    {
        mask_[0] = 1;
        mask_[1] = 1;
        mask_[2] = 1;
        mask_[3] = 1;
        mask_[4] = 2;
        mask_[5] = 1;
        mask_[6] = 1;
        mask_[7] = 1;
        mask_[8] = 1;
        cof = 1.0 / 10.0;
    }
    imageProcess.templateOperation(imageToOperation.bits(),imageOperation.bits(),mask_,cof);
    showResult(imageOperation);
}


//中值滤波 响应函数
void MainWindow::onMiddleFilterAction()
{
    imageProcess.middleValueFilter(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}

//Roberts算子边缘检测响应函数
void MainWindow::onRobertsEdgeDect()
{
    imageProcess.robertsEdgeDect(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//Sobel算子边缘检测响应函数
void MainWindow::onSobelEdgeDect()
{
    imageProcess.sobelEdgeDect(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//Prewitt算子边缘检测响应函数
void MainWindow::onPrewittEdgeDect()
{
    imageProcess.prewittEdgeDect(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//高斯拉普拉斯算子边缘检测响应函数
//void MainWindow::onGasLapEdgeDect()
//{
//    imageProcess.gaslapEdgeDect(imageToOperation.bits(),imageOperation.bits());
//    showResult(imageOperation);
//}


//RGB彩色图像转换为灰度图像响应函数
void MainWindow::onRgb2Gray()
{
    if(32 == imageToOperation.depth())
    {
        grayImage = QImage(imageToOperation.width(),imageToOperation.height(),QImage::Format_Indexed8);
        imageProcess.rgbToGray(imageToOperation,grayImage);
        showResult(grayImage);
    }
    if(8 == imageToOperation.depth())
    {
        QMessageBox::warning(this,tr("提醒"),tr("图片本身已经是灰度的了\n没有必要再转换"),QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
}


//krisch算子边缘检测响应函数
void MainWindow::onKrischEdgeDect()
{
    imageProcess.krischEdgeDect(imageOperation);
    showResult(imageOperation);
}

//灰度均衡响应函数
void MainWindow::onEqualAction()
{
    imageProcess.countOfEachPixel(imageToOperation.bits(),grayCount);
    imageProcess.equal(imageToOperation.bits(),imageOperation.bits(),grayCount);
    showResult(imageOperation);
}



//阈值变换响应函数
void MainWindow::thresholdChangeAction()
{
    if(thresholdSetDialog->isHidden())
    {
        thresholdSetDialog->show();
        thresholdSetDialog->raise();
    }
}



//获取到阈值后实际进行图像处理的函数
void MainWindow::getThresholdAndProcess(int value)
{
//    threshold = value;
    imageProcess.thresholdChange(imageToOperation.bits(),imageOperation.bits(),value);
    showResult(imageOperation);
}


//灰度的线性变换响应函数
void MainWindow::onLinearTransform()
{
    if(linerTransformDilaog->isHidden())
    {
        linerTransformDilaog->show();
        linerTransformDilaog->raise();
    }
}

//获取线性变换参数后实际进行图像处理的函数
void MainWindow::getLinerTransformParamerAndProcess(int gradient, int intercept)
{
    imageProcess.linearTransform(imageToOperation.bits(),imageOperation.bits(),gradient,intercept);
    showResult(imageOperation);
}

//灰度的拉伸响应函数
void MainWindow::onGrayExtend()
{
    if(graySettingDialog->isHidden())
    {
        graySettingDialog->show();
        graySettingDialog->raise();
    }
}


//获取坐标值后实际进行图像灰度拉伸处理的函数
void MainWindow::getCoorsAndProcess(int coor1_x, int coor1_y, int coor2_x, int coor2_y)
{
    imageProcess.grayExtend(imageToOperation.bits(),imageOperation.bits(),coor1_x,coor1_y,coor2_x,coor2_y);
    showResult(imageOperation);
}


//图像缩放响应函数
void MainWindow::onZoomImage()
{
    if(dialogOfZoom->isHidden())
    {
        dialogOfZoom->show();
        dialogOfZoom->raise();
    }
}


//获取缩放参数并且实际进行图像处理的函数
void MainWindow::getScaleAndProcess(float scale)
{
    zoomImage = QImage(imageOperation.width() * scale,imageOperation.height() * scale,imageOperation.format());
    imageProcess.zoomImage(imageToOperation,zoomImage,scale,scale);
    showResult(zoomImage);
}

