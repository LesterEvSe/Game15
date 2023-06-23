#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "database.hpp"

#include <QDialog>

namespace Ui { class Statistics; }
class Statistics : public QDialog
{
    Q_OBJECT

private:
    Ui::Statistics *ui;
    Database *m_database;
    int m_dimension;

private slots:
    void on_comboBox_currentIndexChanged(int index);


public:
    virtual int exec() override;

    explicit Statistics(int dimension, QWidget *parent = nullptr);
    ~Statistics();
};

#endif // STATISTICS_HPP
