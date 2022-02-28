--- LMD (langage de manipulation de données)

--- Contenu des tables (tests)

--- Table IndiceConfort

INSERT INTO IndiceConfort(idIndiceConfort,indice,libelle) VALUES
(-1,0,'inconnu'),
(0,-3,'froid'),
(1,-2,'frais'),
(2,-1,'légèrement frais'),
(3,0,'neutre'),
(4,1,'légèrement tiède'),
(5,2,'tiède'),
(6,3,'chaud');

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

INSERT INTO Salle(nom, lieu, description, superficie, code) VALUES ('B11','Bat. BTS','Cours','15','0000');
INSERT INTO Salle(nom, lieu, description, superficie, code) VALUES ('B20','Bat. BTS','Atelier','60','1234');
INSERT INTO Salle(nom, lieu, description, superficie, code) VALUES ('B21','Bat. BTS','Labo','40','1234');
INSERT INTO Salle(nom, lieu, description, superficie, code) VALUES ('B22','Bat. BTS','Cours','50','6666');

--- Table SeuilsAlerte



--- Table BrokerMQTT

INSERT INTO BrokerMQTT(hostname,estActif) VALUES ('192.168.52.1',1);
