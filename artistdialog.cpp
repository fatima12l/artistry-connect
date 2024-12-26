#include "artistdialog.h"
#include "ui_artistdialog.h"
#include "addpainting.h"
#include<visitorwindow.h>
artistDialog::artistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::artistDialog)
{
    ui->setupUi(this);
}

artistDialog::~artistDialog()
{
    delete ui;
}

void artistDialog::on_pushButton_AddPainting_clicked()
{
    addPainting add;
    add.setModal(true);
    add.exec();
}


void artistDialog::on_pushButton_search_clicked()
{
    VisitorWindow *visitorWindow = new VisitorWindow(this); // Create a new instance of VisitorWindow
    visitorWindow->show(); // Show the VisitorWindow

}

