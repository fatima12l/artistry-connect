#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void on_pushButtonartist_clicked();

    void on_pushButtonvisitor_clicked();

private:
    Ui::MainWindow *ui;
    void centerButtons();
    void setLogoImage();
    void setAnotherImage();
};
#endif // MAINWINDOW_H
