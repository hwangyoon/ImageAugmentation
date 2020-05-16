#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <vector>
#include <QImage>
#include <QString>
#include "../../main/include/request.h"
#include "../../main/include/manager.h"


class GuiController
{
private:
    GlobalRequest request;
    AlgorithmManager manager;

    std::shared_ptr<Request> getRequestFromString(QString name);
public:
    GuiController();
    void makeRequest(QStringList algoList, bool overlay);
    QImage makeRequestPreview(QStringList algoList);
    void savePathIn(QString newPathIn);
    void savePathTo(QString newPathTo);
};

#endif // GUICONTROLLER_H
