#include "mainwindow.h"
#include "ui_mainwindow.h"

static const short COMPONENT_MIN_VALUE = 0;
static const short COMPONENT_MAX_VALUE = 255;
static const short MIN_WIDTH = 1;
static const short MAX_WIDTH = 5;

static void initComboBoxValues(QComboBox* cb, const short min, const short max)
{
    for (short i = min; i <= max; ++i) {
        cb->insertItem(i, QString::number(i));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initComboBoxValues(ui->comboBoxRedComponent, COMPONENT_MIN_VALUE, COMPONENT_MAX_VALUE);
    initComboBoxValues(ui->comboBoxGreenComponent, COMPONENT_MIN_VALUE, COMPONENT_MAX_VALUE);
    initComboBoxValues(ui->comboBoxBlueComponent, COMPONENT_MIN_VALUE, COMPONENT_MAX_VALUE);
    initComboBoxValues(ui->comboBoxWidth, MIN_WIDTH, MAX_WIDTH);
}

MainWindow::~MainWindow()
{
    delete ui;
}
