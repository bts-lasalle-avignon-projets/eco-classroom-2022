#include "ihmecoclassroom.h"
#include "ui_ihmecoclassroom.h"
#include <QDebug>

/**
 * @file ihmecoclassroom.cpp
 * @brief Définition de la classe IHMEcoClassroom
 * @version 0.1
 */

IHMEcoClassroom::IHMEcoClassroom(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMEcoClassroom)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;
}

IHMEcoClassroom::~IHMEcoClassroom()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}
