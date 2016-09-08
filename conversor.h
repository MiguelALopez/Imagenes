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
    void on_buttomLoad_clicked();
    void on_buttomConvert_clicked();


private:
    Ui::Conversor *ui;
    QImage imageOriginal;
    QImage imageTrasformada;
};

#endif // CONVERSOR_H
