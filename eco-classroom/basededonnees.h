/**
 * @brief
 * Fichier qui contient la déclaration de la classe BaseDeDonnees
 * @file basededonnees.h
 */

#ifndef BASEDEDONNEE_H
#define BASEDEDONNEE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QMutex>
#include <QString>

/**
 * @brief
 * Class permettant de s'interfacer avec la base de données
 * @class BaseDeDonnees basededonnees.h "basededonnees.h"
 */
class BaseDeDonnees : public QObject
{
    Q_OBJECT
  private:
    static BaseDeDonnees*
      baseDeDonnees; //!< Objet de type BaseDeDonnees accessible uniquement
                     //!< depuis une méthode static
    static QString typeBase; //!< Attribut de type QString contenant le type de
                             //!< la base de données (MySQL, SQLite, ...)
    static int nbAcces; //!< Attribut de type int contenant le nombre d'accès en
                        //!< cours à la base de données
    QSqlDatabase db; //!< Objet de type QSqlDatabase permettant la connexion
                     //!< avec la base de données
    QMutex mutex; //!< Objet de type QMutex permettant de protéger l'objet db,
                  //!< en autorisant son accès par un seul thread à la fois

    /**
     * @brief
     * Constructeur de la classe BaseDeDonnees en privé afin de controller ses
     * appels
     * @param type
     */
    BaseDeDonnees(QString type);
    /**
     * @brief
     * Destructeur de la classe BaseDeDonnees
     */
    ~BaseDeDonnees();

  public:
    /**
     * @brief
     * Permet de créer une instance de BDD ou de récuperer celle deja en cours,
     * cette méthode controle l'instanciation des objet BaseDeDonnees. Static
     * elle est accessible depuis n'importe où
     * @param type
     * @return Instance de la BDD
     */
    static BaseDeDonnees* getInstance(QString type = "QSQLITE");
    /**
     * @brief
     * Permet de detruire l'instance en cours, Static elle est accessible depuis
     * n'importe où
     */
    static void detruireInstance();
    /**
     * @brief
     * Permet d'ouvrir le fichier de base de données passé en paramètre
     * @param fichierBase
     * @return booleen définissant si l'accès BDD s'est réalisé correctement
     */
    bool ouvrir(QString fichierBase);
    /**
     * @brief
     * Permet de savoir si la base de données est ouverte ou non
     * @return un booleen correspondant à l'état d'ouverture de la base de
     * données
     */
    bool estOuvert();

    /**
     * @brief
     * Permet d'executer la requete passé en paramètre au format SQL
     * @param requete
     * @return un booleen correspondant à l'état de retour de la requête
     */
    bool executer(QString requete);

    /**
     * @brief
     * Permet d'executer la requete passé en paramètre au format SQL, et remplit
     * le QString de sa réponse. Cette requête permet de récuperer un champs
     * d'un enregistrement
     * @param requete
     * @param donnees
     * @return un booleen correspondant à l'état de retour de la requête
     */
    bool recuperer(QString requete, QString& donnees);
    /**
     * @brief
     * Permet d'executer la requete passé en paramètre au format SQL, et remplit
     * le QStringListe de sa réponse. Cette requête permet de récuperer
     * plusieurs champs d'un enregistrement
     * @param requete
     * @param donnees
     * @return un booleen correspondant à l'état de retour de la requête
     */
    bool recuperer(QString requete, QStringList& donnees);
    /**
     * @brief
     * Permet d'executer la requete passé en paramètre au format SQL, et remplit
     * le QVector<QString> de sa réponse. Cette requête permet de récuperer un
     * champs de plusieurs enregistrements
     * @param requete
     * @param donnees
     * @return un booleen correspondant à l'état de retour de la requête
     */
    bool recuperer(QString requete, QVector<QString>& donnees);
    /**
     * @brief
     * Permet d'executer la requete passé en paramètre au format SQL, et remplit
     * le QVector<QStringList> de sa réponse. Cette requête permet de récuperer
     * plusieurs champs de plusieurs enregistrements
     * @param requete
     * @param donnees
     * @return un booleen correspondant à l'état de retour de la requête
     */
    bool recuperer(QString requete, QVector<QStringList>& donnees);

  signals:

  public slots:
};

#endif // BASEDEDONNEE_H
