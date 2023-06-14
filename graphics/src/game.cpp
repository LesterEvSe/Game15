#include "game.hpp"
#include "ui_game.h"
#include "menu.hpp"

// To display the window in the center
#include <QScreen>
#include <QRect>
#include <QPoint>

#include <QPropertyAnimation>
#include <QPixmap> // for icon

#include <vector>
#include <QDebug> // NEED TO DELETE LATER!!!

Game::Game(int dimension, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),

    m_dimension(dimension),
    m_time_ms(0),
    m_duration_animation_ms(100),

    m_block_keyboard(false),
    m_pause(false),
    m_start_solver(0)
{
    ui->setupUi(this);
    setWindowTitle("Game 15");

    set_grid();
    set_styles();
    QObject::connect(&m_timer, &QTimer::timeout, [this](){
        static constexpr unsigned int max_time = 3'600'000*100-1;
        if (m_time_ms >= max_time) return;
        ++m_time_ms;

        ui->timeLabel->setText(QString("%1:%2:%3")
                                   .arg(m_time_ms/3'600'000,   2, 10, QChar('0'))
                                   .arg((m_time_ms/60'000)%60, 2, 10, QChar('0'))
                                   .arg((m_time_ms/1'000)%60,  2, 10, QChar('0')));
    });

    // When you pause, the counter is reset,
    // so if there are seconds,
    // you can solve the whole field in 0 seconds
    m_timer.setInterval(1);

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


void Game::new_game()
{
    // We get a random solvable field
    m_solver = std::make_unique<Solver>(m_dimension);
    const std::vector<std::vector<int>>& field = m_solver->get_field();
    for (int row = 0; row < m_dimension; ++row)
        for (int col = 0; col < m_dimension; ++col)
        {
            int value = field[row][col];
            QLabel *label = qobject_cast<QLabel*>(m_grid_layout->itemAtPosition(row, col)->widget());

            if (value) {
                label->setText(QString::number(value));
                label->setFrameStyle(QFrame::Box);
            }
            else {
                label->setText("");
                label->setFrameStyle(QFrame::NoFrame);
                m_zero_pos = {row, col};
            }
        }
    m_block_keyboard = false;
    m_pause = false;
    m_start_solver = 0;

    ui->solveButton->setEnabled(true);
    ui->solveButton->setText("Solve");
    ui->pauseButton->setEnabled(true);

    m_time_ms = 0;
    m_timer.start();
}

void Game::end_game()
{
    m_timer.stop();
    m_block_keyboard = true;
    switch_solver_buttons(true);
    ui->solveButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);
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
            QLabel *label = new QLabel();
            label->setAlignment(Qt::AlignCenter);

            m_grid_layout->addWidget(label, row, col);
        }
    }
    new_game();

    m_game_widget->setLayout(m_grid_layout);
    ui->stackedWidget->setCurrentWidget(m_game_widget);
}

void Game::set_styles()
{
    QPixmap pixmap(":/clock.png");
    pixmap = pixmap.scaled(pixmap.size());
    ui->iconLabel->setPixmap(pixmap);
}

void Game::switch_solver_buttons(bool enable)
{
    ui->playAgainButton->setEnabled(enable);
    ui->changeDifficultyButton->setEnabled(enable);
    ui->bestTimesButton->setEnabled(enable);
    ui->pauseButton->setEnabled(enable);
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

    // setDuration in ms
    QPropertyAnimation *zero_animation = new QPropertyAnimation(label_from, "pos");
    zero_animation->setDuration(m_duration_animation_ms);
    zero_animation->setStartValue(label_from->pos());
    zero_animation->setEndValue(label_to->pos());

    QPropertyAnimation *elem_animation = new QPropertyAnimation(label_to, "pos");
    elem_animation->setDuration(m_duration_animation_ms);
    elem_animation->setStartValue(label_to->pos());
    elem_animation->setEndValue(label_from->pos());

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
        m_solver->move(row, col);

        // unlock thread
        animation_running = false;

        zero_animation->deleteLater();
        elem_animation->deleteLater();

        if (m_solver->is_solved())
            end_game();

        else if (m_start_solver % 2) {
            std::pair<int, int> pair = m_solver->next_move();
            move_to(pair.first, pair.second);
        }
    });
    return true;
}



void Game::keyPressEvent(QKeyEvent *event)
{
    if (m_block_keyboard) return;

    int key = event->key();
    QString unicode_char = event->text();

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
    if (!m_pause) {
        m_timer.stop();
        m_block_keyboard = true;
        m_pause = true;

        ui->pauseButton->setText("Resume");
        ui->stackedWidget->setCurrentWidget(m_pause_widget);
        return;
    }
    ui->pauseButton->setText("Pause");
    ui->stackedWidget->setCurrentWidget(m_game_widget);

    m_timer.start();
    m_block_keyboard = false;
    m_pause = false;
}

void Game::on_playAgainButton_clicked() {
    new_game();
}

void Game::on_changeDifficultyButton_clicked()
{
    close();
    std::unique_ptr<Menu> menu = std::make_unique<Menu>();
    int start_game = menu->exec();
    if (start_game) {
        Game *new_game = new Game(start_game);
        deleteLater();
    }
}

void Game::on_solveButton_clicked()
{
    if (m_start_solver++ % 2) {
        ui->solveButton->setText("Solver");
        m_duration_animation_ms = 100; // set default value
        switch_solver_buttons(true);
        return;
    }
    switch_solver_buttons(false);
    ui->solveButton->setText("Stop");

    // fps * steps = time
    // time = 15'000 ms
    // fps = time / steps
    // select a value between 60 and 100 ms depending on the number of moves,
    // with a limit <= 15 seconds.
    // Can be ignored if the speed should be < 60 ms
    m_duration_animation_ms = std::min(100, std::max(60, 15'000 / m_solver->solve()));

    std::pair<int, int> pair = m_solver->next_move();
    move_to(pair.first, pair.second);
}

