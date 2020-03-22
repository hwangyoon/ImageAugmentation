#include <iostream>
#include <string>
#include <QImage>
#include "../include/cropfrommiddle.h"
#include "../include/horizontalflip.h"
#include "../include/rotate90.h"
#include "../include/rotate45.h"
#include "../include/verticalflip.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

enum class Command {
    EXIT,
    LOAD_FILE,
    SAVE_FILE,
    // Тут ещё команды по эффектам...
            EXCEPTION
};

bool is_equal(string command, const string &src) {
    return std::equal(command.begin(), command.begin() + command.size() - 1, src.begin());
}

Command get_command_from(const string &src) {
    string exit_("exit");
    string load_("load ");
    string save_("save ");

    if (is_equal(exit_, src))
        return Command::EXIT;

    if (is_equal(load_, src))
        return Command::LOAD_FILE;

    if (is_equal(save_, src))
        return Command::SAVE_FILE;

    return Command::EXCEPTION;
}

string get_filename_from(const string &src) {
    return src.substr(5);
}

int main() {
    string line;
    string name;
    // TODO: Узнать, что конкретно надо в интерфейсе, и написать это
    QImage img("/home/lizazhemchuzhina/Project/ImageAugmentation/samples/house.jpg");
    const QImage *temp = &img;
    Direction45 d = COUNTERCLOCKWISE45;
    Rotate45 proc(d);
    QImage buf;
    buf=proc.processImage(temp);
    buf.save("/home/lizazhemchuzhina/Project/ImageAugmentation/samples/house_1.jpg");
    while (true) {
        std::getline(cin, line);
        switch (get_command_from(line)) {
            case Command::EXIT :
                return 0;
            case Command::EXCEPTION :
                cout << "Invalid command" << endl;
                break;
            case Command::LOAD_FILE :
                name = get_filename_from(line);
                // Тут команда загрузки Image от name
                break;
            case Command::SAVE_FILE :
                name = get_filename_from(line);
                // Тут команда сохранения Image от name
                break;
        }
    }
}
