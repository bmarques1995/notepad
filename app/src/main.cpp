#include "mainwindow.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

//..\..\Windows\Debug\bin\lrelease .\Notepad_en_US.xml -qm .\Notepad_en_US.bin

extern int qInitResources();
extern int qCleanupResources();

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    /*QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Notepad_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();*/

    QApplication a(argc, argv);
    qInitResources();
    QTranslator translator;
    translator.load("./translations/pt_BR.qm");
    a.installTranslator(&translator);
    MainWindow w;
    w.show();
    while(w.isRunning())
        a.processEvents();
	qCleanupResources();
    return 0;
    
}
