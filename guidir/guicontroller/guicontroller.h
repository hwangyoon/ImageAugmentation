#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <vector>
#include <QImage>
#include <QString>
#include "../../main/include/request.h"
#include "../../main/include/manager.h"


class GuiController {
private:
    GlobalRequest request;
    AlgorithmManager manager;

    std::shared_ptr<Request> getRequestFromString(QString name);
public:
    GuiController();
    /* Make request from string list */
    void makeRequest(QStringList algoList, bool overlay);
    /*Make request from string list and return preview*/
    QImage makeRequestPreview(QStringList algoList);
    /*Save picture source path*/
    void savePathIn(QString newPathIn);
    /*Save picture result path*/
    void savePathTo(QString newPathTo);
};

#endif // GUICONTROLLER_H
