#include "game15.hpp"
#include "./ui_game15.h"

// To display the window in the center
#include <QScreen>
#include <QGridLayout>
#include <QLabel>

Game15::Game15(int dimension, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game15),
    m_dimension(dimension)
{
    ui->setupUi(this);
    setFixedSize(m_dimension*100, m_dimension*100);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int w = screenGeometry.width();
    int h = screenGeometry.height();
    move((w - width())/2, (h - height())/2);

    QGridLayout *grid_layout = new QGridLayout(this);

    for (int row = 0; row < m_dimension; ++row)
        for (int col = 0; col < m_dimension; ++col) {
            int value = row * m_dimension + col;
            if (value == m_dimension * m_dimension)
                value = 0;
            QLabel *label = new QLabel(QString::number(value));
            label->setFrameStyle(QFrame::Box);
            label->setAlignment(Qt::AlignCenter);

            grid_layout->addWidget(label, row, col);
        }

    QWidget *central_widget = new QWidget(this);
    central_widget->setLayout(grid_layout);
    setCentralWidget(central_widget);
}

Game15::~Game15() {
    delete ui;
}

