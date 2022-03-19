--
-- Structure de la table `Utilisateur`
--

CREATE TABLE IF NOT EXISTS `Utilisateur` (
	`idUtilisateur`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`nom`	VARCHAR(64) NOT NULL UNIQUE,
	`prenom`	VARCHAR(64) NOT NULL,
	`identifiant`	VARCHAR(64) NOT NULL,
	`code`	VARCHAR(8) NOT NULL,
	UNIQUE(`nom`, `prenom`)
);

INSERT INTO `Utilisateur` (`nom`,`prenom`,`identifiant`,`code`) VALUES('VAIRA','Thierry','tvaira','1234');
INSERT INTO `Utilisateur` (`nom`,`prenom`,`identifiant`,`code`) VALUES('MORELLO','Laura','lmorello','0000');
INSERT INTO `Utilisateur` (`nom`,`prenom`,`identifiant`,`code`) VALUES('ZERYOUHI','Amine','azeryouhi','6666');