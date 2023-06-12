#ifndef GAME_HPP
#define GAME_HPP

#include "solver.hpp"

#include <QWidget>
#include <QStackedWidget>

#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>

#include <memory>

namespace Ui { class Game; }
class Game : public QWidget
{
    Q_OBJECT

private:
    Ui::Game *ui;
    QWidget *m_game_widget;
    QWidget *m_pause_widget;
    QGridLayout *m_grid_layout;

    int m_dimension;
    std::unique_ptr<Solver> m_solver;

    unsigned int m_time_ms;
    QTimer m_timer;
    QPair<int, int> m_zero_pos;

    static bool block_keyboard;

    bool move_to(int row, int col);
    void set_grid();
    void set_styles();
    void set_timer();

private slots:
    void on_pauseButton_clicked();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    explicit Game(int dimension, QWidget *parent = nullptr);
    ~Game();
};

#endif // GAME_HPP
