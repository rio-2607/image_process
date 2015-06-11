#ifndef GRAYEXTENDDIALOG_H
#define GRAYEXTENDDIALOG_H

#include <QDialog>

namespace Ui {
class grayExtendDialog;
}

class grayExtendDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit grayExtendDialog(QWidget *parent = 0);
    ~grayExtendDialog();
    
private:
    Ui::grayExtendDialog *ui;
signals:
    void sendParamer(int coor1_x,int coor1_y,int coor2_x,int coor2_y);
private slots:
    void onOkButton();
    void onCancelButton();
};

#endif // GRAYEXTENDDIALOG_H
