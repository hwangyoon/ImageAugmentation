#include <iostream>
#include <string>
#include <QImage>
#include <QString>
#include <QTextStream>
#include "main/include/cropfrommiddle.h"
#include "main/include/horizontalflip.h"
#include "main/include/rotate90.h"
#include "main/include/rotate45.h"
#include "main/include/verticalflip.h"
#include "main/include/request.h"
#include "main/include/manager.h"
#include <memory>

QTextStream cout(stdout);
QTextStream cin(stdin);

int main() {
    // to do https://www.boost.org/doc/libs/1_72_0/doc/html/program_options.html
    QString command; // algorithm which will be used: crop/hflip/vflip/rot
    QString path_from; // file path the image is loaded from
    QString path_to; // file name the image is saved from
    AlgorithmManager m; //~interpretator
    cin >> path_from >> path_to;
    GlobalRequest request(path_from, path_to);
    while (true) {
        cin >> command;
        if (command == "crop") {
            int x, y, cols, rows;
            cin >> x >> y >> cols >> rows;
            request.add_request(std::make_shared<CropRequest>(x, y, cols, rows));
        } else if (command == "hflip") {
            request.add_request(std::make_shared<FlipHRequest>());
        } else if (command == "vflip") {
            request.add_request(std::make_shared<FlipVRequest>());
        } else if (command == "rot90") {
            request.add_request(std::make_shared<Rotate90Request>());
        } else if (command == "rot45") {
            request.add_request(std::make_shared<Rotate45Request>());
        } else if (command == "exit") {
            m.process_requests(request);
            break;
        }
    }
    return 0;
}

