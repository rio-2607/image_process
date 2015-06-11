#include "linertransformsettingdialog.h"
#include "ui_linertransformsettingdialog.h"

linerTransformSettingDialog::linerTransformSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::linerTransformSettingDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("²ÎÊıÉèÖÃ"));
    setFixedSize(160,180);
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(onOkButton()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButton()));
}

linerTransformSettingDialog::~linerTransformSettingDialog()
{
    delete ui;
}


void linerTransformSettingDialog::onOkButton()
{
    int gradient = ui->gradient->text().toInt();
    int intercept = ui->intercept->text().toInt();
    emit sendParamer(gradient,intercept);
    this->hide();
}

void linerTransformSettingDialog::onCancelButton()
{
    this->hide();
}
