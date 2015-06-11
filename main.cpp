#include <QApplication>
#include"mainwindow.h"
//#include"MainWindow/mainwindow.h"
#include<QTextCodec>
//#include"drawHistogram/drawhistogram.h"
//#include"parameterDialog/parameterdialog.h"
//#include"templatesetting.h"
//#include"setthreshold.h"
//#include"linertransformsettingdialog.h"
//#include"grayextenddialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    MainWindow w;

    w.show();

    
    return a.exec();
}
