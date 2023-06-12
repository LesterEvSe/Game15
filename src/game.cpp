#include "game.hpp"
#include "ui_game.h"

// To display the window in the center
#include <QScreen>
#include <QRect>
#include <QPoint>

#include <QPropertyAnimation>
#include <QPixmap> // for icon
#include <QVBoxLayout>

#include <QDebug>

bool Game::block_keyboard {false};

Game::Game(int dimension, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),

    m_dimension(dimension),
    m_time(0),
    m_zero_pos(m_dimension-1, m_dimension-1)
{
    ui->setupUi(this);
    setWindowTitle("Game 15");

    set_grid();
    set_styles();
    set_timer();

    int window_size = m_dimension * 100;
    resize(window_size, window_size);

    QRect screen_geometry = QApplication::primaryScreen()->geometry();
    int w = screen_geometry.width();
    int h = screen_geometry.height();

    // After that we can get the accurate size of our window
    show();
    move((w - width())/2, (h - height())/2);
}

Game::~Game() {
    delete ui;
}

void Game::set_grid()
{
    m_game_widget = ui->stackedWidget->findChild<QWidget*>("game");
    m_pause_widget = ui->stackedWidget->findChild<QWidget*>("pause");
    m_grid_layout = new QGridLayout(m_game_widget);

    int size = 100;
    if (m_dimension == 2)
        size = 150;

    for (int row = 0; row < m_dimension; ++row)
    {
        m_grid_layout->setRowMinimumHeight(row, size);
        m_grid_layout->setColumnMinimumWidth(row, size);

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
    }
    m_game_widget->setLayout(m_grid_layout);
    ui->stackedWidget->setCurrentWidget(m_game_widget);
}

void Game::set_styles()
{
    QPixmap pixmap(":/clock.png");
    pixmap = pixmap.scaled(pixmap.size());
    ui->iconLabel->setPixmap(pixmap);
}

void Game::set_timer()
{
    QObject::connect(&m_timer, &QTimer::timeout, [this](){
        static constexpr unsigned int max_time = 3600*100-1;
        if (m_time >= max_time) return;
        ++m_time;

        ui->timeLabel->setText(QString("%1:%2:%3")
                                   .arg(m_time/3'600'000,   2, 10, QChar('0'))
                                   .arg((m_time/60'000)%60, 2, 10, QChar('0'))
                                   .arg((m_time/1'000)%60,  2, 10, QChar('0')));
    });

    // When you pause, the counter is reset,
    // so if there are seconds,
    // you can solve the whole field in 0 seconds
    m_timer.start(1);
}

// This is where we take the movement of the cell
// 1 0, -1 0, 0 1, 0 -1
bool Game::move_to(int row, int col)
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

void Game::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QString unicode_char = event->text();
    if (key == Qt::Key_P || unicode_char == QString("з"))
        on_pauseButton_clicked();

    if (block_keyboard) return;

    // Although programmatically we move the 0 cell,
    // the user moves specific blocks of numbers.
    // So moving 0 UP is equivalent to moving
    // the cell with the number DOWN.
    if      (key == Qt::Key_A || key == Qt::Key_Left  || unicode_char == QString("ф"))
        move_to(0, 1);
    else if (key == Qt::Key_D || key == Qt::Key_Right || unicode_char == QString("в"))
        move_to(0, -1);
    else if (key == Qt::Key_W || key == Qt::Key_Up    || unicode_char == QString("ц"))
        move_to(1, 0);
    else if (key == Qt::Key_S || key == Qt::Key_Down  || unicode_char == QString("ы") || unicode_char == QString("і"))
        move_to(-1, 0);
}

void Game::on_pauseButton_clicked()
{
    static bool pause {false};
    if (!pause) {
        m_timer.stop();
        block_keyboard = true;
        pause = true;

        ui->pauseButton->setText("Resume");
        ui->stackedWidget->setCurrentWidget(m_pause_widget);
        return;
    }
    ui->pauseButton->setText("Pause");
    ui->stackedWidget->setCurrentWidget(m_game_widget);

    m_timer.start();
    block_keyboard = false;
    pause = false;
}

