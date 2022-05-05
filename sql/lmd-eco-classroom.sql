--- LMD (langage de manipulation de données)

--- Contenu des tables (tests)

--- Table IndiceConfort

INSERT INTO IndiceConfort(idIndiceConfort,libelle) VALUES
(-4,'inconnu'),
(-3,'froid'),
(-2,'frais'),
(-1,'légèrement frais'),
(0,'neutre'),
(1,'légèrement tiède'),
(2,'tiède'),
(3,'chaud');

--- Table IndiceQualiteAir

INSERT INTO IndiceQualiteAir(idIndiceQualiteAir,libelle) VALUES
(0,'inconnu'),
(1,'très bon'),
(2,'bon'),
(3,'moyen'),
(4,'médiocre'),
(5,'mauvais'),
(6,'très mauvais');

--- Table Salle

INSERT INTO Salle(nom, lieu, description, superficie) VALUES ('B11','Bat. BTS','Cours','15');
INSERT INTO Salle(nom, lieu, description, superficie) VALUES ('B20','Bat. BTS','Atelier','60');
INSERT INTO Salle(nom, lieu, description, superficie) VALUES ('B21','Bat. BTS','Labo','40');
INSERT INTO Salle(nom, lieu, description, superficie) VALUES ('B22','Bat. BTS','Cours','50');

--- Table Mesure

-- temperature,luminosite,humidite,co2

INSERT INTO Mesure(idSalle,horodatage) VALUES ('1', '1970-01-01 00:00:00');
INSERT INTO Mesure(idSalle,horodatage) VALUES ('2', '1970-01-01 00:00:00');
INSERT INTO Mesure(idSalle,horodatage) VALUES ('3', '1970-01-01 00:00:00');
INSERT INTO Mesure(idSalle,horodatage) VALUES ('4', '1970-01-01 00:00:00');


--- Table SeuilsAlerte



--- Table BrokerMQTT

INSERT INTO BrokerMQTT(hostname,estActif) VALUES ('192.168.52.7',1);
