#include "game15.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int start_game = 4;
    if (!start_game) return 0;

    Game15 window(start_game);
    window.show();
    return a.exec();
}