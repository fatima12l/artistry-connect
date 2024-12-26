#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "artistdialog.h"
#include "visitorwindow.h"
#include <QScreen>
#include <QApplication>
#include <QPixmap> // Include QPixmap for image handling

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Center the buttons in the desktop window
    centerButtons();
    setLogoImage(); // Call to set the logo image
    setAnotherImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::centerButtons()
{
    // Get the screen geometry
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // Calculate the center of the screen
    int screenCenterX = screenGeometry.width() / 2;
    int screenCenterY = screenGeometry.height() / 2;

    // Get button dimensions
    int buttonWidth = ui->pushButtonartist->width();
    int buttonHeight = ui->pushButtonartist->height();

    // Calculate positions for the buttons
    int artistButtonX = screenCenterX - buttonWidth - 10; // Adjust for left placement
    int artistButtonY = screenCenterY - (buttonHeight / 2);

    int visitorButtonX = screenCenterX + 10; // Adjust for right placement
    int visitorButtonY = screenCenterY - (buttonHeight / 2);

    // Move the buttons
    ui->pushButtonartist->move(artistButtonX, artistButtonY);
    ui->pushButtonvisitor->move(visitorButtonX, visitorButtonY);
}

void MainWindow::on_pushButtonartist_clicked()
{
    artistDialog ad;
    ad.setModal(true);
    ad.exec();
}

void MainWindow::on_pushButtonvisitor_clicked()
{
    VisitorWindow *vw = new VisitorWindow();  // Create a new instance of the window
    vw->show();  // Show the window
}
void MainWindow::setLogoImage()
{
    // Set the relative path to the logo
    QString logoPath = "D:\logoo.PNG"; // Adjust path if needed

    QPixmap logoPixmap(logoPath);
    if (!logoPixmap.isNull()) {
        ui->label_logo->setPixmap(logoPixmap); // Set the logo image
        ui->label_logo->setScaledContents(true); // Scale the image to fit the label
    } else {
        qWarning("Failed to load the logo image!");
    }
}
void MainWindow::setAnotherImage()
{
    // Set the relative path to the logo
    QString logoPath = "D:\logoo.PNG"; // Adjust path if needed

    QPixmap logoPixmap(logoPath);
    if (!logoPixmap.isNull()) {
        ui->label_flower2->setPixmap(logoPixmap); // Set the logo image
        ui->label_flower2->setScaledContents(true); // Scale the image to fit the label
    } else {
        qWarning("Failed to load the logo image!");
    }
}
