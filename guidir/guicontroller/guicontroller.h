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
    std::vector<Request*> request_list;
    AlgorithmManager manager;
    QString path_in;
public:
    GuiController();
    QImage make_request(QStringList algo_list);
    QImage make_request_preview(QStringList algo_list);
    void save_path_in(QString new_path_in);
};

#endif // GUICONTROLLER_H
