#pragma once

#include <QMainWindow>
#include "threewaydialog.hpp"
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const std::string& programPath, QWidget *parent = nullptr);
    ~MainWindow();

    bool isRunning() const;
    void closeEvent(QCloseEvent* event) override;

public slots:
	void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
	void on_actionSave_as_triggered();

    void on_actionUndo_triggered();
	void on_actionRedo_triggered();
	void on_actionCut_triggered();
	void on_actionCopy_triggered();
	void on_actionPaste_triggered();

	void on_actionInfo_triggered();
	void on_actionFont_triggered();
    void on_actionColor_triggered();
    void on_actionBackground_triggered();

    void on_actionSettings_triggered();

private:
    QString m_CurrentFilename;
    QString m_AllFiles = "*.txt;*.md";
    QString m_InitialContent = "";
    Ui::MainWindow *ui;
    bool m_IsRunning = true;

    void OpenFile(QFile& file, const QString& filename);

    ThreeWayDialog::Result closeAction();

    QString m_SettingsLocation;
    static bool s_MsgInitialized;
    static QString s_WarningMsg;
    static QString s_FileReadMsg;
    static QString s_FileWriteMsg;
	static QString s_SaveMsg;
    static QString s_TextColorSelect;
    static QString s_OpenFileMsg;
    static void initMessages();
};
