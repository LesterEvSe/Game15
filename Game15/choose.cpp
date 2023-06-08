#include "choose.hpp"
#include "ui_choose.h"

Choose::Choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
    setWindowTitle("Game 15");
}

Choose::~Choose() {
    delete ui;
}

void Choose::on_button2x2_clicked() { done(2); }
void Choose::on_button3x3_clicked() { done(3); }
void Choose::on_button4x4_clicked() { done(4); }
void Choose::on_button5x5_clicked() { done(5); }
