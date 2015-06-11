#include "templatesetting.h"
#include "ui_templatesetting.h"
#include<QDebug>

templateSetting::templateSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::templateSetting)
{
    ui->setupUi(this);
    ui->meanTemplate->setChecked(true);
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(onOkButton()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButton()));
}

templateSetting::~templateSetting()
{
    delete ui;
}





void templateSetting::onOkButton()
{
    int select;
    if(ui->meanTemplate->isChecked())
        select = 1;
    if(ui->gaussTemplate->isChecked())
        select = 2;
    if(ui->commonTemplate1->isChecked())
        select = 3;
    if(ui->commonTemplate2->isChecked())
        select = 4;
    if(ui->commonTemplate3->isChecked())
        select = 5;
    emit sendSelect(select);
    this->hide();
}


void templateSetting::onCancelButton()
{
    this->hide();
}
