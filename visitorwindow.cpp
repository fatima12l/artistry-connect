#include "visitorwindow.h"
#include "ui_visitorwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

VisitorWindow::VisitorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisitorWindow)
{
    ui->setupUi(this);

    // Disable maximize and minimize buttons
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);

    // Ensure labels scale their contents
    for (int i = 1; i <= 11; ++i) {
        QLabel *label = findChild<QLabel *>("label_" + QString::number(i));
        if (label) {
            label->setScaledContents(true); // Scale image to fit the label
        }
    }

    setupDatabase(); // Set up the database
    loadImages();    // Load and display images
    setupButtonConnections(); // Connect buttons to show painting details
}

VisitorWindow::~VisitorWindow()
{
    delete ui;
    if (db.isOpen()) {
        db.close();
    }
}

void VisitorWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/artistryconnect.db");

    if (!db.open()) {
        qCritical() << "Database connection failed:" << db.lastError().text();
    }
}

void VisitorWindow::loadImages()
{
    if (!db.isOpen()) {
        qCritical() << "Database is not open!";
        return;
    }

    QSqlQuery query("SELECT image FROM paintings");
    if (!query.exec()) {
        qCritical() << "Query failed:" << query.lastError().text();
        return;
    }

    int labelIndex = 1;
    while (query.next() && labelIndex <= 11) {
        QByteArray imageData = query.value(0).toByteArray(); // Fetch image data
        QPixmap pixmap;
        pixmap.loadFromData(imageData); // Convert QByteArray to QPixmap

        QLabel *label = findChild<QLabel *>("label_" + QString::number(labelIndex));
        if (label) {
            if (!pixmap.isNull()) {
                label->setPixmap(pixmap); // Display the image
            } else {
                label->setText("No Image"); // Placeholder text if image is invalid
            }
        }

        ++labelIndex;
    }
}

void VisitorWindow::setupButtonConnections()
{
    for (int i = 1; i <= 11; ++i) {
        QPushButton *button = findChild<QPushButton *>("pushButton_" + QString::number(i));
        if (button) {
            connect(button, &QPushButton::clicked, this, [=]() {
                showPaintingDetails(i);
            });
        }
    }
}

void VisitorWindow::showPaintingDetails(int paintingIndex)
{
    if (!db.isOpen()) {
        qCritical() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name, artist, upload_date, price, details FROM paintings LIMIT 1 OFFSET :index");
    query.bindValue(":index", paintingIndex - 1);

    if (!query.exec()) {
        qCritical() << "Query failed:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString name = query.value(0).toString();
        QString artist = query.value(1).toString();
        QString uploadDate = query.value(2).toString();
        QString price = query.value(3).toString();
        QString details = query.value(4).toString();

        // Create a dialog to display the painting details
        QDialog *dialog = new QDialog(this);
        QVBoxLayout *layout = new QVBoxLayout(dialog);

        QLabel *nameLabel = new QLabel("Name: " + name, dialog);
        QLabel *artistLabel = new QLabel("Artist: " + artist, dialog);
        QLabel *uploadDateLabel = new QLabel("Upload Date: " + uploadDate, dialog);
        QLabel *priceLabel = new QLabel("Price: " + price, dialog);
        QLabel *detailsLabel = new QLabel("Details: " + details, dialog);

        layout->addWidget(nameLabel);
        layout->addWidget(artistLabel);
        layout->addWidget(uploadDateLabel);
        layout->addWidget(priceLabel);
        layout->addWidget(detailsLabel);

        dialog->setLayout(layout);
        dialog->setWindowTitle("Painting Details");
        dialog->exec();
    } else {
        qCritical() << "No painting details found for index:" << paintingIndex;
    }
}
