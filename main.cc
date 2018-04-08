#include "hexviewwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexViewWindow w;
    w.show();

    return a.exec();
}
