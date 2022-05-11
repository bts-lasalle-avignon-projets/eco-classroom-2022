--- LDD (langage de définition de données)

--- Supprime les tables

DROP TABLE IF EXISTS BrokerMQTT;
DROP TABLE IF EXISTS Mesure;
DROP TABLE IF EXISTS Salle;
DROP TABLE IF EXISTS IndiceQualiteAir;
DROP TABLE IF EXISTS IndiceConfort;

--- Création des tables

-- Structure de la table IndiceConfort
-- indice : facultatif (peut être calculé à partir de l'id)

CREATE TABLE IF NOT EXISTS IndiceConfort(idIndiceConfort INTEGER PRIMARY KEY, libelle VARCHAR);

-- Structure de la table IndiceQualiteAir

CREATE TABLE IF NOT EXISTS IndiceQualiteAir(idIndiceQualiteAir INTEGER PRIMARY KEY, libelle VARCHAR);

-- Structure de la table Salle

CREATE TABLE IF NOT EXISTS Salle(
    idSalle INTEGER PRIMARY KEY AUTOINCREMENT,
    nom VARCHAR,
    lieu VARCHAR,
    description VARCHAR,
    superficie INTEGER DEFAULT 0,
    idIndiceConfort INTEGER DEFAULT -4,
    idIndiceQualiteAir INTEGER DEFAULT 0,
    etatFenetres INTEGER DEFAULT 0, -- Boolean values are stored as integers 0 (false) and 1 (true)
    etatLumieres INTEGER DEFAULT 0,
    estOccupe INTEGER DEFAULT 0,
    estFavori INTEGER DEFAULT 0,
    CONSTRAINT IndiceConfort_fk_1 FOREIGN KEY (idIndiceConfort) REFERENCES IndiceConfort(idIndiceConfort),
    CONSTRAINT IndiceQualiteAir_fk_1 FOREIGN KEY (idIndiceQualiteAir) REFERENCES IndiceQualiteAir(idIndiceQualiteAir)
);

-- Structure de la table Mesure

CREATE TABLE IF NOT EXISTS Mesure(
    idMesure INTEGER PRIMARY KEY AUTOINCREMENT,
    idSalle INTEGER NOT NULL,
    temperature DECIMAL(3,1) DEFAULT 0, -- de -99.9 à 99.9
    luminosite SMALLINT UNSIGNED DEFAULT 0,
    humidite TINYINT UNSIGNED DEFAULT 0,
    co2 SMALLINT UNSIGNED DEFAULT 0,
    horodatage DATETIME NOT NULL,
    CONSTRAINT Salle_fk_1 FOREIGN KEY (idSalle) REFERENCES Salle(idSalle)
    ON DELETE CASCADE
);

--- Voir aussi :
--- ON DELETE CASCADE

PRAGMA foreign_keys=on;
-- Structure de la table SeuilsAlerte

CREATE TABLE IF NOT EXISTS SeuilsAlerte(
    idSalle INTEGER NOT NULL,
    temperatureMin DOUBLE NULL,
    temperatureMax DOUBLE NULL,
    luminositeMin INTEGER NULL,
    luminositeMax INTEGER NULL,
    humiditeMin INTEGER NULL,
    humiditeMax INTEGER NULL,
    co2Min INTEGER NULL,
    co2Max INTEGER NULL,
    PRIMARY KEY (idSalle),
    CONSTRAINT Salle_fk_2 FOREIGN KEY (idSalle) REFERENCES Salle(idSalle)
);

-- Structure de la table BrokerMQTT
-- mqtt(s)://[username[:password]@]host[:port]/topic
-- topic : temperature/b20 ou b20/temperature

CREATE TABLE IF NOT EXISTS BrokerMQTT(
    idBrokerMQTT INTEGER PRIMARY KEY AUTOINCREMENT,
    hostname VARCHAR NOT NULL,
    port INTEGER NOT NULL DEFAULT 1883,
    username VARCHAR DEFAULT NULL,
    `password` VARCHAR DEFAULT NULL,
    estActif INTEGER DEFAULT 1
);
