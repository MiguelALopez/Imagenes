#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
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

    void resizeEvent(QResizeEvent * event);

private slots:
    void on_buttonLoad_clicked();
    void on_buttonConvert_clicked();


    void on_buttonSelectChannel_clicked();

    void on_buttonApplyConvolution_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::Conversor *ui;
    QImage imageOriginal;
    QImage imageTrasformada;
    QImage imageChanelR;
    QImage imageChanelG;
    QImage imageChanelB;
    QImage imageFiltered;

    int selectedFlag;
};

#endif // CONVERSOR_H
