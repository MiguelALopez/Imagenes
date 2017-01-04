#include "error.h"

Error::Error()
{

}

void Error::ConfusionMatix(QImage *imageOriginal, QImage *imageCreated){
    double TP = 0;
    double TN = 0;
    double FN = 0;
    double FP = 0;

    int x = imageOriginal->width();
    int y = imageOriginal->height();

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            int originalColor = QColor(imageOriginal->pixel(i,j)).red();
            int createdColor = QColor(imageCreated->pixel(i,j)).red();
            if(createdColor == 255 && originalColor == 255){
                TP++;
            }
            if(createdColor == 0 && originalColor == 0){
                TN++;
            }
            if(createdColor == 255 && originalColor == 0){
                FP++;
            }
            if(createdColor == 0 && originalColor == 255){
                FN++;
            }
        }
    }

//    std::cout << "TP: " << TP << std::endl;
//    std::cout << "TN: " << TN << std::endl;
//    std::cout << "FN: " << FN << std::endl;
//    std::cout << "FP: " << FP << std::endl;

    double AC = (TP + TN)/(TP + TN + FP + FN);
    double TPR = TP / (TP + FN);
    double FPR = FP / (FP + TN);
    double TNR = TN / (TN + FP);
    double FNR = FN / (FN + TP);
    double P = TP / (FP + TP);

    QString text = "Confusion Matrix\n" +
            QString("TP: ") + QString::number(TPR) + QString("\n") +
            QString("TN: ") + QString::number(TNR) + QString("\n") +
            QString("FP: ") + QString::number(FPR) + QString("\n") +
            QString("FN: ") + QString::number(FNR) + QString("\n") +
            QString("Accuracy: ") + QString::number(AC) + QString("\n") +
            QString("Precision: ") + QString::number(P);
    QMessageBox::information(NULL, "Error Calculated", text);
}
