#ifndef SETTHRESHOLD_H
#define SETTHRESHOLD_H

#include <QDialog>

namespace Ui {
class setThreshold;
}

class setThreshold : public QDialog
{
    Q_OBJECT
    
public:
    explicit setThreshold(QWidget *parent = 0);
    ~setThreshold();
private slots:
    void onOkButton();
    void onCancelButton();
signals:
    void sendThreshold(int thres);
private:
    Ui::setThreshold *ui;
};

#endif // SETTHRESHOLD_H
