#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "Raschet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  ui->As->clear();
  ui->Asef->clear();
  ui->d->clear();
  try {

    float a = ui->a->text().toFloat();
    if (a <= 0) {
      throw std::runtime_error("параметр a неверно заполнен");
    }
    float h = ui->h->text().toFloat();
    if (h <= 0) {
      throw std::runtime_error("параметр h неверно заполнен");
    }

    float hf = ui->hf->text().toFloat();
    if (hf <= 0) {
      throw std::runtime_error("параметр hf неверно заполнен");
    }

    float b = ui->b->text().toFloat();
    if (b <= 0) {
      throw std::runtime_error("параметр b неверно заполнен");
    }

    float bf = ui->bf->text().toFloat();
    if (bf <= 0) {
      throw std::runtime_error("параметр bf неверно заполнен");
    }

    float M = ui->M->text().toFloat();
    if (M <= 0) {
      throw std::runtime_error("параметр M неверно заполнен");
    }

    if (N <= -1) {
      throw std::runtime_error("параметр N неверно заполнен");
    }

    Params params{bf, b, hf, h, a, M * 1000, A, B};
    float As = params.Raschet() * 100;
    ui->As->setText(QString::number(As));

    auto rez = params.Italon(As, N);
    if (rez.Asef == 0) {
      throw std::runtime_error("поменяете количество стержней");
    }
    ui->Asef->setText(QString::number(rez.Asef));
    ui->d->setText(QString::number(rez.diam));
  } catch (std::exception &a) {
    QMessageBox::warning(this, "ошибка", a.what());
  }
}

void MainWindow::on_comboBox_3_activated(int index) { N = index; }

void MainWindow::on_comboBox_activated(int index) { B = index; }

void MainWindow::on_comboBox_2_activated(int index) { A = index; }
