#ifndef CONFIGFILEEXCEPTIONS_H
#define CONFIGFILEEXCEPTIONS_H

#include <exception>
#include <QString>

/* A base abstract class for possible exceptions that happen during parsing of config file */
class ConfigFileException : public std::exception {
protected:
    const char* message = "Unexpected error with config file";
public:
    virtual const char* what() const noexcept {
        return message;
    }
};

/* User provided file that does not exist */
class FileNotFoundException : public ConfigFileException {
public:
    FileNotFoundException() { message = "Error: config file not found"; }
};

/* User provided file that can not be parsed */
class FileNotReadableException : public ConfigFileException {
public:
    FileNotReadableException() { message = "Error: unable to read file"; }
    FileNotReadableException(QString error) { message = qPrintable("Error: unable to read file: " + error); }
};

/* User provided empty file */
class EmptyFileException : public ConfigFileException {
public:
    EmptyFileException() {
        message = "Error: no data is currently available for reading from file";
    }
};

/* User included an algorithm, but did not provide all the needed information for that algorithm */
class KeyNotGivenException : public ConfigFileException {
public:
    KeyNotGivenException() { message = "Error: key was not provided"; }
    KeyNotGivenException(QString key) { message = qPrintable("Error: key "+ key + " is not provided"); }
};

/* User included an algorithm, but provided more(or less) arguments needed for that algorithm */
class WrongNumberOfArgumentsException : public ConfigFileException {
public:
    WrongNumberOfArgumentsException() { message = "Error: wrong number of arguments provided"; }
    WrongNumberOfArgumentsException(QString key) {
        message = qPrintable("Error: wrong number of arguments provided in " + key);
    }
};

/* User included an algorithm that does not exist */
class UnrecognisedKeyException : public ConfigFileException {
public:
    UnrecognisedKeyException() { message = "Error: unrecognised key"; }
    UnrecognisedKeyException(QString key) { message = qPrintable("Error: unrecognised key " + key); }
};

#endif // CONFIGFILEEXCEPTIONS_H
