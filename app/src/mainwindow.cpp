#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setCentralWidget(ui->textEdit);
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
	
	if (m_InitialContent == ui->textEdit->toPlainText())
	{
		m_IsRunning = false;
		QWidget::closeEvent(event);
	}
	else {
		auto result = closeAction();
		switch (result)
		{
		case ThreeWayDialog::OptionA:
		case ThreeWayDialog::OptionB:
			QWidget::closeEvent(event);
			break;
		case ThreeWayDialog::OptionC:
		default:
			event->ignore();
			break;
		}
	}
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), m_AllFiles);
	QFile file(filename);
    m_CurrentFilename = filename;
    if (file.exists())
    {
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, tr("Warning"), tr("Cannot read file %1:\n%2.").arg(filename).arg(file.errorString()));
            return;
		}
        QTextStream enterFile(&file);
		QString text = enterFile.readAll();
		m_InitialContent = text;
		ui->textEdit->setText(text);
    }

    file.close();
}

void MainWindow::on_actionExit_triggered()
{
	this->close();
}

void MainWindow::on_actionSave_triggered()
{
	QFile file(m_CurrentFilename);
	if (file.exists())
	{
		if (!file.open(QFile::WriteOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Warning"), tr("Cannot write file %1:\n%2.").arg(m_CurrentFilename).arg(file.errorString()));
			return;
		}
		QTextStream out(&file);
		out << ui->textEdit->toPlainText();
		m_InitialContent = ui->textEdit->toPlainText();
		file.flush();
		file.close();
	}
	else
		on_actionSave_as_triggered();
}

void MainWindow::on_actionSave_as_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), m_AllFiles);
	m_CurrentFilename = filename;
	if(m_CurrentFilename == "")
		return;

	QFile file(m_CurrentFilename);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		if(file.exists())
			QMessageBox::warning(this, tr("Warning"), tr("Cannot write file %1:\n%2.").arg(m_CurrentFilename).arg(file.errorString()));
		return;
	}
	QTextStream out(&file);
	out << ui->textEdit->toPlainText();
	m_InitialContent = ui->textEdit->toPlainText();
	file.flush();
	file.close();
}

ThreeWayDialog::Result MainWindow::closeAction()
{
	auto reply = ThreeWayDialog(nullptr);
	if (reply.exec() == QDialog::Accepted) {
		auto result = reply.getResult();
		switch (result)
		{
		case ThreeWayDialog::OptionA:
			on_actionSave_triggered();
		case ThreeWayDialog::OptionB:
		{
			m_IsRunning = false;
			break;
		}
		case ThreeWayDialog::OptionC:
		default: break;
		}
	}
	return reply.getResult();
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}
