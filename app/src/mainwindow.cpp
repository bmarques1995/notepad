#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QColorDialog>

QString MainWindow::s_WarningMsg;
QString MainWindow::s_FileReadMsg;
QString MainWindow::s_FileWriteMsg;
QString MainWindow::s_SaveMsg;
QString MainWindow::s_TextColorSelect;
QString MainWindow::s_OpenFileMsg;
bool MainWindow::s_MsgInitialized = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setCentralWidget(ui->textEdit);
	if (!s_MsgInitialized)
	{
		initMessages();
	}
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
    QString filename = QFileDialog::getOpenFileName(this, s_OpenFileMsg, QDir::homePath(), m_AllFiles);
	QFile file(filename);
    m_CurrentFilename = filename;
    if (file.exists())
    {
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
			QString preReadWarning = s_FileReadMsg;
			preReadWarning.arg(filename).arg(file.errorString());
            QMessageBox::warning(this, s_WarningMsg, preReadWarning);
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
			QString preWriteWarning = s_FileWriteMsg;
			preWriteWarning.arg(m_CurrentFilename).arg(file.errorString());
			QMessageBox::warning(this, s_WarningMsg, preWriteWarning);
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
	QString filename = QFileDialog::getSaveFileName(this, s_SaveMsg, QDir::homePath(), m_AllFiles);
	m_CurrentFilename = filename;
	if(m_CurrentFilename == "")
		return;

	QFile file(m_CurrentFilename);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QString warningMsg = QCoreApplication::translate("MainWindowMessages", "Warning");
		QString fileMsg = s_FileWriteMsg;
		fileMsg.arg(m_CurrentFilename).arg(file.errorString());
		if(file.exists())
			QMessageBox::warning(this, s_WarningMsg, fileMsg);
		return;
	}
	QTextStream out(&file);
	out << ui->textEdit->toPlainText();
	m_InitialContent = ui->textEdit->toPlainText();
	file.flush();
	file.close();
}

void MainWindow::on_actionUndo_triggered()
{
	ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
	ui->textEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
	ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
	ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
	ui->textEdit->paste();
}

void MainWindow::on_actionInfo_triggered()
{
	QString text = QCoreApplication::translate("MainWindowAbout", "Developed by Bruno S Marques, available at ") + 
		"<a href=\"https://github.com/bmarques1995/notepad\">https://github.com/bmarques1995/notepad.git</a> " +
		QCoreApplication::translate("MainWindowAbout", "under") +
		" <a href=\"https://opensource.org/license/bsd-3-clause\">BSD 3-Clause License</a>";
	QString headline = QCoreApplication::translate("MainWindowMessages", "About QNotepad");
	QMessageBox::about(this, headline, text);
}

void MainWindow::on_actionFont_triggered()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, ui->textEdit->font());
	if (ok)
		ui->textEdit->setFont(font);
	return;
}

void MainWindow::on_actionColor_triggered()
{
	QColor color = QColorDialog::getColor(Qt::white, this, s_TextColorSelect);
	if(color.isValid())
		ui->textEdit->setTextColor(color);
}

void MainWindow::on_actionBackground_triggered()
{
	QColor color = QColorDialog::getColor(Qt::white, this, s_TextColorSelect);
	if (color.isValid())
		ui->textEdit->setTextBackgroundColor(color);
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

void MainWindow::initMessages()
{
	s_WarningMsg = QCoreApplication::translate("MainWindowMessages", "Warning");
	s_FileReadMsg = QCoreApplication::translate("MainWindowMessages", "Cannot read file %1:\n%2.");
	s_FileWriteMsg = QCoreApplication::translate("MainWindowMessages", "Cannot write file %1:\n%2.");
	s_SaveMsg = QCoreApplication::translate("MainWindowMessages", "Save File");
	s_TextColorSelect = QCoreApplication::translate("MainWindowMessages", "Select Text Color");
	s_OpenFileMsg = QCoreApplication::translate("MainWindowMessages", "Open File");
	s_MsgInitialized = true;
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}
