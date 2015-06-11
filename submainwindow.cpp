#include "submainwindow.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QImage>
#include<QPainter>
#include<QLabel>
#include<QScrollArea>
#include<QString>
#include<QFileDialog>
#include<QMessageBox>
#include<QPushButton>
subMainWindow::subMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createMenu();
    subImageLabel = new QLabel;
    subImageLabel->setBackgroundRole(QPalette::NoRole);
    subImageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    subImageLabel->setScaledContents(true); //ѡ���Զ���Ӧ��ı仯���������۽��Ի�����С�Ŵ󶼲�Ӱ�����أ������ڿ�ͼƬ��ʱ��ͼƬ�����ػ����������

    subScrollArea = new QScrollArea;       //��������
    subScrollArea->setBackgroundRole(QPalette::Dark);
    subScrollArea->setWidget(subImageLabel);

    backImage = QImage();


    setCentralWidget(subScrollArea);
    setWindowTitle(tr("������ͼƬ"));
    resize(600,500);
}


void subMainWindow::createMenu()
{
    menu = menuBar()->addMenu(tr("�˵�"));

    saveFile = new QAction(tr("����ͼƬ"),this);
    saveFile->setShortcut(QKeySequence::Save);
    connect(saveFile,SIGNAL(triggered()),this,SLOT(saveImage()));

    exit = new QAction(tr("�˳�"),this);
    exit->setShortcut(QKeySequence::Quit);
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));


    menu->addAction(saveFile);
    menu->addAction(exit);
    menu->addSeparator();

}

void subMainWindow::setImage(QImage image)
{
    this->subImageToOperation = image;
    backImage = image;
    noSave = true;              //����noSaveΪtrue��ͼƬû�б���
}


void subMainWindow::paintEvent(QPaintEvent *)
{
    subImageLabel->setPixmap(QPixmap::fromImage(subImageToOperation));
    subImageLabel->adjustSize();
}

void subMainWindow::saveImage()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("�����ļ�"),"",tr("(Images (*.png *.jpg)"));
    if(!filename.isNull())
    {
        QPixmap::fromImage(subImageToOperation).save(filename);
        noSave = false;                     //���ñ�־λΪfalse
    }
    else
    {
        return;
    }
}


void subMainWindow::closeEvent(QCloseEvent *)
{
    if(noSave)
    {
        QMessageBox saveWarnBox;
        saveWarnBox.setWindowTitle(tr("����"));
        QPushButton *save = saveWarnBox.addButton(tr("����"),QMessageBox::ActionRole);
        QPushButton *cancel = saveWarnBox.addButton(tr("������"),QMessageBox::ActionRole);
        saveWarnBox.setIconPixmap(tr(":/res/qt.ico"));
        saveWarnBox.setText(tr("�Ƿ񱣴�ͼƬ��"));

        saveWarnBox.exec();

        if(save == saveWarnBox.clickedButton())
        {
            saveImage();
        }
        if(cancel == saveWarnBox.clickedButton())
        {
            return;
        }
    }
}

























