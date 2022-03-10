#include "ihmclassroom.h"
#include "ui_ihmclassroom.h"

IhmClassroom::IhmClassroom(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IhmClassroom)
{
    ui->setupUi(this);
}

IhmClassroom::~IhmClassroom()
{
    delete ui;
}

