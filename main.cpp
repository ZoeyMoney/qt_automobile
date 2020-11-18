#include "login.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.setWindowIcon(QIcon(":/img/favicon.ico"));
    w.show();

    return a.exec();
}
