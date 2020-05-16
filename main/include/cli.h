#ifndef CLI_H
#define CLI_H
#include <QCommandLineParser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "request.h"
#include "jsonfileparser.h"
#include "configfileexceptions.h"

/*A class that parses command line in console application*/

class Cli {
public:
    Cli() {}
    ~Cli();
    /* adds application description, options and positional variables */
    void process(QCoreApplication& app);
    /* returns false if AlgorithmOption was not given
     * returns true and processes the option if given */
    bool processAlgorithmsOption();
    /* verifies number of arguments
     * verifies source file/directory exists */
    void checkPositionalArgumentsCorrectness();
    /* returns GlobalRequest object filled in accordance with user's request */
    GlobalRequest getGlobalRequest();
private:
    QCommandLineParser parser;
    /* Option that specifies the algorithm which won't be used */
    QCommandLineOption* disableOption;
    /* Option that allows user to provide config file */
    QCommandLineOption* configOption;
    /* Option that shows names of all possible algorithms */
    QCommandLineOption* algorithmsOption;
    /* Option that allows user to define format of output file */
    QCommandLineOption* formatOption;
    /* Option that allows user to define maximum number of images made */
    QCommandLineOption* limitOption;
    /* Option that allows user to define possible depths of overlay */
    QCommandLineOption* depthOption;
    /* The method that sets all options */
    void addOptions();
    /* The methos that sets source file/directory
     *  and destination directory as positional arguments */
    void addPositionalArguments();
    /* Verify user provided correct algorithm names
     * returns true if all algorithms names are correct
     * returns false otherwise */
    bool checkDisabledOptionValueCorrectness();
    /* Add algorithms that were not disabled by user to GlobalRequest object */
    void addNotDisabledAlgorithms(GlobalRequest& request);
    /* Fill GlobalRequest object with information provided by user in congin file
     * throws exception if parsing of config file was not possible */
    void processConfigFile(GlobalRequest& request);
    /* All possible algorithm names
     * used in the checkDisabledOptionValueCorrectness method */
    std::set<QString> algoNames{"crop", "dithering", "kuwahara",
                                "gaussnoise", "hflip", "vflip",
                                "whiteblack", "rotate90", "lightening",
                                "rgbtone", "rotate45", "blur", "negative",
                                "sharpen", "embross", "lightblur", "lightsharpen",
                                "lightembross", "gaussblur", "randomcrop"};
};

#endif // CLI_H
