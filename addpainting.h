#ifndef ADDPAINTING_H
#define ADDPAINTING_H
#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QByteArray>
namespace Ui {
class addPainting;
}

class addPainting : public QDialog
{
    Q_OBJECT

public:
    explicit addPainting(QWidget *parent = nullptr);
    ~addPainting();

private slots:

    void on_pushButton_submit_clicked();
    void on_pushButton_uploadImage_clicked();  // Slot for uploading image

private:
    Ui::addPainting *ui;
    QByteArray imageData;  // Declare imageData as a private member

};

#endif // ADDPAINTING_H
