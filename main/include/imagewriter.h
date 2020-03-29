#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include <QDir>
#include <memory>
#include <QImage>

class ImageWriter {
public:
    ImageWriter() { srand(time(NULL)); }
    void save_to_directory(QDir path_to_, std::vector<std::shared_ptr<QImage>> images, QString format = ".jpg");
    void save_to_file(QDir path_to, QImage& img);
private:
    QString generate_string(std::size_t n);
};

#endif // IMAGEWRITER_H
