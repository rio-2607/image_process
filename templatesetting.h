#ifndef TEMPLATESETTING_H
#define TEMPLATESETTING_H

#include <QDialog>

namespace Ui {
class templateSetting;
}

class templateSetting : public QDialog
{
    Q_OBJECT
    
public:
    explicit templateSetting(QWidget *parent = 0);
    ~templateSetting();
    
private:
    Ui::templateSetting *ui;
signals:
    void sendSelect(int);                   //发送所选择的模板的序号
private slots:
    void onOkButton();
    void onCancelButton();
};

#endif // TEMPLATESETTING_H
