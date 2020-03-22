#include <iostream>
#include <string>
#include <QImage>
#include <QString>
#include <QTextStream>
#include "main/include/cropfrommiddle.h"
#include "main/include/horizontalflip.h"
//#include "main/include/rotate90clockwise.h"
#include "main/include/verticalflip.h"
#include "main/include/request.h"
#include "main/include/manager.h"

QTextStream cout(stdout);
QTextStream cin(stdin);

int main() {
    // to do https://www.boost.org/doc/libs/1_72_0/doc/html/program_options.html
    QString command; // algorithm which will be used: crop/hflip/vflip/rot
    QString path_from; // file path the image is loaded from
    QString path_to; // file name the image is saved from
    AlgorithmManager m; //~interpretator
    cin >> command >> path_from >> path_to;
    if (command == "crop") {
        int x, y, cols, rows;
        cin >> x >> y >> cols >> rows;
        CropRequest r(x, y, cols, rows);
        std::vector<Request*> req;
        req.push_back(&r);
        m.process_requests(req, path_from, path_to);
    } else if (command == "hflip") {
        FlipHRequest r;
        std::vector<Request*> req;
        req.push_back(&r);
        m.process_requests(req, path_from, path_to);
    } else if (command == "vflip") {
        FlipVRequest r;
        std::vector<Request*> req;
        req.push_back(&r);
        m.process_requests(req, path_from, path_to);
     } else if (command == "rot") {
        RotateRequest r;
        std::vector<Request*> req;
        req.push_back(&r);
        m.process_requests(req, path_from, path_to);
    }
}

