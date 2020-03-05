#ifndef MANAGER_H
#define MANAGER_H
#include <QImage>
#include <QString>
#include "factory.h"

class manager
{
public:
    manager() = default;
    void process_requests(std::vector<Request*>& r, QString path_from, QString path_to);
private:
    factory f;
};

#endif // MANAGER_H
