#ifndef MANAGER_H
#define MANAGER_H
#include <QImage>
#include <QString>
#include <algorithm>
#include <random>
#include <memory>
#include "factory.h"
#include "imagewriter.h"
#include "imageloader.h"

/* A class that handles user's requests */
class AlgorithmManager {
public:
    AlgorithmManager() {}
    /* Processes information provided in GlobalRequest object */
    void processRequests(GlobalRequest r);
    /* Returns preview picture or throws an exception if source picture is invalid */
    QImage preview(GlobalRequest r);
private:
    Factory f;
    /* Gets random algorithm combinations according to user's request
     * and creates processed image for each combination then save all images */
    void processSingleImage(GlobalRequest r);
    /* Uses the processSingleImage method on each picture in the directory */
    void processDirectory(GlobalRequest r);
    /* Creates vector of random algorithm combinations according to user's request */
    std::vector<QString> getCombinationsOfAlgorithms(int32_t limit,
                                                     std::vector<int32_t> &depths,
                                                     int32_t numberOfAlgorithms);
    /* Creates algorithm combination and saves it to vector
     * This method is used in getCombinationOfAlgorithms as a help method */
    void appendNewCombination(std::vector<QString>& allCombinations, int32_t depth,
                              int32_t numberOfAlgorithms, int32_t current, QString overlay);
    ImageWriter imgwriter;
};

#endif // MANAGER_H
