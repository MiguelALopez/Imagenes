#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>
#include <QRgb>
#include <iostream>

namespace Ui {
class Conversor;
}

class Conversor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Conversor(QWidget *parent = 0);
    ~Conversor();

private slots:
    void on_buttomCargar_clicked();
    void on_pushButton_2_clicked();

    void convertRGBtoYue();
    void convertRGBtoHSV();

private:
    Ui::Conversor *ui;
    QImage imageOriginal;
};

#endif // CONVERSOR_H
