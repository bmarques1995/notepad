#pragma once

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.hpp"

class Controller
{
public:
	Controller(int argc, char** argv);
	~Controller();

	void run();
private:
	void readSettings();
	void configureLocale();

	QString m_ProgramPath;
	QApplication m_App;
	QTranslator m_Translator;
	MainWindow* m_MainWindow;
};