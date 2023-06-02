#include "game15.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game15 w;
    w.show();
    return a.exec();
}
