#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "templatematching.h"

float thresholds[] = {0.7, 0.68, 0.59, 0.63, 0.65};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    for (int i = 1; i <= 5; ++i)
        ui->imageNumber->addItem(QString::number(i));

    ui->image->setScaledContents(true);

    QImage image;
    image.load("Sushi-Images/sushi1.jpg");

    ui->image->setPixmap(QPixmap::fromImage(image));

    ui->image->show();

    TemplateMatching tm("Sushi-Images/sushi1.jpg", "Sushi-Images/templ1.jpg");
    pair<Mat, int> ret = tm.getPositionsOfTemplate(thresholds[0]);
    imshow("Template Matches", ret.first);
    ui->numberOfPieces->setText(QString::number(ret.second));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_imageNumber_activated(const QString &currentImage) {
    QImage image;
    image.load("Sushi-Images/sushi" + currentImage + ".jpg");

    ui->image->setPixmap(QPixmap::fromImage(image));

    ui->image->show();

    TemplateMatching tm("Sushi-Images/sushi" + currentImage.toStdString() + ".jpg", "Sushi-Images/templ" + currentImage.toStdString() + ".jpg");
    pair<Mat, int> ret = tm.getPositionsOfTemplate(thresholds[currentImage.toInt() - 1]);
    imshow("Template Matches", ret.first);
    ui->numberOfPieces->setText(QString::number(ret.second));
}
