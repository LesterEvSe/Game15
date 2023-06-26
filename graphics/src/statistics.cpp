#include "statistics.hpp"
#include "ui_statistics.h"
#include "game.hpp" // for 'showErrorAndExit' function

#include <vector>
#include <QDebug> /// NEED TO DELETE LATER!!!

Statistics::Statistics(int dimension, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistics),
    m_database(Database::get_instance()),
    m_dimension(dimension)
{
    ui->setupUi(this);
    setWindowTitle("Best Times");

    ui->comboBox->addItem("2x2");
    ui->comboBox->addItem("3x3");
    ui->comboBox->addItem("4x4");
    ui->comboBox->addItem("5x5");

    // dimension from 2 to 5 inclusive.
    // Indexes from 0 to 3 inclusive too
    ui->comboBox->setCurrentIndex(m_dimension-2);
}

Statistics::~Statistics() {
    delete ui;
}

int Statistics::exec() {
    ui->comboBox->setCurrentIndex(m_dimension-2);
    on_comboBox_currentIndexChanged(m_dimension-2);
    return QDialog::exec();
}

void Statistics::on_comboBox_currentIndexChanged(int index)
{
    std::vector<std::pair<QString, QString>> data;
    // index + 2 - from index to dimension
    try {
        data = m_database->get_time_players(index + 2);
    }
    catch(const QSqlError &error) {
        Game::showErrorAndExit("Caught SQL error: " + error.text());
    }

    ui->rankTextBrowser->clear();
    ui->timeTextBrowser->clear();
    ui->playerTextBrowser->clear();
    setFixedSize(1200, 400); // The size is handpicked

    for (int i = 0; i < data.size(); ++i) {
        unsigned int time = data[i].first.toInt();
        ui->rankTextBrowser->append(QString::number(i+1));
        ui->timeTextBrowser->append(QString::number(time/60) + " minutes " +
                                    QString::number(time%60) + " seconds");
        ui->playerTextBrowser->append(data[i].second);

        ui->rankTextBrowser->setAlignment(Qt::AlignCenter);
        ui->timeTextBrowser->setAlignment(Qt::AlignCenter);
        ui->playerTextBrowser->setAlignment(Qt::AlignCenter);
    }
}

