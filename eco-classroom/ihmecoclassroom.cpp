#include "ihmecoclassroom.h"
#include "ui_ihmecoclassroom.h"

/**
 * @file ihmecoclassroom.cpp
 * @brief Définition de la classe ihmecoclassroom
 * @version 0.1
 * version 0.1
 */

IHMEcoClassroom::IHMEcoClassroom(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::IHMEcoClassroom) {
  ui->setupUi(this);
}

IHMEcoClassroom::~IHMEcoClassroom() { delete ui; }
