#include "game15.hpp"

// To display the window in the center
#include <QScreen>
#include <QRect>

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
        for (int col = 0; col < m_dimension; ++col) {
            int value = row * m_dimension + col + 1;
            if (value == m_dimension * m_dimension)
                value = 0;
            QLabel *label = new QLabel(QString::number(value));
            label->setFrameStyle(QFrame::Box);
            label->setAlignment(Qt::AlignCenter);

            m_grid_layout->addWidget(label, row, col);
        }
    setLayout(m_grid_layout.get());
}
