#ifndef GAME_HPP
#define GAME_HPP

#include "solver.hpp"

#include <QApplication>
#include <QWidget>
#include <QStackedWidget>

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include <QKeyEvent>

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

    // variable flags
    bool m_block_keyboard;
    bool m_pause;


    bool move_to(int row, int col);
    void set_grid();
    void set_styles();

    void new_game();
    void end_game();

private slots:
    void on_pauseButton_clicked();
    void on_playAgainButton_clicked();
    void on_changeDifficultyButton_clicked();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    explicit Game(int dimension, QWidget *parent = nullptr);
    ~Game();
};

#endif // GAME_HPP
