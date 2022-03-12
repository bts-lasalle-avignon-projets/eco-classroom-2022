#include "ihmecoclassroom.h"
#include "ui_ihmecoclassroom.h"

IHMEcoClassroom::IHMEcoClassroom(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IHMEcoClassroom)
{
    ui->setupUi(this);
}

IHMEcoClassroom::~IHMEcoClassroom()
{
    delete ui;
}

