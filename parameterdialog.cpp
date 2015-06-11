#include "parameterdialog.h"
#include "ui_parameterdialog.h"

parameterDialog::parameterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parameterDialog)
{
    ui->setupUi(this);
    ui->hLineEdit->setText(tr("0"));
    ui->vLineEdit->setText(tr("0"));
    setWindowTitle(tr("图像平移参数设定"));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(onOkButton()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButton()));
}

parameterDialog::~parameterDialog()
{
    delete ui;
}


void parameterDialog::onOkButton()
{
    int x = ui->hLineEdit->text().toInt();
    int y = ui->vLineEdit->text().toInt();
    emit sendParameter(x,y);
    hide();
}

void parameterDialog::onCancelButton()
{
    emit sendParameter(0,0);
    hide();
}
