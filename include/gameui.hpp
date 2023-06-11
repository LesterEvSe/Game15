#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>

#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>

#include <memory>

namespace Ui { class GameUi; }
class GameUi : public QMainWindow
{
    Q_OBJECT

private:
    Ui::GameUi *ui;

    // widget where m_grid_layout and pause window are located
    QStackedWidget *m_stacked_widget;
    QGridLayout *m_grid_layout;

    QWidget *m_game_widget;
    QWidget *m_pause_widget;

    int m_dimension;
    unsigned int m_time;
    QTimer m_timer;
    QPair<int, int> m_zero_pos;


    bool move_to(int row, int col);
    void set_grid();
    void set_pause_window();
    void set_styles();
    void set_timer();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    explicit GameUi(int dimension, QWidget *parent = nullptr);
    ~GameUi();
private slots:
    void on_pauseButton_clicked();
};

#endif // GAMEUI_HPP
