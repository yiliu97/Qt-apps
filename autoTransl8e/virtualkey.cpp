#include "virtualkey.h"
#include "ui_virtualkey.h"


/*
  a virtual keyboard to enable inputs on embedded devices
  currently only support numbers and lowercase letters
*/
virtualkey::virtualkey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::virtualkey)
{
    ui->setupUi(this);
}

virtualkey::~virtualkey()
{
    delete ui;
}
