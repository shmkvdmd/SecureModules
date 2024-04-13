#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm lf;
    lf.show();
    return a.exec();
}
