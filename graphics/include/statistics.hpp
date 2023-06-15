#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <QDialog>

namespace Ui {
class Statistics;
}

class Statistics : public QDialog
{
    Q_OBJECT

private:
    Ui::Statistics *ui;

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics();
};

#endif // STATISTICS_HPP
