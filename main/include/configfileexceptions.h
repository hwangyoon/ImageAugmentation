#ifndef CONFIGFILEEXCEPTIONS_H
#define CONFIGFILEEXCEPTIONS_H

#include <exception>
#include <QString>

class configFileException : public std::exception {
protected:
    const char* message = "Unexpected error with config file";
public:
    virtual const char* what() const noexcept {
        return message;
    }
};

class fileNotFoundException : public configFileException {
public:
    fileNotFoundException() { message = "Error: source file/directory not found"; }
};

class fileNotReadableException : public configFileException {
public:
    fileNotReadableException() { message = "Error: unable to read file"; }
    fileNotReadableException(QString error) { message = qPrintable("Error: unable to read file: " + error); }
};

class emptyFileException : public configFileException {
public:
    emptyFileException() {
        message = "Error: no data is currently available for reading from file";
    }
};

class keyNotGivenException : public configFileException {
public:
    keyNotGivenException() { message = "Error: key was not provided"; }
    keyNotGivenException(QString key) { message = qPrintable("Error: key "+ key + " is not provided"); }
};

class wrongNumberOfArgumentsException : public configFileException {
public:
    wrongNumberOfArgumentsException() { message = "Error: wrong number of arguments provided"; }
    wrongNumberOfArgumentsException(QString key) {
        message = qPrintable("Error: wrong number of arguments provided in " + key);
    }
};

class wrongValueException : public configFileException {
public:
    wrongValueException() { message = "Error: wrong value"; }
    wrongValueException(QString key) { message = qPrintable("Error: wrong value for key " + key); }
};

class unrecognisedKeyException : public configFileException {
public:
    unrecognisedKeyException() { message = "Error: unrecognised key"; }
    unrecognisedKeyException(QString key) { message = qPrintable("Error: unrecognised key " + key); }
};
#endif // CONFIGFILEEXCEPTIONS_H
