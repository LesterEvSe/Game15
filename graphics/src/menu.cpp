#include "menu.hpp"
#include "ui_menu.h"

#include <QMessageBox>

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

void Menu::on_informationButton_clicked()
{
    QMessageBox::information(this, "Information",
                "The main goal is to arrange all the blocks"
                "in ascending order, for example:\n\n"

                "1 2 3\n"
                "4 5 6\n"
                "7 8  \n\n"

                "Moves can be made using the W A S D keys\n"
                "or by left-clicking on the cell adjacent to an empty.\n\n"

                "Warning! If you used a solver, then your result will not be counted.");
}

