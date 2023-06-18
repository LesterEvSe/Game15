#ifndef ACCEPTRESULT_HPP
#define ACCEPTRESULT_HPP

#include "database.hpp"

#include <QDialog>

namespace Ui { class AcceptResult; }
class AcceptResult : public QDialog
{
    Q_OBJECT

private:
    Ui::AcceptResult *ui;

    int m_dimension;
    unsigned int m_time_sec;
    Database *m_database;

    void set_styles();

private slots:
    void on_okButton_clicked();

public:
    explicit AcceptResult(int dimension, unsigned int time_sec, QWidget *parent = nullptr);
    ~AcceptResult();
};

#endif // ACCEPTRESULT_HPP
