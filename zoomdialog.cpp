#include "zoomdialog.h"
#include "ui_zoomdialog.h"

zoomDialog::zoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zoomDialog)
{
    ui->setupUi(this);
    ui->scale->setText(tr("1.0"));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(onOkButton()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButton()));
    setWindowTitle(tr(" ÉèÖÃ²ÎÊı"));
    ui->scale->setFocus();
}

zoomDialog::~zoomDialog()
{
    delete ui;
}


void zoomDialog::onOkButton()
{
    float scale = ui->scale->text().toFloat();
    emit sendParamer(scale);
    this->hide();
}


void zoomDialog::onCancelButton()
{
    this->hide();
}
