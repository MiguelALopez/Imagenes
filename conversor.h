#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QRgb>
#include <iostream>
#include <math.h>
#include <algorithm>
//#include <QtCharts>
//#include <QtCharts/QBarSeries>
#include "histogramview.h"

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

    typedef enum{
        RGB, GRAYSCALE, HSV, HSL, OPPONENT, CMY, INVERTIDOS
    }TypeTransform;

    typedef enum{
        RED, GREEN, BLUE, GREY
    }ChannelFilter;

private slots:
    void on_buttonLoad_clicked();
    void on_buttonConvert_clicked();


    void on_buttonSelectChannel_clicked();

    void on_buttonApplyConvolution_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_buttonApplyContrast_clicked();

    void on_buttonEdges_clicked();

    void initVector();

    void on_bUseConv_clicked();

    void on_bSaveconv_clicked();

    void on_bUseContrast_clicked();

    void on_bSaveContrast_clicked();

    void on_bUseEdges_clicked();

    void on_bSaveEdges_clicked();

    void on_bApplyThres_clicked();

    void on_bUseThres_clicked();

    void on_bSaveThres_clicked();

    void on_bApplyMorph_clicked();

    void on_buttonSave_clicked();

private:
    Ui::Conversor *ui;
    void resizeWindow();

    QImage imageOriginal;
    QImage imageTrasformada;
    QImage imageChannelR;
    QImage imageChannelG;
    QImage imageChannelB;
    QImage imageChoosed;
    
    QImage imageConvolution;
    QImage imageContrast;
    QImage imageEdges;
    QImage imageThres;

    QVector<double> imageTransformadaHisto;


    TypeTransform transform;
    ChannelFilter channel;
};

#endif // CONVERSOR_H

