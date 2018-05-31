#include "hexviewwindow.h"
#include "ui_hexviewwindow.h"
#include <QDir>
#include <QStringBuilder>
#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

HexViewWindow::HexViewWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HexViewWindow), filebuffer(nullptr) {
  ui->setupUi(this);
}

HexViewWindow::~HexViewWindow() {
  delete ui;
  delete filebuffer;
}

std::string HexViewWindow::hexify(array<unsigned char, CHUNK_SIZE> &buffer) {
  string retVal;
  stringstream out;
  stringstream raw;
  retVal.reserve(CHUNK_SIZE * 2);
  out << std::setfill('0') << std::setw(2) << std::hex;
  for (auto item : buffer) {
    out << std::setfill('0') << std::setw(2)
        << static_cast<unsigned short>(item) << " ";
    if (item > 65) {
      raw << static_cast<char>(item);
    } else
      raw << "0";
  }
  out << "\t" << raw.str() << endl;
  return out.str();
}

void HexViewWindow::hexifyC(array<unsigned char, CHUNK_SIZE> &buffer,
                            char *line) {
  for (auto index = 0; index < CHUNK_SIZE; index++) {
    snprintf(&line[index * 3], // 3 is size of format string....
             CHUNK_SIZE, "%02x ", buffer[index] & 0xff);
  }
}

void HexViewWindow::getFileC(std::ifstream &infile) {
  if (infile) {
    infile.seekg(0, infile.end);
    long length = infile.tellg();
    infile.seekg(0, infile.beg);
    const auto BUFFERSIZE =
        static_cast<unsigned long>(length) * sizeof(char) * 4UL;
    filebuffer = new char[BUFFERSIZE];
    memset(filebuffer, 0, BUFFERSIZE - 1);

    char buffer[CHUNK_SIZE];

    for (auto lineno = 0; lineno <= length / CHUNK_SIZE; lineno++) {
      infile.read(buffer, CHUNK_SIZE);
      if (lineno % 1000 == 0) {
        cout << " chunk no: " << lineno << endl;
      }

      if (infile) {
        for (auto index = 0; index < CHUNK_SIZE; index++) {
          snprintf(&filebuffer[lineno * CHUNK_SIZE +
                               index * 3], // 3 is size of format string....
                   CHUNK_SIZE, "%02x ", buffer[index] & 0xff);
        }
        filebuffer[lineno * CHUNK_SIZE + CHUNK_SIZE] = '\n';
      }
    }
  }
}
std::string HexViewWindow::getFile(std::ifstream &infile) {
  string filedata;
  if (infile) {
    infile.seekg(0, infile.end);
    long length = infile.tellg();
    infile.seekg(0, infile.beg);
    array<unsigned char, CHUNK_SIZE> buffer;

    filedata.reserve(static_cast<unsigned long>(length) * sizeof(char) * 3UL);

    for (auto n = 0; n <= length / CHUNK_SIZE; n++) {
      infile.read((char *)buffer.data(), buffer.size());
      if (n % 50000 == 0) {
        cout << " chunk no: " << n << endl;
      }

      if (infile) {
        filedata.append(hexify(buffer));
      }
    }
    if (!infile.eof()) {
      infile.read((char *)buffer.data(), buffer.size());
      filedata += hexify(buffer);
      cout << "Read last " << infile.gcount() << endl;
    }
    cout << "Length " << length << " chunks " << length / CHUNK_SIZE << endl;
    return filedata.c_str();
  } else {
    cout << "File not found!" << endl;
    return "";
  }
}

void HexViewWindow::on_actionOpen_triggered() {
  string filename(QDir::homePath().toStdString() + "/slask/db.sqlite");
  std::ifstream infile(QDir::homePath().toStdString() +
                           /* "/slask/db.sqlite",*/ "/slask/amiga+ball.zip",
                       std::ifstream::binary);

  string filedata = getFile(infile);

  ui->plainTextEdit->setPlainText(filedata.c_str());
}
