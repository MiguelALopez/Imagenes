#ifndef ERROR_H
#define ERROR_H

#include <QImage>
#include <QMessageBox>
#include <iostream>

class Error
{
public:
    Error();

    void ConfusionMatix(QImage *imageOriginal, QImage *imageCreated);
};

#endif // ERROR_H
