#include "game15.hpp"

// To display the window in the center
#include <QScreen>
#include <QRect>
#include <QPoint>
#include <QPropertyAnimation>
#include <QDebug>

Game15::Game15(int dimension, QWidget *parent) :
    QWidget(parent),
    m_dimension(dimension),
    m_zero_pos(m_dimension-1, m_dimension-1)
{
    m_grid_layout = std::make_unique<QGridLayout>();
    resize(m_dimension*100, m_dimension*100);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int w = screenGeometry.width();
    int h = screenGeometry.height();
    move((w - width())/2, (h - height())/2);

    for (int row = 0; row < m_dimension; ++row)
        for (int col = 0; col < m_dimension; ++col)
        {
            int value = row * m_dimension + col + 1;
            QLabel *label;

            if (value == m_dimension * m_dimension)
                label = new QLabel();
            else {
                label = new QLabel(QString::number(value));
                label->setFrameStyle(QFrame::Box);
                label->setAlignment(Qt::AlignCenter);
            }
            m_grid_layout->addWidget(label, row, col);
        }
    setLayout(m_grid_layout.get());
}

Game15::~Game15()
{
    QLayoutItem *item;
    while (item = m_grid_layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
}

// This is where we take the movement of the cell
// 1 0, -1 0, 0 1, 0 -1
bool Game15::move_to(int row, int col)
{
    // Simulation of thread lock
    static bool animation_running {false};
    if (animation_running) return false;
    animation_running = true;

    // target pos
    row += m_zero_pos.first;
    col += m_zero_pos.second;

    if (row < 0 || row >= m_dimension ||
        col < 0 || col >= m_dimension)
    {
        // unlock thread
        animation_running = false;
        return false;
    }

    QLayoutItem *layout_item_from = m_grid_layout->itemAtPosition(m_zero_pos.first, m_zero_pos.second);
    QLayoutItem *layout_item_to   = m_grid_layout->itemAtPosition(row, col);

    QLabel *label_from = qobject_cast<QLabel*>(layout_item_from->widget());
    QLabel *label_to   = qobject_cast<QLabel*>(layout_item_to->widget());

    QPoint curr_pos    = label_from->pos();
    QPoint target_pos  = label_to->pos();

    // in ms
    static constexpr int duration {100};
    QPropertyAnimation *zero_animation = new QPropertyAnimation(label_from, "pos");
    zero_animation->setDuration(duration);
    zero_animation->setStartValue(curr_pos);
    zero_animation->setEndValue(target_pos);

    QPropertyAnimation *elem_animation = new QPropertyAnimation(label_to, "pos");
    elem_animation->setDuration(duration);
    elem_animation->setStartValue(target_pos);
    elem_animation->setEndValue(curr_pos);

    zero_animation->start();
    elem_animation->start();

    connect(elem_animation, &QPropertyAnimation::finished, this, [
        this, label_from, label_to, row, col, zero_animation, elem_animation](){

        // delete elements, then add them to new positions
        m_grid_layout->removeWidget(label_from);
        m_grid_layout->removeWidget(label_to);

        m_grid_layout->addWidget(label_from, row, col);
        m_grid_layout->addWidget(label_to, m_zero_pos.first, m_zero_pos.second);

        m_zero_pos = {row, col};
        // unlock thread
        animation_running = false;

        zero_animation->deleteLater();
        elem_animation->deleteLater();
    });
    return true;
}

void Game15::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    // Although programmatically we move the 0 cell,
    // the user moves specific blocks of numbers.
    // So moving 0 UP is equivalent to moving
    // the cell with the number DOWN.
    if      (key == Qt::Key_A || key == Qt::Key_Left)
        move_to(0, 1);
    else if (key == Qt::Key_D || key == Qt::Key_Right)
        move_to(0, -1);
    else if (key == Qt::Key_W || key == Qt::Key_Up)
        move_to(1, 0);
    else if (key == Qt::Key_S || key == Qt::Key_Down)
        move_to(-1, 0);
}











