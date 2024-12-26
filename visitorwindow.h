#ifndef VISITORWINDOW_H
#define VISITORWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class VisitorWindow;
}

class VisitorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VisitorWindow(QWidget *parent = nullptr);
    ~VisitorWindow();

private:
    Ui::VisitorWindow *ui;
    QSqlDatabase db;

    void setupDatabase();   // Set up the database connection
    void loadImages();      // Load images and create buttons dynamically
    void setupButtonConnections(); // Connect buttons to their respective slots
    void showPaintingDetails(int paintingIndex); // Show painting details for a given index
};

#endif // VISITORWINDOW_H
