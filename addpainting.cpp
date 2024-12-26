#include "addpainting.h"
#include "ui_addpainting.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QFile>

addPainting::addPainting(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addPainting)
{
    ui->setupUi(this);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/artistryconnect.db");

    if (!mydb.open()) {
        ui->label->setText("Failed");
    } else {
        ui->label->setText("Connected");
    }

    // Connect the button for uploading image
    connect(ui->pushButton_uploadImage, &QPushButton::clicked, this, &addPainting::on_pushButton_uploadImage_clicked);
}

addPainting::~addPainting()
{
    delete ui;
}

void addPainting::on_pushButton_submit_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString artist = ui->lineEdit_artist->text();
    QString desc = ui->lineEdit_desc->text();
    QString date = ui->lineEdit_date->text();
    QString price = ui->lineEdit_price->text();

    // Validate input fields
    if (name.isEmpty() || artist.isEmpty() || desc.isEmpty() || date.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill out all the required fields.");
    } else {
        // Prepare the SQL query to insert the data into the database
        QSqlQuery query;

        query.prepare("INSERT INTO paintings (name, artist, details, upload_date, price, image) "
                      "VALUES (:name, :artist, :details, :upload_date, :price, :image)");

        // Bind the input values to the query
        query.bindValue(":name", name);
        query.bindValue(":artist", artist);
        query.bindValue(":upload_date", date);
        query.bindValue(":price", price);
        query.bindValue(":details", desc);
        query.bindValue(":image", imageData);  // Bind the image data here

        // Execute the query
        if (query.exec()) {
            QMessageBox::information(this, "Congratulations", "Successfully Added!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to add painting: " + query.lastError().text());
            qDebug() << query.lastQuery();
            qDebug() << query.boundValues();
        }
    }
}

void addPainting::on_pushButton_uploadImage_clicked()
{
    // Open a file dialog to choose an image
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!fileName.isEmpty()) {
        // Read the image file into binary data (needed for database storage)
        QFile imageFile(fileName);
        if (imageFile.open(QIODevice::ReadOnly)) {
            imageData = imageFile.readAll();  // Store the image data in imageData variable
            imageFile.close();
        }

        // Load the image into a QPixmap and display it in the label
        QPixmap pixmap(fileName);
        if (!pixmap.isNull()) {
            ui->label_imagePreview->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));  // Scale image to fit QLabel
        } else {
            QMessageBox::warning(this, "Error", "Failed to load the image.");
        }
    }
}
