#include "grayextenddialog.h"
#include "ui_grayextenddialog.h"
#include<QMessageBox>

grayExtendDialog::grayExtendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::grayExtendDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("参数设置"));
    setFixedSize(200,230);
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(onOkButton()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButton()));
}

grayExtendDialog::~grayExtendDialog()
{
    delete ui;
}


void grayExtendDialog::onOkButton()
{
    int coor1_x = ui->coor1_x->text().toInt();
    int coor1_y = ui->coor1_y->text().toInt();
    int coor2_x = ui->coor2_x->text().toInt();
    int coor2_y = ui->coor2_y->text().toInt();
    if(coor2_x <= coor1_x)
    {
        QMessageBox::warning(this,tr("警告"),tr("输入参数有误\n第二个点的横坐标一定要大于第一个点的横坐标"),\
                             QMessageBox::Yes,QMessageBox::Yes);
        return;
    }

    emit sendParamer(coor1_x,coor1_y,coor2_x,coor2_y);
    this->hide();
}


void grayExtendDialog::onCancelButton()
{
    this->hide();
}
