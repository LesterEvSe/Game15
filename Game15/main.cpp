#include "choose.hpp"
#include "game15.hpp"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Choose choose;
    int start_game = choose.exec();

    if (!start_game) return 0;
    Game15 window(start_game);
    window.show();
    return a.exec();
}
