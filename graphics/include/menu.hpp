#ifndef MENU_HPP
#define MENU_HPP

#include <QDialog>

namespace Ui { class Menu; }
class Menu : public QDialog
{
    Q_OBJECT

private:
    Ui::Menu *ui;

private slots:
    void on_button2x2_clicked();
    void on_button3x3_clicked();
    void on_button4x4_clicked();
    void on_button5x5_clicked();

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
};

#endif // MENU_HPP
