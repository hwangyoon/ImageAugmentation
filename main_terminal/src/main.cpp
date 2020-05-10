#include <iostream>
#include <QTextStream>
#include "main/include/cli.h"
#include "main/include/manager.h"

QTextStream cout(stdout);
QTextStream cin(stdin);

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("ImageAugmentation");
    QCoreApplication::setApplicationVersion("1.0");

    Cli parser;
    parser.process(app);
    if (parser.processAlgorithmsOption()) {
        return 0;
    }
    parser.checkPositionalArgumentsCorrectness();

    GlobalRequest request = parser.getGlobalRequest();

    AlgorithmManager manager;
    manager.processRequests(request);
    return 0;
}

