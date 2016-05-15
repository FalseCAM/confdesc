#include "mainwindow.h"
#include <confdesc/confdesc.h>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QSpinBox>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

std::string MainWindow::exampleJSON() {
  std::string json =
      "{"
      "\"confdesc\":["
      "{\"name\":\"testname\", \"type\":\"integer\",\"value\":15, \"max\":42},"
      "{\"name\":\"testname2\", \"type\":\"float\",\"value\":3.14, \"max\":42},"
      "{\"name\":\"testname3\", \"type\":\"boolean\",\"value\":true},"
      "{\"name\":\"testname4\", \"type\":\"string\",\"value\":\"Hello "
      "World!\", \"max\":42}"
      "]"
      "}";
  return json;
}

void MainWindow::on_exampleButton_clicked() {
  ui->jsonBrowser->setText(QString::fromStdString(exampleJSON()));
}

void MainWindow::on_generateButton_clicked() {
  QLayoutItem* item;
  while ((item = ui->generateLayout->layout()->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }

  cd::ConfDesc desc(ui->jsonBrowser->toPlainText().toStdString());
  for (const auto& items : desc) {
    cd::ConfigItem item = items.second;

    switch (item.getType()) {
      case cd::DataType::BOOLEAN: {
        QCheckBox* checkbox = new QCheckBox();
        checkbox->setChecked(item.getValue<bool>());
        checkbox->setText(QString::fromStdString(item.getName()) + " ");
        ui->generateLayout->addWidget(checkbox);
      } break;
      case cd::DataType::FLOAT: {
        QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
        doubleSpinBox->setValue(item.getValue<double>());
        doubleSpinBox->setPrefix(QString::fromStdString(item.getName()) + " ");
        ui->generateLayout->addWidget(doubleSpinBox);
      } break;
      case cd::DataType::INTEGER: {
        QSpinBox* spinBox = new QSpinBox();
        spinBox->setValue(item.getValue<int>());
        spinBox->setMaximum(item.getMax());
        spinBox->setMinimum(item.getMin());
        spinBox->setPrefix(QString::fromStdString(item.getName()) + " ");
        ui->generateLayout->addWidget(spinBox);
      } break;
      case cd::DataType::STRING: {
        QLineEdit* lineEdit = new QLineEdit();
        lineEdit->setText(QString::fromStdString(item.getValue<std::string>()));
        lineEdit->setMaxLength(item.getMax());
        lineEdit->setToolTip(QString::fromStdString(item.getName()));
        ui->generateLayout->addWidget(lineEdit);
      } break;
      default:
        break;
    };
  }
}
