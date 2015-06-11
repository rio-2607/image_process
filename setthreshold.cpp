#include "setthreshold.h"
#include "ui_setthreshold.h"
#include<QDebug>
#include<QMessageBox>

setThreshold::setThreshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setThreshold)
{
    ui->setupUi(this);
    setWindowTitle(tr("��ֵ��������"));
    setFixedSize(155,180);

    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(onOkButton()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButton()));
}

setThreshold::~setThreshold()
{
    delete ui;
}

void setThreshold::onOkButton()
{
    int value = ui->thresholdValue->text().toInt();

    if(value < 0 || value > 255)
    {
        QMessageBox::warning(this,tr("��������"),tr("����Ĳ���������Ҫ��\n����Ӧ�ô�����С��255"),\
                             QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
    else
    {
        emit sendThreshold(value);
        this->hide();
    }
}


void setThreshold::onCancelButton()
{
    this->hide();
    return;
}

