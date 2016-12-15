#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <iostream>

namespace Ui {
class HistogramView;
}

class HistogramView : public QMainWindow
{
    Q_OBJECT

public:
	HistogramView(QVector<double> pixelData, int maxPixel);
    explicit HistogramView(QWidget *parent = 0);
    ~HistogramView();

    void renderHistogram(QCustomPlot *customPlot, QVector<double> pixelData, int maxPixel);

private:
    Ui::HistogramView *ui;

    QVector<double> pixelData;
    int maxPixel;
};

#endif // HISTOGRAMVIEW_H
