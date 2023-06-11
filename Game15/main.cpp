#include "menu.hpp"
#include "gameui.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu menu;
    int start_game = menu.exec();
    if (!start_game) return 0;

    GameUi window(start_game);
    window.show();
    return a.exec();
}
