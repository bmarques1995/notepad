#pragma once

#include <QMainWindow>
#include "threewaydialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isRunning() const;
    void closeEvent(QCloseEvent* event) override;

public slots:
	void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
	void on_actionSave_as_triggered();

private:
    QString m_CurrentFilename;
    QString m_AllFiles = "*.txt;*.md";
    QString m_InitialContent = "";
    Ui::MainWindow *ui;
    bool m_IsRunning = true;

    ThreeWayDialog::Result closeAction();
};
