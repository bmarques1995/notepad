#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isRunning() const
{
    return m_IsRunning;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	m_IsRunning = false;
    QWidget::closeEvent(event);
}
