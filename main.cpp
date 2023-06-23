#include "menu.hpp"
#include "game.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<Menu> menu = std::make_unique<Menu>();
    int start_game = menu->exec();
    if (!start_game) return 0;

    std::unique_ptr<Game> window = std::make_unique<Game>(start_game);
    return a.exec();
}
