#ifndef MANAGER_H
#define MANAGER_H
#include <QImage>
#include <QString>
#include "factory.h"
#include "imagewriter.h"

class AlgorithmManager {
public:
    AlgorithmManager() {}
    void process_requests(GlobalRequest r);
    QImage preview(GlobalRequest r);
private:
    Factory f;
    ImageWriter imgwriter;
};

#endif // MANAGER_H
