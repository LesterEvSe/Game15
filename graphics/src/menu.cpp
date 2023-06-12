#include "menu.hpp"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowTitle("Game 15");
}

Menu::~Menu() {
    delete ui;
}

void Menu::on_button2x2_clicked() { done(2); }
void Menu::on_button3x3_clicked() { done(3); }
void Menu::on_button4x4_clicked() { done(4); }
void Menu::on_button5x5_clicked() { done(5); }
