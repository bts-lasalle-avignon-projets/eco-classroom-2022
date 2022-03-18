#ifndef IHMECOCLASSROOM_H
#define IHMECOCLASSROOM_H

/**
 * @file ihmecoclassroom.h
 * @brief Déclaration de la classe IHMEcoClassroom
 * @version 0.1
 */

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMEcoClassroom;
}
QT_END_NAMESPACE

class IHMEcoClassroom : public QMainWindow
{
    Q_OBJECT

  public:
    IHMEcoClassroom(QWidget* parent = nullptr);
    ~IHMEcoClassroom();

  private:
    Ui::IHMEcoClassroom* ui;
    QLabel*              labelfiltrer;
    QComboBox*           filtrerSalles;
    QLabel*              labelList;
    QLabel*              labelSalles;
    QLabel*              labelDescription;
    QLabel*              labelConfort;
    QLabel*              labelFenetres;
    QLabel*              labelLumieres;
    QPushButton*         info;
};
#endif // IHMECOCLASSROOM_H
