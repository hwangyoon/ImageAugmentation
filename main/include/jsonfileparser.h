#ifndef JSONFILEPARSER_H
#define JSONFILEPARSER_H

#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include "request.h"
#include "configfileexceptions.h"
class JsonParser {
public:
    JsonParser() = default;
    //get GlobalRequest from given configuration file
    //throws exception if file or format is invalid
    GlobalRequest getInformationFromConfigFile(QFile& file);
private:
    void checkConfigFileCorrect(QFile& file) const;
    QJsonValue getValue(const QJsonObject& data, const QString& key);
};

#endif // JSONFILEPARSER_H
