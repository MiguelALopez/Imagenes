#ifndef MORPHOLOGICALOPERATORS_H
#define MORPHOLOGICALOPERATORS_H

#include <QImage>
//#include

class MorphologicalOperators
{
public:
    MorphologicalOperators();

    void dilate(QImage *image);
    void erosion(QImage *image);
};

#endif // MORPHOLOGICALOPERATORS_H
