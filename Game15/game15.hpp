#ifndef GAME15_HPP
#define GAME15_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Game15; }
QT_END_NAMESPACE

class Game15 : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Game15 *ui;

public:
    Game15(QWidget *parent = nullptr);
    ~Game15();
};
#endif // GAME15_HPP
