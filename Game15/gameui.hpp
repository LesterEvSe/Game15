#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <QMainWindow>
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
    std::unique_ptr<QGridLayout> m_grid_layout;

    int m_dimension;
    unsigned int m_time;
    QTimer m_timer;
    QPair<int, int> m_zero_pos;

    bool move_to(int row, int col);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    explicit GameUi(int dimension, QWidget *parent = nullptr);
    ~GameUi();
};

#endif // GAMEUI_HPP
