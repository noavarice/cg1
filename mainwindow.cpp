#include "mainwindow.h"
#include "ui_mainwindow.h"

static const uint8_t COMPONENT_MIN_VALUE = 0;
static const uint8_t COMPONENT_MAX_VALUE = 255;
static const uint8_t MIN_WIDTH = 1;
static const uint8_t MAX_WIDTH = 5;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (short i = COMPONENT_MIN_VALUE; i <= COMPONENT_MAX_VALUE; ++i) {
        ui->comboBoxRedComponent->insertItem(i, QString::number(i));
        ui->comboBoxGreenComponent->insertItem(i, QString::number(i));
        ui->comboBoxBlueComponent->insertItem(i, QString::number(i));
    }

    for (uint8_t i = MIN_WIDTH; i < MAX_WIDTH; ++i) {
        ui->comboBoxWidth->insertItem(i, QString::number(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
