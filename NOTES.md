# Notes sur la qualité de l'air et le confort thermique

- [Notes sur la qualité de l'air et le confort thermique](#notes-sur-la-qualité-de-lair-et-le-confort-thermique)
  - [CO2](#co2)
  - [Confort thermique](#confort-thermique)
    - [Indice de confort thermique](#indice-de-confort-thermique)
    - [Heat Index (HI) et Temperature-Humidity Index (THI)](#heat-index-hi-et-temperature-humidity-index-thi)
  - [Conclusion](#conclusion)
    - [CO2](#co2-1)
    - [Confort thermique](#confort-thermique-1)
  - [Lien](#lien)

## CO2

La concentration en CO2 dans l’air intérieur des bâtiments est habituellement comprise entre **350 et 2500 ppm** environ, et constitue l'un des critères qui fondent la réglementation en matière d'aération des locaux (bâtiments scolaires, bâtiments résidentiels et bureaux).

Pour les bâtiments non résidentiels, le seuil maximal en CO2 est fixé à **1000 ppm** dans des conditions normales d’occupation, avec une **tolérance à 1300 ppm** dans les locaux où il est interdit de fumer.

Le seuil maximal retenu pour une salle de classe sera : **1300 ppm**.

Les concentrations mesurées en CO2 permettent de définir un indice de confinement des locaux. Le décret n°2012-11 du 5 janvier 2012 fixe une valeur d’indice à 5 qu’il ne faut pas dépasser. L’indice de confinement ICONE (Indice de CONfinement d’air dans les Ecoles) varie de 0 (aucun confinement) à 5 (confinement extrême). Un confinement élevé ou très élevé (4 ou 5) traduit une densité d’occupation importante associée à un renouvellement d’air insuffisant.

Les valeurs de dioxyde de carbone correspondant aux périodes retenues sont ensuite partitionnées en trois classes selon leur niveau :

- nombre de valeurs inférieures ou égales à 1000 ppm (`n0`)
- nombre de valeurs comprises entre 1000 et 1700 ppm inclus (`n1`)
- nombre de valeurs supérieures à 1700 ppm (`n2`)
- proportions de valeurs comprises entre 1000 et 1700 ppm inclus (`f1`)
- proportions de valeurs supérieures à 1700 ppm (`f2`)

```
ICONE = (2.5 / log(2)) x log(1 + f1 + 3xf2)
```

| Valeur brute         | Valeur retenue   |
| :------------------: | :--------------: |
| ICONE < 0.5          | 0                |
| 0.5 <= ICONE < 1.5   | 1                |
| 1.5 <= ICONE < 2.5   | 2                |
| 2.5 <= ICONE < 3.5   | 3                |
| 3.5 <= ICONE < 4.5   | 4                |
| ICONE >= 4.5         | 5                |

_Remarque :_ Le calcul de l’indice de confinement nécessite de disposer de l’enregistrement des valeurs de concentrations de CO2 pour une période.

| Indice | Interprétation         |
| ------ | ---------------------- |
| 0      | Confinement nul        |
| 1      | Confinement faible     |
| 2      | Confinement moyen      |
| 3      | Confinement élevé      |
| 4      | Confinement très élevé |
| 5      | Confinement extrême    |

Mesure CO2 en temps réel

| Niveau       | Indice | En ppm        | Interprétation                                                                                            |
| ------------ |:------:|:-------------:| --------------------------------------------------------------------------------------------------------- |
| Excellent    | 1      | 0 - 400       | L'air intérieur est aussi frais que l'air extérieur                                                       |
| Très bien    | 2      | 400 - 1000    | La qualité de l'air à l'intérieur reste à des niveaux inoffensifs                                         |
| Modéré       | 3      | 1000 - 1500   | La qualité de l'air à l'intérieur a atteint des niveaux remarquables                                      |
| Mauvais      | 4      | 1500 - 2000   | La qualité de l'air à l'intérieur a atteint des niveaux précaires                                         |
| Très mauvais | 5      | 2000 - 5000   | La qualité de l'air à l'intérieur a atteint des niveaux inacceptables                                     |
| Sévère       | 6      | à partir 5000 | La qualité de l'air à l'intérieur a dépassé les valeurs maximales de concentration sur le lieu de travail |

## Confort thermique

### Indice de confort thermique

Selon l’OQAI (Observatoire de la Qualité de l’Air Intérieur), le taux optimal d’humidité relative dans l’air d’un logement se situe entre 40 et 70 %, pour une température s’élevant entre 18° et 22°C afin d’assurer de bonnes conditions de confort.

Le domaine du génie climatique fixe la plage acceptable pour le taux d’humidité de l’air entre 35 % et 70 %. Le taux d’humidité optimal pour des locaux chauffés se situe entre 40 % et 45 %.

Pour une salle de classe : 19-21°C et 45-55 %

### Heat Index (HI) et Temperature-Humidity Index (THI)

L’indice de chaleur HI est un indice qui est utilisé par le _National Oceanic and Atmospheric Administration_ (NOAA) aux Etats-Unis, combinant la température de l'air ambiant et l'humidité relative pour tenter de déterminer leur impact sur le confort thermique de l’homme.

L’indice appelé « temperature-humidity index » (THI) est un indice empirique développé lui aussi aux Etats-Unis dans les années 1950 afin d’évaluer les conditions d’inconfort thermique dans les milieux chauds et humides. THI est calculé avec la température de l’air (en °C) et l’humidité relative (en %).

> L’avantage est que leur calcul ne nécessite que deux données, la température d’air et l’humidité relative, qui sont des variables météorologiques facilement accessibles ou mesurables. Leur limite est que ni le rayonnement, ni le vent ne sont pris en compte alors que ce sont des facteurs qui influencent de manière non négligeable le confort thermique en milieu urbain.

L’indice THI (Temperature Humidity Index) de Thom se calcule selon la formule suivante :

```
THI = T - [(0.55 - 0.0055 x H) x (T - 14.5)]
```

Les ambiances définies par le THI de Thom se classent alors selon différents critères :

| Niveau | Indice de Thom    | Ambiance         |
| :----: | :---------------: | ---------------- |
| -3     | THI < -1.7        | froid            |
| -2     | -1.7 <= THI < 13  | frais            |
| -1     | 13 <= THI < 15    | légèrement frais |
| 0      | 15.0 <= THI < 20  | neutre           |
| 1      | 20 <= THI < 26.5  | légèrement tiède |
| 2      | 26.5 <= THI < 30  | tiède            |
| 3      | THI >= 30         | chaud            |

## Conclusion

### CO2

- pour les mesures de CO2 en temps réel :
    - le seuil maximal retenu pour une salle de classe sera : **1300 ppm**
    - évaluer la qualité de l'air de 1 à 6 (de Excellent à Sévère)
- pour les mesures enregistrées de CO2 :
    - calculer l'indice de confinement ICONE
    - évaluer le confinement de 0 à 5 (de Nul à Extrême)

### Confort thermique

- calculer le THI de Thom et évaluer le niveau d'ambiance de -3 à 3 (de Froid à Chaud)

Pour une salle de classe : 19-21°C et 45-55 %

## Lien

- [Climat intérieur et confort](https://enbau-online.ch/bauphysik/fr/1-2-climat-interieur-et-confort/)

---
Thierry Vaira [**[thierry(dot)vaira(at)gmail(dot)com](mailto:thierry.vaira@gmail.com)**]
