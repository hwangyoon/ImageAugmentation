#include <iostream>
#include <set>
#include <cassert>
#include <QImage>
#include <QString>
#include <QTextStream>
#include <QCommandLineParser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "main/include/jsonfileparser.h"
#include "main/include/configfileexceptions.h"
#include "main/include/cropfrommiddle.h"
#include "main/include/horizontalflip.h"
#include "main/include/rotate90.h"
#include "main/include/rotate45.h"
#include "main/include/verticalflip.h"
#include "main/include/request.h"
#include "main/include/manager.h"
#include "main/include/dithering.h"
#include "main/include/kuwahara.h"
#include "main/include/rgbtone.h"
#include <memory>

QTextStream cout(stdout);
QTextStream cin(stdin);

std::set<QString> algoNames{"crop", "dithering", "kuwahara",
                            "gaussnoise", "hflip", "vflip",
                            "whiteblack", "rotate90", "lightening",
                            "rgbtone", "rotate45", "convolution"};

bool checkPositionalArgumentsCorrectness(const QCommandLineParser& parser) {
    //get all positionalArguments in a list
    const QStringList args = parser.positionalArguments();

    if (args.size() != 2) {
        fprintf(stderr, "%s\n", qPrintable("Error: Must specify source file/directory and destination directory."));
        return false;
    }

    QFileInfo source(args[0]);
    if (!source.exists()) {
        fprintf(stderr, "%s\n", qPrintable("Error: Invalid source file/directory"));
        return false;
    }
    return true;
}

bool checkDisabledOptionValueCorrectness(const QCommandLineParser& parser) {
    QCommandLineOption disableOption(QStringList() << "d" << "disable",
                                     "Specify the algorithm which won't be used.",
                                     "algorithm");
    const QStringList disabledValues = parser.values(disableOption);
    for (auto algorithm : disabledValues) {
        if (algoNames.find(algorithm) == algoNames.end()) {
            fprintf(stderr, "%s\n", qPrintable("Wrong option value"));
            return false;
        }
    }
    return true;
}

void addNotDisabledAlgorithms(const QCommandLineParser& parser, GlobalRequest& request) {
    QCommandLineOption disableOption(QStringList() << "d" << "disable",
                                     "Specify the algorithm which won't be used.",
                                     "algorithm");
    const QStringList disabledValues = parser.values(disableOption);
    if (!disabledValues.contains("crop")) {
        request.addRequest(std::make_shared<CropRequest>());
    }
    if (!disabledValues.contains("dithering")) {
        request.addRequest(std::make_shared<DitheringRequest>());
    }
    if (!disabledValues.contains("kuwahara")) {
        request.addRequest(std::make_shared<KuwaharaRequest>());
    }
    if (!disabledValues.contains("gaussnoise")) {
        request.addRequest(std::make_shared<GaussianNoiseRequest>());
    }
    if (!disabledValues.contains("hflip")) {
        request.addRequest(std::make_shared<FlipHRequest>());
    }
    if (!disabledValues.contains("vflip")) {
        request.addRequest(std::make_shared<FlipVRequest>());
    }
    if (!disabledValues.contains("whiteblack")) {
        request.addRequest(std::make_shared<WhiteBlackRequest>());
    }
    if (!disabledValues.contains("rotate90")) {
        request.addRequest(std::make_shared<Rotate90Request>());
    }
    if (!disabledValues.contains("rotate45")) {
        request.addRequest(std::make_shared<Rotate45Request>());
    }
    if (!disabledValues.contains("lightening")) {
        request.addRequest(std::make_shared<LighteningRequest>());
    }
    if (!disabledValues.contains("rgbtone")) {
        request.addRequest(std::make_shared<RGBToneRequest>());
    }
    if (!disabledValues.contains("convolution")) {
        request.addRequest(std::make_shared<MatrixConvolutionRequest>());
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("ImageAugmentation");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;

    //description that will be shown with -help option
    parser.setApplicationDescription("Application options description table");
    parser.addHelpOption();
    parser.addVersionOption();

    //set disableOption(key(s), description, arguments)
    QCommandLineOption disableOption(QStringList() << "d" << "disable",
                                     "Specify the algorithm which won't be used.",
                                     "algorithm");
    parser.addOption(disableOption);
    //set config file option
    QCommandLineOption configOption(QStringList() << "c" << "config",
                                     "Config file",
                                     "file");
    parser.addOption(configOption);
    //set option that shows names of all possible algorithms
    QCommandLineOption algorithmsOption(QStringList() << "a" << "algorithms",
                                     "Possible algorithms");
    parser.addOption(algorithmsOption);
    //set option that will allow user to define format of output file
    QCommandLineOption formatOption(QStringList() << "f" << "format",
                                     "Specify format of output images: png/jpg/gif/bmp/dib",
                                     "format");
    parser.addOption(formatOption);

    //addPositionalArgument(name, description)
    parser.addPositionalArgument("source", "Source file.");
    parser.addPositionalArgument("destination", "Destination directory.");

    parser.process(app);

    //check if such option was given
    if (parser.isSet(algorithmsOption)) {
        //qPrintable(str) returns str as a const char*
        fprintf(stdout, "%s\n", qPrintable("crop | hflip | vflip | rotate90 | rotate45 |"
                                           "dithering | gaussnoise | kuwahara | lightening |"
                                           "rgbtone | whiteblack | convolution"));
        return 0;
    }

    if (!checkPositionalArgumentsCorrectness(parser)) {
        //displays the help information, and exits the application with exit code 1
        parser.showHelp(1);
    }

    const QStringList args = parser.positionalArguments();

    GlobalRequest request;
    if (parser.isSet(configOption)) {
        QFile file;
        file.setFileName(parser.value(configOption));
        JsonParser configFileParser;
        try {
            request = configFileParser.getInformationFromConfigFile(file);
        } catch (std::exception& e) {
            fprintf(stderr, "%s\n", e.what());
            parser.showHelp(1);
        }
        request.setLoadDirectoryOrFile(QFileInfo(args[0]));
        request.setSaveDirectory(QFileInfo(args[1]));
        if (parser.isSet(formatOption)) {
            const QString fileFormat = parser.value(formatOption);
            request.setFileFormat(fileFormat);
        }
        AlgorithmManager m;
        m.processRequests(request);
        return 0;
    }

    request.setLoadDirectoryOrFile(QFileInfo(args[0]));
    request.setSaveDirectory(QFileInfo(args[1]));
    if (parser.isSet(formatOption)) {
        const QString fileFormat = parser.value(formatOption);
        request.setFileFormat(fileFormat);
    }
    if (!checkDisabledOptionValueCorrectness(parser)) {
        parser.showHelp(1);
    }
    addNotDisabledAlgorithms(parser, request);
    AlgorithmManager m;
    m.processRequests(request);
    return 0;
}

