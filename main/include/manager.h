#ifndef MANAGER_H
#define MANAGER_H
#include <QImage>
#include <QString>
#include "factory.h"
#include "imagewriter.h"
#include "imageloader.h"

class AlgorithmManager {
public:
    AlgorithmManager() {}
    void processRequests(GlobalRequest r);
    //return preview picture or throws an exception if source picture is invalid
    QImage preview(GlobalRequest r);
private:
    Factory f;
    void processSingleImage(GlobalRequest r);
    void processDirectory(GlobalRequest r);
    ImageWriter imgwriter;
};

#endif // MANAGER_H
