#ifndef GAME_HPP
#define GAME_HPP

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
    unsigned int m_time;
    QTimer m_timer;
    QPair<int, int> m_zero_pos;

    bool move_to(int row, int col);
    void set_grid();
    void set_styles();
    void set_timer();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    explicit Game(int dimension, QWidget *parent = nullptr);
    ~Game();
};

#endif // GAME_HPP
