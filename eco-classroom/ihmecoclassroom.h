#ifndef IHMECOCLASSROOM_H
#define IHMECOCLASSROOM_H

/**
 * @file ihmecoclassroom.h
 * @brief Déclaration de la classe ihmecoclassroom
 * @version 0.1
 * version 0.1
 */

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class IHMEcoClassroom;
}
QT_END_NAMESPACE

class IHMEcoClassroom : public QMainWindow {
  Q_OBJECT

public:
  IHMEcoClassroom(QWidget *parent = nullptr);
  ~IHMEcoClassroom();

private:
  Ui::IHMEcoClassroom *ui;
};
#endif // IHMECOCLASSROOM_H
