#include "game15.hpp"

// To display the window in the center
#include <QScreen>
#include <QRect>
#include <QPoint>
#include <QPropertyAnimation>
#include <QDebug>

Game15::Game15(int dimension, QWidget *parent) :
    QWidget(parent),
    m_dimension(dimension)
{
    m_grid_layout = std::make_unique<QGridLayout>();
    setFixedSize(m_dimension*100, m_dimension*100);

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
    static bool animation_running {false};
    if (animation_running) return false;
    animation_running = true;

    // target pos
    row += m_zero_pos.first;
    col += m_zero_pos.second;
    qDebug() << m_zero_pos;
    qDebug() << row << ' ' << col << Qt::endl;

    if (row < 0 || row >= m_dimension ||
        col < 0 || col >= m_dimension) return false;

    QLayoutItem *layout_item_from = m_grid_layout->itemAtPosition(m_zero_pos.first, m_zero_pos.second);
    QLayoutItem *layout_item_to   = m_grid_layout->itemAtPosition(row, col);

    /// Here problems with deletes elements
    // delete elements, then add them to new positions
    m_grid_layout->removeWidget(layout_item_from);
    m_grid_layout->removeWidget(layout_item_to);

    m_grid_layout->addWidget(layout_item_from, row, col);
    m_grid_layout->addWidget(layout_item_to, m_zero_pos.first, m_zero_pos.second);
    m_zero_pos = {row, col};

    QLabel *label_from = qobject_cast<QLabel*>(layout_item_from->widget());
    QLabel *label_to   = qobject_cast<QLabel*>(layout_item_to->widget());

    QPoint curr_pos    = label_from->pos();
    QPoint target_pos  = label_to->pos();

    // in ms
    static constexpr int duration {200};
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

    connect(elem_animation, &QPropertyAnimation::finished, this, [this](){
        animation_running = false;
    });
    return true;
}

void Game15::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    //if (key == Qt::Key_Left )

    move_to(-1, 0);
//    QLayoutItem *layout_item = m_grid_layout->itemAtPosition(1, 2);
//    QLabel *label = qobject_cast<QLabel*>(layout_item->widget());

//    QPoint curr_pos = label->pos();
//    qDebug() << curr_pos;
//    QPoint target_pos = curr_pos + QPoint(100, 0);

//    QPropertyAnimation *animation = new QPropertyAnimation(label, "pos");
//    animation->setDuration(1'000);
//    animation->setStartValue(curr_pos);
//    animation->setEndValue(target_pos);
//    animation->start();

//    int key = event->key();

//    if (key == Qt::Key_Left || key == Qt::Key_A)
//        ;
}













