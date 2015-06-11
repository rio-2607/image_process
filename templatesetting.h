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
    void sendSelect(int);                   //������ѡ���ģ������
private slots:
    void onOkButton();
    void onCancelButton();
};

#endif // TEMPLATESETTING_H
