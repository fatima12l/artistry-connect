#ifndef ARTISTDIALOG_H
#define ARTISTDIALOG_H

#include <QDialog>

namespace Ui {
class artistDialog;
}

class artistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit artistDialog(QWidget *parent = nullptr);
    ~artistDialog();

private slots:
    void on_pushButton_AddPainting_clicked();

    void on_pushButton_search_clicked();

private:
    Ui::artistDialog *ui;
};

#endif // ARTISTDIALOG_H
