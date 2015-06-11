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
    imageLabel->setScaledContents(true); //ѡ���Զ���Ӧ��ı仯���������۽��Ի�����С�Ŵ󶼲�Ӱ�����أ������ڿ�ͼƬ��ʱ��ͼƬ�����ػ����������

    scrollArea = new QScrollArea;       //��������
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
    openAction = new QAction(tr("���ļ�"),this);
    connect(openAction,SIGNAL(triggered()),this,SLOT(onOpenFile()));
    openAction->setShortcut(QKeySequence::New);

    rgb2Gray = new QAction(tr("ת���ɻҶ�ͼƬ"),this);
    connect(rgb2Gray,SIGNAL(triggered()),this,SLOT(onRgb2Gray()));
    rgb2Gray->setEnabled(false);
    exitAction = new QAction(tr("�˳�"),this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    histogramAction = new QAction(tr("�Ҷ�ֱ��ͼ"),this);
    connect(histogramAction,SIGNAL(triggered()),this,SLOT(onHistogramAction()));
    linerTransformAction = new QAction(tr("�Ҷȵ����Ա任"),this);
    connect(linerTransformAction,SIGNAL(triggered()),this,SLOT(onLinearTransform()));
    extendAction = new QAction(tr("�Ҷ�����"),this);
    connect(extendAction,SIGNAL(triggered()),this,SLOT(onGrayExtend()));
    equalAction = new QAction(tr("�ҶȾ���"),this);
    connect(equalAction,SIGNAL(triggered()),this,SLOT(onEqualAction()));
    thresholdAction = new QAction(tr("��ֵ�任"),this);
    connect(thresholdAction,SIGNAL(triggered()),this,SLOT(thresholdChangeAction()));

    translationAction = new QAction(tr("ͼ���ƽ�� "),this);
    connect(translationAction,SIGNAL(triggered()),this,SLOT(onTranslationAction()));
    hMirroredAction = new QAction(tr("ͼ���ˮƽ����任"),this);
    connect(hMirroredAction,SIGNAL(triggered()),this,SLOT(onHMirroredTran()));
    vMirroredAction = new QAction(tr("ͼ��Ĵ�ֱ����任"),this);
    connect(vMirroredAction,SIGNAL(triggered()),this,SLOT(onVMirroredTran()));
    transpositionAction = new QAction(tr("ͼ��ת��"),this);
    connect(transpositionAction,SIGNAL(triggered()),this,SLOT(onTranposition()));
    zoomAction = new QAction(tr("ͼ������"),this);
    connect(zoomAction,SIGNAL(triggered()),this,SLOT(onZoomImage()));


    smoothAction = new QAction(tr("ͼ��ƽ��"),this);
    connect(smoothAction,SIGNAL(triggered()),this,SLOT(onSmoothOperation()));
    middleFilterAction = new QAction(tr("��ֵ�˲�"),this);
    connect(middleFilterAction,SIGNAL(triggered()),this,SLOT(onMiddleFilterAction()));
    gradientSharpenAction = new QAction(tr("�ݶ���"),this);
    connect(gradientSharpenAction,SIGNAL(triggered()),this,SLOT(onGradientSharpen()));
    laplaceSharpenAction = new QAction(tr("������˹��"),this);
    connect(laplaceSharpenAction,SIGNAL(triggered()),this,SLOT(onLaplaceSharpen()));

    roberts = new QAction(tr("Roberts����"),this);
    connect(roberts,SIGNAL(triggered()),this,SLOT(onRobertsEdgeDect()));
    sobel = new QAction(tr("Sobel����"),this);
    connect(sobel,SIGNAL(triggered()),this,SLOT(onSobelEdgeDect()));
    prewitt = new QAction(tr("prewitt����"),this);
    connect(prewitt,SIGNAL(triggered()),this,SLOT(onPrewittEdgeDect()));
    krisch = new QAction(tr("krisch����"),this);
    connect(krisch,SIGNAL(triggered()),this,SLOT(onKrischEdgeDect()));
//    gaslap = new QAction(tr("��˹������˹����"),this);
//    connect(gaslap,SIGNAL(triggered()),this,SLOT(onGasLapEdgeDect()));
    aboutAuthorAction = new QAction(tr("����"),this);
    connect(aboutAuthorAction,SIGNAL(triggered()),this,SLOT(onAbout()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("�ļ�"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(rgb2Gray);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    pointOperatorMenu = menuBar()->addMenu(tr("ͼ������"));
    pointOperatorMenu->addAction(histogramAction);
    pointOperatorMenu->addAction(linerTransformAction);
    pointOperatorMenu->addAction(extendAction);
    pointOperatorMenu->addAction(equalAction);
    pointOperatorMenu->addAction(thresholdAction);

    geometryTansformMenu = menuBar()->addMenu(tr("���α任"));
    geometryTansformMenu->addAction(translationAction);
    subMirroredMenu = geometryTansformMenu->addMenu(tr("����任"));
    subMirroredMenu->addAction(hMirroredAction);
    subMirroredMenu->addAction(vMirroredAction);
    geometryTansformMenu->addAction(transpositionAction);
    geometryTansformMenu->addAction(zoomAction);
//    subZoomMenu = geometryTansformMenu->addMenu(tr("ͼ������"));
//    subZoomMenu->addAction(zoomInAction);
//    subZoomMenu->addAction(zoomOutAction);
//    geometryTansformMenu->addAction(rotateAction);

//    fourierTansformMenu = menuBar()->addMenu(tr("����Ҷ�任"));
//    fourierTansformMenu->addAction(fourierAction);

    imageEnhanceMenu = menuBar()->addMenu(tr("ͼ����ǿ"));
    imageEnhanceMenu->addAction(smoothAction);
    imageEnhanceMenu->addAction(middleFilterAction);
    subSharpenMenu = imageEnhanceMenu->addMenu(tr("ͼ����"));
    subSharpenMenu->addAction(gradientSharpenAction);
    subSharpenMenu->addAction(laplaceSharpenAction);

    edgeDetectMenu = menuBar()->addMenu(tr("��Ե���"));
//    edgeDetectMenu->addAction(edgeAction);
    edgeDetectMenu->addAction(roberts);
    edgeDetectMenu->addAction(sobel);
    edgeDetectMenu->addAction(krisch);
    edgeDetectMenu->addAction(prewitt);
//    edgeDetectMenu->addAction(gaslap);

    aboutMenu = menuBar()->addMenu(tr("����"));
    aboutMenu->addAction(aboutAuthorAction);
}


void MainWindow::paintEvent(QPaintEvent */*event*/)
{
    imageLabel->setPixmap(QPixmap::fromImage(imageToOperation));
    imageLabel->adjustSize();
}

void MainWindow::onOpenFile()
{
    QString loadFileName = QFileDialog::getOpenFileName(this, tr("��ͼƬ"),\
                                                     ".", tr("jpg�ļ�(*.jpg);;png�ļ�(*.png);;bmp�ļ�(*.bmp);;jpeg�ļ�(*.jpeg);;�����ļ�(*.*)"));

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
        QMessageBox::critical(NULL, tr("���ļ�����"), \
                             tr("���ļ�bmp��ʽ�ļ�,ʧ��!"));
        return;
    }
    setMenuEnabled(true);
    setWindowTitle(loadFileName);
    update();
}



void MainWindow::onAbout()
{
    QMessageBox authorBox;
    authorBox.setWindowTitle(tr("����ͼ����"));
    authorBox.addButton(tr("ȷ��"),QMessageBox::ActionRole);
    authorBox.setIconPixmap(QPixmap(":/res/res/qt.ico"));
    authorBox.setText(tr("����ͼ����ѧϰ���\n����:���Ż���а uestc\n����:huanglaoxie2607@gmail.com"));
    authorBox.exec();
}

//���ƻҶ�ֱ��ͼ
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


//ͼ��ƽ�� �˵���Ӧ����
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
        QMessageBox::critical(this,tr("��������"),tr("ƽ�Ʋ���������ͼƬ�ĳ��Ȼ��߿��"));
        return;
    }
    if(x < 0 || y < 0)
    {
        QMessageBox::critical(this,tr("��������"),tr("ƽ�Ʋ�������Ϊ����"));
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


//ͼ��ת�� ������
void MainWindow::onTranposition()
{
    //����ת�ú��ͼ��Ҳ���Ǹ�תְ���ͼ������ڴ�ռ�
    imageTransposition = new QImage(imageOperation.height(),imageOperation.width(),imageOperation.format());
    imageProcess.transpositionImage(imageToOperation.bits(),imageTransposition->bits());//ת�� ����
    showResult(*imageTransposition);
}


//�ݶ�����Ӧ����
void MainWindow::onGradientSharpen()
{
    imageProcess.gradientSharpen(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}

//������˹����Ӧ����
void MainWindow::onLaplaceSharpen()
{
    imageProcess.laplaceSharpen(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//��ʾͼ����������
void MainWindow::showResult(QImage image)
{
    subWindow->setImage(image);
    subWindow->update();
    subWindow->show();
    subWindow->raise();
}

//ͼ��ƽ�� ��Ӧ����
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


//��ֵ�˲� ��Ӧ����
void MainWindow::onMiddleFilterAction()
{
    imageProcess.middleValueFilter(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}

//Roberts���ӱ�Ե�����Ӧ����
void MainWindow::onRobertsEdgeDect()
{
    imageProcess.robertsEdgeDect(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//Sobel���ӱ�Ե�����Ӧ����
void MainWindow::onSobelEdgeDect()
{
    imageProcess.sobelEdgeDect(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//Prewitt���ӱ�Ե�����Ӧ����
void MainWindow::onPrewittEdgeDect()
{
    imageProcess.prewittEdgeDect(imageToOperation.bits(),imageOperation.bits());
    showResult(imageOperation);
}


//��˹������˹���ӱ�Ե�����Ӧ����
//void MainWindow::onGasLapEdgeDect()
//{
//    imageProcess.gaslapEdgeDect(imageToOperation.bits(),imageOperation.bits());
//    showResult(imageOperation);
//}


//RGB��ɫͼ��ת��Ϊ�Ҷ�ͼ����Ӧ����
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
        QMessageBox::warning(this,tr("����"),tr("ͼƬ�����Ѿ��ǻҶȵ���\nû�б�Ҫ��ת��"),QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
}


//krisch���ӱ�Ե�����Ӧ����
void MainWindow::onKrischEdgeDect()
{
    imageProcess.krischEdgeDect(imageOperation);
    showResult(imageOperation);
}

//�ҶȾ�����Ӧ����
void MainWindow::onEqualAction()
{
    imageProcess.countOfEachPixel(imageToOperation.bits(),grayCount);
    imageProcess.equal(imageToOperation.bits(),imageOperation.bits(),grayCount);
    showResult(imageOperation);
}



//��ֵ�任��Ӧ����
void MainWindow::thresholdChangeAction()
{
    if(thresholdSetDialog->isHidden())
    {
        thresholdSetDialog->show();
        thresholdSetDialog->raise();
    }
}



//��ȡ����ֵ��ʵ�ʽ���ͼ����ĺ���
void MainWindow::getThresholdAndProcess(int value)
{
//    threshold = value;
    imageProcess.thresholdChange(imageToOperation.bits(),imageOperation.bits(),value);
    showResult(imageOperation);
}


//�Ҷȵ����Ա任��Ӧ����
void MainWindow::onLinearTransform()
{
    if(linerTransformDilaog->isHidden())
    {
        linerTransformDilaog->show();
        linerTransformDilaog->raise();
    }
}

//��ȡ���Ա任������ʵ�ʽ���ͼ����ĺ���
void MainWindow::getLinerTransformParamerAndProcess(int gradient, int intercept)
{
    imageProcess.linearTransform(imageToOperation.bits(),imageOperation.bits(),gradient,intercept);
    showResult(imageOperation);
}

//�Ҷȵ�������Ӧ����
void MainWindow::onGrayExtend()
{
    if(graySettingDialog->isHidden())
    {
        graySettingDialog->show();
        graySettingDialog->raise();
    }
}


//��ȡ����ֵ��ʵ�ʽ���ͼ��Ҷ����촦��ĺ���
void MainWindow::getCoorsAndProcess(int coor1_x, int coor1_y, int coor2_x, int coor2_y)
{
    imageProcess.grayExtend(imageToOperation.bits(),imageOperation.bits(),coor1_x,coor1_y,coor2_x,coor2_y);
    showResult(imageOperation);
}


//ͼ��������Ӧ����
void MainWindow::onZoomImage()
{
    if(dialogOfZoom->isHidden())
    {
        dialogOfZoom->show();
        dialogOfZoom->raise();
    }
}


//��ȡ���Ų�������ʵ�ʽ���ͼ����ĺ���
void MainWindow::getScaleAndProcess(float scale)
{
    zoomImage = QImage(imageOperation.width() * scale,imageOperation.height() * scale,imageOperation.format());
    imageProcess.zoomImage(imageToOperation,zoomImage,scale,scale);
    showResult(zoomImage);
}

