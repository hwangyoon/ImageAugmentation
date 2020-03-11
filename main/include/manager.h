#ifndef MANAGER_H
#define MANAGER_H
#include <QImage>
#include <QString>
#include "factory.h"

<<<<<<< HEAD
class AlgorithmManager {
public:
    AlgorithmManager() = default;
    //takes vector of requests for a single picture, one request == one algorithm
    void process_requests(std::vector<Request*>& r, QString path_from, QString path_to);
private:
    Factory f;
=======
class manager
{
public:
    manager() = default;
    //takes vector of requests for a single picture, one request == one algorithm
    void process_requests(std::vector<Request*>& r, QString path_from, QString path_to);
private:
    factory f;
>>>>>>> b12925ec1e8740785930234c87e00b42fe562cbe
};

#endif // MANAGER_H
