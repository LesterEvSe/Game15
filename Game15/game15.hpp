#ifndef GAME15_HPP
#define GAME15_HPP

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>

#include <memory> // for unique_ptr

class Game15 : public QWidget
{
    Q_OBJECT

private:
    int m_dimension;
    QPair<int, int> m_zero_pos {3, 3};
    std::unique_ptr<QGridLayout> m_grid_layout;

    bool move_to(int row, int col);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    Game15(int dimension, QWidget *parent = nullptr);
    ~Game15();
};
#endif // GAME15_HPP
