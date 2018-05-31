#ifndef HEXVIEWWINDOW_H
#define HEXVIEWWINDOW_H

#include <QMainWindow>
#include <array>
#include <fstream>
#include <memory>
#include <string>

namespace Ui {
class HexViewWindow;
}

class HexViewWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit HexViewWindow(QWidget *parent = nullptr);
  ~HexViewWindow();
  static const long CHUNK_SIZE = 30;
private slots:
  void on_actionOpen_triggered();

private:
  std::string hexify(std::array<unsigned char, CHUNK_SIZE> &buffer);
  void hexifyC(std::array<unsigned char, CHUNK_SIZE> &buffer, char *line);
  std::string getFile(std::ifstream &filename);
  void getFileC(std::ifstream &infile);
  Ui::HexViewWindow *ui;
  char *filebuffer;
};

#endif // HEXVIEWWINDOW_H
