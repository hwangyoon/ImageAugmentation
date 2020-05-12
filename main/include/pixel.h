#ifndef PIXEL_H
#define PIXEL_H

#include <QRgb>

/*auxiliary structure, which implements a number of obvious operators
 *  for each component from the RGB vector*/
struct Pixel {
    long long red = 0;
    long long green = 0;
    long long blue = 0;

    Pixel() = default;

    Pixel(int red, int green, int blue)
            : red(red), green(green), blue(blue) {}

    Pixel(long long red, long long green, long long blue)
            : red(red), green(green), blue(blue) {}

    Pixel(double red, double green, double blue)
            : red(red), green(green), blue(blue) {}

    explicit Pixel(QRgb colour)
            : red(qRed(colour)), green(qGreen(colour)), blue(qBlue(colour)) {}

    Pixel(int power, bool mono);

    Pixel& operator+=(const Pixel& other) {
        red += other.red;
        green += other.green;
        blue += other.blue;
        return *this;
    }

    Pixel& operator-=(const Pixel& other) {
        red -= other.red;
        green -= other.green;
        blue -= other.blue;
        return *this;
    }

    template<class T>
    Pixel& operator/=(T x) {
        red /= x;
        green /= x;
        blue /= x;
        return *this;
    }

    template<class T>
    Pixel& operator*=(T x) {
        red *= x;
        green *= x;
        blue *= x;
        return *this;
    }

    Pixel powSquare(const Pixel& other) {
        red += other.red * other.red;
        green += other.green * other.green;
        blue += other.blue * other.blue;
        return *this;
    }

    Pixel operator-(Pixel other) const {
        return Pixel(red - other.red, green - other.green, blue - other.blue);
    }

    template<class T>
    Pixel operator*(T x) const {
        return Pixel(red * x, green * x, blue * x);
    }

    template<class T>
    Pixel operator/(T x) const {
        return Pixel(red / x, green / x, blue / x);
    }

    Pixel operator>>(int x) const {
        return Pixel(red >> x, green >> x, blue >> x);
    }

    Pixel getSquare() const {
        return Pixel(red * red, green * green, blue * blue);
    }

    QRgb getRgb() {
        if (red > 255)
            red = 255;
        if (red < 0)
            red = 0;

        if (green > 255)
            green = 255;
        if (green < 0)
            green = 0;

        if (blue > 255)
            blue = 255;
        if (blue < 0)
            blue = 0;

        return qRgb(red, green, blue);
    }

    QRgb getRgbWithoutShift() const {
        return qRgb(red, green, blue);
    }

    long long getSum() const {
        return red + green + blue;
    }

    Pixel round() const {
        int redRound, greenRound, blueRound;
        if (255 - red > red) {
            redRound = 0;
        }
        else {
            redRound = 255;
        }

        if (255 - green > green) {
            greenRound = 0;
        }
        else {
            greenRound = 255;
        }
        if (255 - blue > blue) {
            blueRound = 0;
        }
        else {
            blueRound = 255;
        }
        return Pixel(redRound, greenRound, blueRound);
    }

};

#endif // PIXEL_H
