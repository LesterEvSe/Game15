#include "menu.hpp"
#include "game.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu menu;
    int start_game = menu.exec();
    if (!start_game) return 0;

    Game window(start_game);
    return a.exec();
}
