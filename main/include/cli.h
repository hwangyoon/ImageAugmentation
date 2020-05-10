#ifndef CLI_H
#define CLI_H
#include <QCommandLineParser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "request.h"
#include "jsonfileparser.h"
#include "configfileexceptions.h"

class Cli {
public:
    Cli() {}
    ~Cli();
    void process(QCoreApplication& app);
    bool processAlgorithmsOption();
    void checkPositionalArgumentsCorrectness();
    GlobalRequest getGlobalRequest();
private:
    QCommandLineParser parser;
    QCommandLineOption* disableOption;
    QCommandLineOption* configOption;
    QCommandLineOption* algorithmsOption;
    QCommandLineOption* formatOption;
    QCommandLineOption* limitOption;
    QCommandLineOption* depthOption;
    void addOptions();
    void addPositionalArguments();
    bool checkDisabledOptionValueCorrectness();
    void addNotDisabledAlgorithms(GlobalRequest& request);
    void processConfigFile(GlobalRequest& request);
    std::set<QString> algoNames{"crop", "dithering", "kuwahara",
                                "gaussnoise", "hflip", "vflip",
                                "whiteblack", "rotate90", "lightening",
                                "rgbtone", "rotate45", "blur", "negative",
                                "sharpen", "embross", "lightblur", "lightsharpen",
                                "lightembross", "gaussblur", "randomcrop"};
};

#endif // CLI_H
