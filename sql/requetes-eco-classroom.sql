--- Exemples et exercices d'accompagnement : déterminer les requêtes SQL

--- Liste des indices de confort



|indice|libelle|
|---|---|
|-3|froid|
|-2|frais|
|-1|légèrement frais|
|0|neutre|
|1|légèrement tiède|
|2|tiède|
|3|chaud|

--- Liste des indices de confort



|idIndiceQualiteAir|libelle|
|---|---|
|1|très bon|
|2|bon|
|3|moyen|
|4|médiocre|
|5|mauvais|
|6|très mauvais|

--- Liste des salles



|idSalle|nom|lieu|description|superficie|code|idIndiceConfort|idIndiceQualiteAir|etatFenetres|etatLumieres|estOccupe|estFavori|
|---|---|---|---|---|---|---|---|---|---|---|---|
|1|B11|Bat. BTS|Cours|15|0000|-1|0|0|0|0|0|
|2|B20|Bat. BTS|Atelier|60|1234|-1|0|0|0|0|0|
|3|B21|Bat. BTS|Labo|40|1234|-1|0|0|0|0|0|
|4|B22|Bat. BTS|Cours|50|6666|-1|0|0|0|0|0|



|nom|indice|libelle|
|---|---|---|
|B11|0|inconnu|
|B20|0|inconnu|
|B21|0|inconnu|
|B22|0|inconnu|

--- Nombre de salles

SELECT COUNT(*) AS NbSalles FROM Salle;

| NbSalles |
| -------- |
| 4        |

--- Liste des brokers MQTT

SELECT * FROM BrokerMQTT;

|idBrokerMQTT|hostname|port|username|password|estActif|
|---|---|---|---|---|---|
|1|192.168.52.1|1883|NULL|NULL|1|

--- Nombre de mesures

SELECT COUNT(*) AS NbMesures FROM Mesure;

--- Liste des mesures



|idMesure|idSalle|temperature|luminosite|humidite|co2|horodatage|idSalle|nom|lieu|description|superficie|code|idIndiceConfort|idIndiceQualiteAir|etatFenetres|etatLumieres|estOccupe|estFavori|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|1|1|20.3|450|35|500|2022-01-29 08:00:00|1|B11|Bat. BTS|Curs|15|0000|-1|0|0|0|0|0|
|2|2|20.3|450|35|500|2022-01-29 08:00:00|2|B20|Bat. BTS|Atelier|60|1234|-1|0|0|0|0|0|

---- Modifier un état d'une salle


