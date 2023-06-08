#ifndef CHOOSE_HPP
#define CHOOSE_HPP

#include <QDialog>

namespace Ui {
class Choose;
}

class Choose : public QDialog
{
    Q_OBJECT
private:
    Ui::Choose *ui;

public:
    explicit Choose(QWidget *parent = nullptr);
    ~Choose();
private slots:
    void on_button2x2_clicked();
    void on_button3x3_clicked();
    void on_button4x4_clicked();
    void on_button5x5_clicked();
};

#endif // CHOOSE_HPP
