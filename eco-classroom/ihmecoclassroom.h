#ifndef IHMECOCLASSROOM_H
#define IHMECOCLASSROOM_H

/**
 * @file ihmecoclassroom.h
 * @brief Déclaration de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

#include <QtWidgets>

#define NOM     "Eco-Classroom"
#define VERSION "0.1"

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMEcoClassroom;
}
QT_END_NAMESPACE

class CommunicationMQTT;

/**
 * @class IHMEcoClassroom
 * @brief Déclaration de la classe IHMEcoClassroom
 * @details Cette classe s'occupe de l'affichage de la fenêtre principale
 */
class IHMEcoClassroom : public QMainWindow
{
    Q_OBJECT

  public:
    IHMEcoClassroom(QWidget* parent = nullptr);
    ~IHMEcoClassroom();

  private:
    Ui::IHMEcoClassroom* ui; //!< la fenêtre graphique associée à cette classe
    CommunicationMQTT*
      communicationMQTT; //!< association avec la classe CommunicationMQTT

    void ajouterMenuAide();

  public slots:
    void afficherAPropos();
};

#endif // IHMECOCLASSROOM_H
