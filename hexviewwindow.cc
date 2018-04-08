#include "hexviewwindow.h"
#include "ui_hexviewwindow.h"

HexViewWindow::HexViewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HexViewWindow)
{
    ui->setupUi(this);
}

HexViewWindow::~HexViewWindow()
{
    delete ui;
}
