#ifndef ZOOMDIALOG_H
#define ZOOMDIALOG_H

#include <QDialog>

namespace Ui {
class zoomDialog;
}

class zoomDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit zoomDialog(QWidget *parent = 0);
    ~zoomDialog();
    
private:
    Ui::zoomDialog *ui;
signals:
    void sendParamer(float scale);

private slots:
    void onOkButton();
    void onCancelButton();
};

#endif // ZOOMDIALOG_H
