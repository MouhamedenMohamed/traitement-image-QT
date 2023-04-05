#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QWidget>
#include<QLabel>
#include<QPainter>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
        QWidget window;
        window.setWindowTitle("QFileDialog");
        window.setGeometry(100, 100, 300, 200);

        QPushButton button("Ouvrir le fichier", &window);
        button.setToolTip("Cliquez pour ouvrir le QFileDialog");
        button.move(100, 50);

        QString filename = QFileDialog::getOpenFileName(
                    &window,
                    "Ouvrir un fichier en .png",
                    "",
                    "Images (*.png)");
        if(!filename.isNull()) {

//            QImage image ;

            QImage image(filename);
                    if(image.isNull()) {
                        QMessageBox::critical(&window, "Erreur", "Le fichier sélectionné ne contient pas une image valide.");
                    } else {
                        // Creating a QLabel to display the image off-screen
                        QLabel* imageLabel = new QLabel(&window);
                        QPixmap pix = QPixmap::fromImage(image);
                        imageLabel->setPixmap(pix);
//                        imageLabel->hide();

                        // Creating a QImage that will be displayed on the parent widget on top of other elements
                        QImage displayImage(image.size(), QImage::Format_ARGB32_Premultiplied);
                        QPainter painter(&displayImage);
                        image = image.scaled(ui->label->size(), Qt::KeepAspectRatio); // Resize the image
                        painter.drawImage(0, 0, image);
//                        painter.end();

                        // Creating a QLabel to display the QImage on the parent widget
                        QLabel* displayImageLabel = new QLabel(ui->label);
                        displayImageLabel->setPixmap(QPixmap::fromImage(displayImage));
                        displayImageLabel->show();
                    }
        }
        if(filename.isNull()){
            QMessageBox::critical(&window, "Erreur", "Le fichier sélectionné ne contient pas une image valide.");

        }


}

