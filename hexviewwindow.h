#ifndef HEXVIEWWINDOW_H
#define HEXVIEWWINDOW_H

#include <QMainWindow>

namespace Ui {
class HexViewWindow;
}

class HexViewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HexViewWindow(QWidget *parent = 0);
    ~HexViewWindow();

private:
    Ui::HexViewWindow *ui;
};

#endif // HEXVIEWWINDOW_H
