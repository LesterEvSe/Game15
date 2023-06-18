#ifndef GAME_HPP
#define GAME_HPP

#include "solver.hpp"
#include "acceptresult.hpp"
#include "statistics.hpp"

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

    // To make the solver faster, we will speed up,
    // depending on the number of steps
    int m_duration_animation_ms;

    QTimer m_timer;
    QPair<int, int> m_zero_pos;

    // variable flags
    bool m_block_keyboard;
    bool m_pause;

    // Incremented. An odd (1,3...) number is a stop button,
    // otherwise a solver.
    // If > 0, the the record is not counted
    int m_start_solver;

    bool move_to(int row, int col);
    void set_grid();
    void set_styles();

    void new_game();
    void end_game();

    void switch_solver_buttons(bool enable);

private slots:
    void on_pauseButton_clicked();
    void on_playAgainButton_clicked();
    void on_changeDifficultyButton_clicked();

    void on_solveButton_clicked();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    static void showErrorAndExit(const QString &error);
    explicit Game(int dimension, QWidget *parent = nullptr);
    ~Game();
};

#endif // GAME_HPP
