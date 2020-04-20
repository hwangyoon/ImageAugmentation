#include <iostream>
#include <string>
#include <QImage>
#include <QString>
#include <QTextStream>
#include <QCommandLineParser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("ImageAugmentation");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;

    //description that will be shown with -help option
    parser.setApplicationDescription("Application options description table");
    parser.addHelpOption();
    parser.addVersionOption();

    //addPositionalArgument(name, description)
    parser.addPositionalArgument("source", "Source file.");
    parser.addPositionalArgument("destination", "Destination directory.");

    //disableOption(key(s), description, arguments)
    QCommandLineOption disableOption(QStringList() << "d" << "disable",
                                     "Specify the algorithm which won't be used.",
                                     "algorithm");
    parser.addOption(disableOption);
    QCommandLineOption configOption(QStringList() << "c" << "config",
                                     "Config file",
                                     "file");
    parser.addOption(configOption);
    QCommandLineOption algorithmsOption(QStringList() << "a" << "algorithms",
                                     "Possible algorithms");
    parser.addOption(algorithmsOption);
    QCommandLineOption formatOption(QStringList() << "f" << "format",
                                     "Specify format.",
                                     "format");
    parser.addOption(formatOption);
    parser.process(app);

    //check if such option was given
    if (parser.isSet(algorithmsOption)) {
        //qPrintable(str) returns str as a const char*
        fprintf(stdout, "%s\n", qPrintable("crop | hflip | vflip | rotate90 | rotate45 |"
                                           "dithering | gaussnoise | kuwahara | lightening |"
                                           "rgbtone | whiteblack"));
        return 0;
    }

    //get all positionalArguments in a list
    const QStringList args = parser.positionalArguments();
    if (args.size() != 2) {
        fprintf(stderr, "%s\n", qPrintable("Error: Must specify source file and destination directory."));
        //displays the help information, and exits the application with exit code 1
        parser.showHelp(1);
    }

    QFile source(args[0]);
    if (!source.exists()) {
        fprintf(stderr, "%s\n", qPrintable("Error: Invalid source file."));
        parser.showHelp(1);
    }

    QDir destination(args[1]);
    if (!destination.exists()) {
        fprintf(stderr, "%s\n", qPrintable("Error: Invalid destination directory."));
        parser.showHelp(1);
    }

    GlobalRequest request(args[0], args[1]);
    if (parser.isSet(configOption)) {
        QFile file;
        file.setFileName(parser.value(configOption));
        if (!file.exists()){
            fprintf(stderr, "%s\n", qPrintable("File not found."));
            file.close();
            parser.showHelp(1);
        }
        QFileDevice::FileError err = QFileDevice::NoError;
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            fprintf(stderr, "%s", qPrintable("Could not open file for reading: "));
            err = file.error();
            fprintf(stderr, "%s\n", qPrintable(QString(err)));
            file.close();
            parser.showHelp(1);
        }
        QString settings = file.readAll();
        if (file.error() != QFile::NoError) {
            fprintf(stderr, "%s\n", qPrintable("Failed to read from file"));
            file.close();
            parser.showHelp(1);
        }
        if (settings.isEmpty()) {
            fprintf(stderr, "%s\n", qPrintable("No data was currently available for reading from file"));
        }
        file.close();
        QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
        QJsonObject sett2 = sd.object();
        if (sett2.contains("rotate90")) {
            if (sett2.value("rotate90").toString() == "CLOCKWISE90")
                request.add_request(std::make_shared<Rotate90Request>(CLOCKWISE90));
            else
                request.add_request(std::make_shared<Rotate90Request>(COUNTERCLOCKWISE90));
        }
        if (sett2.contains("rotate45")) {
            if (sett2.value("rotate45").toString() == "CLOCKWISE45")
                request.add_request(std::make_shared<Rotate45Request>(CLOCKWISE45));
            else
                request.add_request(std::make_shared<Rotate45Request>(COUNTERCLOCKWISE45));
        }
        if (sett2.contains("crop")) {
            QJsonValue value = sett2.value("crop");
            QJsonArray array = value.toArray();
            int x = array.at(0).toInt();
            int y = array.at(1).toInt();
            int cols = array.at(2).toInt();
            int rows = array.at(3).toInt();
            request.add_request(std::make_shared<CropRequest>(x, y, cols, rows));
        }
        if (sett2.contains("gaussiannoise")) {
            QJsonValue value = sett2.value("gaussiannoise");
            QJsonArray array = value.toArray();
            int32_t degree = array.at(0).toInt();
            bool mono = array.at(1).toBool();
            request.add_request(std::make_shared<GaussianNoiseRequest>(degree, mono));
        }
        if (sett2.contains("rgbtone")) {
            QJsonValue value = sett2.value("rgbtone");
            QJsonArray array = value.toArray();
            int32_t degree = array.at(0).toInt();
            Color color;
            if (array.at(1).toString() == "RED") {
                color = RED;
            }
            if (array.at(1).toString() == "GREEN") {
                color = GREEN;
            }
            if (array.at(1).toString() == "BLUE") {
                color = BLUE;
            }
            request.add_request(std::make_shared<RGBToneRequest>(degree, color));
        }
        if (sett2.contains("kuwahara")) {
            QJsonValue value = sett2.value("kuwahara");
            QJsonArray array = value.toArray();
            int32_t degreeOfBlur = array.at(0).toInt();
            request.add_request(std::make_shared<KuwaharaRequest>(degreeOfBlur));
        }
        if (sett2.contains("lightening")) {
            QJsonValue value = sett2.value("lightening");
            QJsonArray array = value.toArray();
            int32_t degreeOfLightening = array.at(0).toInt();
            request.add_request(std::make_shared<LighteningRequest>(degreeOfLightening));
        }
        if (sett2.contains("enable")) {
            QJsonValue value = sett2.value("enable");
            QJsonArray array = value.toArray();
            for (auto algo : array) {
                if (algo.toString() == "hflip") {
                    request.add_request(std::make_shared<FlipHRequest>());
                }
                if (algo.toString() == "vflip") {
                    request.add_request(std::make_shared<FlipVRequest>());
                }
                if (algo.toString() == "dithering") {
                    request.add_request(std::make_shared<DitheringRequest>());
                }
                if (algo.toString() == "whiteblack") {
                    request.add_request(std::make_shared<WhiteBlackRequest>());
                }
            }
        }
        AlgorithmManager m;
        m.process_requests(request);
        return 0;
    }

    const QStringList disabledValues = parser.values(disableOption);
    if (parser.isSet(formatOption)) {
        const QString fileFormat = parser.value(formatOption);
        request.setFileFomat(fileFormat);
    }
    for (auto algorithm : disabledValues) {
        if (algorithm != "crop" && algorithm != "dithering" && algorithm != "kuwahara" &&
            algorithm != "gaussnoise" && algorithm != "hflip" && algorithm != "vflip" &&
            algorithm != "whiteblack" && algorithm != "rotate90" && algorithm != "lightening" &&
            algorithm != "rgbtone") {
            fprintf(stderr, "%s\n", qPrintable("Wrong option value"));
            parser.showHelp(1);
        }
    }
    if (!disabledValues.contains("crop")) {
        request.add_request(std::make_shared<CropRequest>());
    }
    if (!disabledValues.contains("dithering")) {
        request.add_request(std::make_shared<DitheringRequest>());
    }
    if (!disabledValues.contains("kuwahara")) {
        request.add_request(std::make_shared<KuwaharaRequest>());
    }
    if (!disabledValues.contains("gaussnoise")) {
        request.add_request(std::make_shared<GaussianNoiseRequest>());
    }
    if (!disabledValues.contains("hflip")) {
        request.add_request(std::make_shared<FlipHRequest>());
    }
    if (!disabledValues.contains("vflip")) {
        request.add_request(std::make_shared<FlipVRequest>());
    }
    if (!disabledValues.contains("whiteblack")) {
        request.add_request(std::make_shared<WhiteBlackRequest>());
    }
    if (!disabledValues.contains("rotate90")) {
        request.add_request(std::make_shared<Rotate90Request>());
    }
    if (!disabledValues.contains("rotate45")) {
        request.add_request(std::make_shared<Rotate45Request>());
    }
    if (!disabledValues.contains("lightening")) {
        request.add_request(std::make_shared<LighteningRequest>());
    }
    if (!disabledValues.contains("rgbtone")) {
        request.add_request(std::make_shared<RGBToneRequest>());
    }
    AlgorithmManager m;
    m.process_requests(request);
    return 0;
}

