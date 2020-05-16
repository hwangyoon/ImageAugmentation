#include "../include/cli.h"

Cli::~Cli() {
    delete disableOption;
    delete configOption;
    delete algorithmsOption;
    delete formatOption;
    delete limitOption;
    delete depthOption;
}

void Cli::process(QCoreApplication& app) {
    /* Description that will be shown with -help option */
    parser.setApplicationDescription("Application options description table");
    parser.addHelpOption();
    parser.addVersionOption();
    addOptions();
    addPositionalArguments();
    parser.process(app);
}

void Cli::addPositionalArguments() {
    /* AddPositionalArgument(name, description) */
    parser.addPositionalArgument("source", "Source file.");
    parser.addPositionalArgument("destination", "Destination directory.");
}

void Cli::addOptions() {
    /* Set disableOption(key(s), description, arguments) */
    disableOption = new QCommandLineOption(QStringList() << "d" << "disable",
                                     "Specify the algorithm which won't be used.",
                                     "algorithm");
    parser.addOption(*disableOption);
    configOption = new QCommandLineOption(QStringList() << "c" << "config",
                                     "Config file",
                                     "file");
    parser.addOption(*configOption);
    algorithmsOption = new QCommandLineOption(QStringList() << "a" << "algorithms",
                                     "Possible algorithms");
    parser.addOption(*algorithmsOption);
    formatOption = new QCommandLineOption(QStringList() << "f" << "format",
                                     "Specify format of output images: png/jpg/gif/bmp/dib",
                                     "format");
    parser.addOption(*formatOption);
    limitOption = new QCommandLineOption(QStringList() << "l" << "limit",
                                     "Specify maximum number of images made (default 25)", "number");
    parser.addOption(*limitOption);
    depthOption = new QCommandLineOption(QStringList() << "o" << "overlay",
                                     "Specify possible depths of overlay (default 1)", "number");
    parser.addOption(*depthOption);
}

bool Cli::processAlgorithmsOption() {
    if (parser.isSet(*algorithmsOption)) {
        /* qPrintable(str) returns str as a const char* */
        fprintf(stdout, "%s\n", qPrintable("crop | hflip | vflip | rotate90 | rotate45 | "
                                           "dithering | gaussnoise | kuwahara | lightening | "
                                           "rgbtone | whiteblack | blur | negative | sharpen | "
                                           "embross | lightblur | lightsharpen | lightembross | "
                                           "gaussblur | randomcrop"));
        return true;
    }
    return false;
}

void Cli::checkPositionalArgumentsCorrectness() {
    /* Get all positionalArguments in a list */
    const QStringList args = parser.positionalArguments();

    if (args.size() != 2) {
        fprintf(stderr, "%s\n", qPrintable("Error: Must specify source file/directory and destination directory."));
        //shows help table and exists application with return code 1
        parser.showHelp(1);
    }

    QFileInfo source(args[0]);
    if (!source.exists()) {
        fprintf(stderr, "%s\n", qPrintable("Error: Invalid source file/directory"));
        parser.showHelp(1);
    }
}

void Cli:: processConfigFile(GlobalRequest& request) {
    QFile file;
    /* Get config file path from configOption value */
    file.setFileName(parser.value(*configOption));
    JsonParser configFileParser;
    try {
        request = configFileParser.getInformationFromConfigFile(file);
    } catch (std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        parser.showHelp(1);
    }
    const QStringList args = parser.positionalArguments();
    request.setLoadDirectoryOrFile(QFileInfo(args[0]));
    request.setSaveDirectory(QFileInfo(args[1]));
    if (parser.isSet(*formatOption)) {
        const QString fileFormat = parser.value(*formatOption);
        request.setFileFormat(fileFormat);
    }
    if (parser.isSet(*depthOption)) {
        /* Get list of all possible numbers of overlay */
        const QStringList depthValues = parser.values(*depthOption);
        std::vector<int32_t> allDepths;
        for (auto depth : depthValues) {
            allDepths.push_back(depth.toInt());
        }
        request.setDepthOfOverlay(allDepths);
    }
}

GlobalRequest Cli::getGlobalRequest() {
    const QStringList args = parser.positionalArguments();

    GlobalRequest request;
    if (parser.isSet(*configOption)) {
        processConfigFile(request);
        return request;
    }
    request.setLoadDirectoryOrFile(QFileInfo(args[0]));
    request.setSaveDirectory(QFileInfo(args[1]));
    if (parser.isSet(*formatOption)) {
        const QString fileFormat = parser.value(*formatOption);
        request.setFileFormat(fileFormat);
    }
    if (parser.isSet(*limitOption)) {
        const QString limit = parser.value(*limitOption);
        request.setLimitOfPictures(limit.toInt());
    }
    if (parser.isSet(*depthOption)) {
        const QStringList depthValues = parser.values(*depthOption);
        std::vector<int32_t> allDepths;
        for (auto depth : depthValues) {
            allDepths.push_back(depth.toInt());
        }
        request.setDepthOfOverlay(allDepths);
    }
    if (!checkDisabledOptionValueCorrectness()) {
        parser.showHelp(1);
    }
    addNotDisabledAlgorithms(request);
    return request;
}

bool Cli::checkDisabledOptionValueCorrectness() {
    /* Get all disabled values in a list */
    const QStringList disabledValues = parser.values(*disableOption);
    for (auto algorithm : disabledValues) {
        /* Make sure user provided correct algorithm name that will be disabled */
        if (algoNames.find(algorithm) == algoNames.end()) {
            fprintf(stderr, "%s\n", qPrintable("Wrong option value " + algorithm));
            return false;
        }
    }
    return true;
}

void Cli::addNotDisabledAlgorithms(GlobalRequest& request) {
    const QStringList disabledValues = parser.values(*disableOption);
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
        request.addRequest(std::make_shared<GaussianNoiseRequest>(40, true));
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
        request.addRequest(std::make_shared<Rotate90Request>(CLOCKWISE90));
        request.addRequest(std::make_shared<Rotate90Request>(COUNTERCLOCKWISE90));
    }
    if (!disabledValues.contains("rotate45")) {
        request.addRequest(std::make_shared<Rotate45Request>(CLOCKWISE45));
        request.addRequest(std::make_shared<Rotate45Request>(COUNTERCLOCKWISE45));
    }
    if (!disabledValues.contains("lightening")) {
        request.addRequest(std::make_shared<LighteningRequest>());
    }
    if (!disabledValues.contains("blur")) {
        request.addRequest(std::make_shared<BlurConvolutionRequest>());
    }
    if (!disabledValues.contains("negative")) {
        request.addRequest(std::make_shared<NegativeConvolutionRequest>());
    }
    if (!disabledValues.contains("sharpen")) {
        request.addRequest(std::make_shared<SharpenConvolutionRequest>());
    }
    if (!disabledValues.contains("embross")) {
        request.addRequest(std::make_shared<EmbrossConvolutionRequest>());
    }
    if (!disabledValues.contains("lightblur")) {
        request.addRequest(std::make_shared<LightBlurConvolutionRequest>());
    }
    if (!disabledValues.contains("lightsharpen")) {
        request.addRequest(std::make_shared<LightSharpenConvolutionRequest>());
    }
    if (!disabledValues.contains("lightembross")) {
        request.addRequest(std::make_shared<LightEmbrossConvolutionRequest>());
    }
    if (!disabledValues.contains("gausselur")) {
        request.addRequest(std::make_shared<GaussBlurConvolutionRequest>());
    }
    if (!disabledValues.contains("randomcrop")) {
        request.addRequest(std::make_shared<RandomCropRequest>());
    }
    if (!disabledValues.contains("rgbtone")) {
        request.addRequest(std::make_shared<RGBToneRequest>(50, RED));
        request.addRequest(std::make_shared<RGBToneRequest>(50, GREEN));
        request.addRequest(std::make_shared<RGBToneRequest>(50, BLUE));
    }
}
