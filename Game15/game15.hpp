#ifndef GAME15_HPP
#define GAME15_HPP

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Game15; }
QT_END_NAMESPACE

class Game15 : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Game15 *ui;
    int m_dimension;

public:
    Game15(int dimension, QWidget *parent = nullptr);
    ~Game15();
};
#endif // GAME15_HPP
