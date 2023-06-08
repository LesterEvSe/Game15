#ifndef GAME15_HPP
#define GAME15_HPP

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <memory> // for unique_ptr

class Game15 : public QWidget
{
    Q_OBJECT

private:
    int m_dimension;
    std::unique_ptr<QGridLayout> m_grid_layout;

public:
    Game15(int dimension, QWidget *parent = nullptr);
    ~Game15() = default;
};
#endif // GAME15_HPP
