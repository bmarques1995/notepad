#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    bool m_IsRunning = true;
};
#endif // MAINWINDOW_HPP
