#ifndef PARAMETERDIALOG_H
#define PARAMETERDIALOG_H

#include <QDialog>

namespace Ui {
class parameterDialog;
}

class parameterDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit parameterDialog(QWidget *parent = 0);
    ~parameterDialog();
    
private:
    Ui::parameterDialog *ui;
signals:
    void sendParameter(int xOffset,int yOffset);
private slots:
    void onOkButton();
    void onCancelButton();
};

#endif // PARAMETERDIALOG_H
