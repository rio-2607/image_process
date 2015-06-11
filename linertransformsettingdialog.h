#ifndef LINERTRANSFORMSETTINGDIALOG_H
#define LINERTRANSFORMSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class linerTransformSettingDialog;
}

class linerTransformSettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit linerTransformSettingDialog(QWidget *parent = 0);
    ~linerTransformSettingDialog();
    
private:
    Ui::linerTransformSettingDialog *ui;
signals:
    void sendParamer(int gradient,int intercept);       //ͨ���źŰ����õ�б�ʺͽؾഫ��mainwindow
private slots:
    void onOkButton();
    void onCancelButton();
};

#endif // LINERTRANSFORMSETTINGDIALOG_H
