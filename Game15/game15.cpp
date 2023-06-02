#include "game15.hpp"
#include "./ui_game15.h"

Game15::Game15(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game15)
{
    ui->setupUi(this);
}

Game15::~Game15() {
    delete ui;
}

