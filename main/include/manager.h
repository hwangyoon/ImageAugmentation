#ifndef MANAGER_H
#define MANAGER_H
#include <QImage>
#include <QString>
#include <algorithm>
#include <random>
#include "factory.h"
#include "imagewriter.h"
#include "imageloader.h"

class AlgorithmManager {
public:
    AlgorithmManager() {}
    void processRequests(GlobalRequest r);
    //return preview picture or throw an exception if source picture is invalid
    QImage preview(GlobalRequest r);
private:
    Factory f;
    void processSingleImage(GlobalRequest r);
    void processDirectory(GlobalRequest r);
    std::vector<QString> getCombinationsOfAlgorithms(int32_t limit,
                                                     std::vector<int32_t> &depths,
                                                     int32_t numberOfAlgorithms);
    ImageWriter imgwriter;
};

#endif // MANAGER_H
