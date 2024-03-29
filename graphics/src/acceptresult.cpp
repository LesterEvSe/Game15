#include "acceptresult.hpp"
#include "ui_acceptresult.h"
#include "game.hpp" // for 'showErrorAndExit' function

#include <QMessageBox>
#include <QIcon>

AcceptResult::AcceptResult(int dimension, unsigned int time_sec, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AcceptResult),

    m_dimension(dimension),
    m_time_sec(time_sec),
    m_database(Database::get_instance())
{
    ui->setupUi(this);
    setWindowTitle("Congratulations!");
    ui->timeLabel->setText(
        QString::number(m_time_sec/60) + " minutes\n" +
        QString::number(m_time_sec%60) + " seconds");

    set_styles();
}

AcceptResult::~AcceptResult() {
    delete ui;
}

void AcceptResult::set_styles()
{
    QIcon icon(":/res/ok-button.png");
    ui->okButton->setIcon(icon);
}

void AcceptResult::on_okButton_clicked()
{
    QString username = ui->playerLineEdit->text();
    if (username.length() < 4) {
        QMessageBox::warning(this, "Warning", "Username must contain at least 4 symbols");
        ui->playerLineEdit->clear();
    }
    else if (username.length() > 32) {
        QMessageBox::warning(this, "Warning", "Username is too long");
        ui->playerLineEdit->clear();
    }
    else {
        try {
            m_database->add_time(m_dimension, m_time_sec, username);
            accept();
        }
        catch(const QSqlError &error) {
            Game::showErrorAndExit("Caught SQL error: " + error.text());
        }
    }
}

