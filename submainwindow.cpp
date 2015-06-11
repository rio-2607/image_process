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
    subImageLabel->setScaledContents(true); //选择自动适应框的变化，就是无论将对话框，缩小放大都不影响像素，作用在看图片的时候，图片的像素会跟着相框调整

    subScrollArea = new QScrollArea;       //滚动区域
    subScrollArea->setBackgroundRole(QPalette::Dark);
    subScrollArea->setWidget(subImageLabel);

    backImage = QImage();


    setCentralWidget(subScrollArea);
    setWindowTitle(tr("处理后的图片"));
    resize(600,500);
}


void subMainWindow::createMenu()
{
    menu = menuBar()->addMenu(tr("菜单"));

    saveFile = new QAction(tr("保存图片"),this);
    saveFile->setShortcut(QKeySequence::Save);
    connect(saveFile,SIGNAL(triggered()),this,SLOT(saveImage()));

    exit = new QAction(tr("退出"),this);
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
    noSave = true;              //设置noSave为true，图片没有保存
}


void subMainWindow::paintEvent(QPaintEvent *)
{
    subImageLabel->setPixmap(QPixmap::fromImage(subImageToOperation));
    subImageLabel->adjustSize();
}

void subMainWindow::saveImage()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("保存文件"),"",tr("(Images (*.png *.jpg)"));
    if(!filename.isNull())
    {
        QPixmap::fromImage(subImageToOperation).save(filename);
        noSave = false;                     //设置标志位为false
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
        saveWarnBox.setWindowTitle(tr("警告"));
        QPushButton *save = saveWarnBox.addButton(tr("保存"),QMessageBox::ActionRole);
        QPushButton *cancel = saveWarnBox.addButton(tr("不保存"),QMessageBox::ActionRole);
        saveWarnBox.setIconPixmap(tr(":/res/qt.ico"));
        saveWarnBox.setText(tr("是否保存图片？"));

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

























