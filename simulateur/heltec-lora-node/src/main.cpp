/**
*
* @file src/main.cpp
* @brief Simulateur esp32-lora pour eco-classroom (n salles)
* @author Thierry Vaira
* @version 0.1
*/

#include <Arduino.h>
#include <ui.h>
#include <mylora.h>
#include <Preferences.h>

/**
 * @def DEBUG
 * @brief Débugage sur la liaison série
 */
#define DEBUG

// OLED 8 lignes x 16 colonnes
// Linge de 0 à 7
#define LIGNE_TITRE 0
#define LIGNE_STATUS_WIFI  2
#define LIGNE_STATUS_LORA  3
#define LIGNE_STATUS_MQTT  4
#define LIGNE_DATA_LORA  6
#define LIGNE_DATA_MQTT  7

/**
 * @def LORA_ON
 * @brief Active la transmission LoRa
 */
#define LORA_ON
/**
 * @def PERIODE
 * @brief La période d'envoi en ms des messages LoRa pour une salle
 */
#define PERIODE   15000 // en ms
/**
 * @def DELAI
 * @brief Le délai en ms entre chaque message LoRa
 */
#define DELAI     1000 // en ms
/**
 * @def NB_SALLES
 * @brief Le nombre simulé de salles
 */
#define NB_SALLES 4

Preferences preferences; //!< pour le stockage interne
String salles[NB_SALLES] = { String("B11"), String("B20"), String("B21"), String("B22") }; //!< les noms des salles
String salle; //!< le nom d'une salle
String message; //!< le message LoRa
uint16_t luminosite; //!< valeur de l'éclairement lumineux en lux
uint8_t humidite; //!< valeur de l'humidité en %
float temperature; //!< valeur de la température en degré Celcius
uint16_t co2; //!< valeur de co2 en ppm
int indiceNiveauConfort = -1; //!< l'indice de confort
int indiceQualiteAir = 0; //!< l'indice de qualité d'air
bool etatLumieres = false; //!< état des lumières
bool etatFenetres = false; //!< état des fenêtres
bool etatOccupation = false; //!< état d'occupation

String getTemperature();
String getHumidite();
String getLuminosite();
String getCO2();
String getEtatFenetres();
String getEtatLumieres();
String getEtatOccupation();
String getIndiceNiveauConfort();
String getIndiceQualiteAir();

/**
 * @brief Initialise les ressources
 *
 * @fn setup()
 */
void setup()
{
  Serial.begin(115200);
  while (!Serial);

  #ifdef DEBUG
  Serial.println(" LoRa Simulateur");
  #endif

  initialiserOLED();
  ui.drawString(0, LIGNE_TITRE, "LoRa Simulateur");
  ui.drawString(0, LIGNE_STATUS_WIFI, salle.c_str());

  #ifdef LORA_ON
  if(initialiserLora())
  {
    #ifdef DEBUG
    Serial.println("LoRa ok");
    #endif
    ui.drawString(0, LIGNE_STATUS_LORA, "LoRa ok");
  }
  else
  {
    #ifdef DEBUG
    Serial.println("Erreur LoRa !");
    #endif
    ui.drawString(0, LIGNE_STATUS_LORA, "Erreur LoRa !");
    while(1);
  }
  #else
  #ifdef DEBUG
  Serial.println("Sans LoRa !");
  #endif
  ui.drawString(0, LIGNE_STATUS_LORA, "LoRa sans");
  #endif

  // initialise les préférences
  //preferences.begin("eeprom", false); // false pour r/w

  // initialise le générateur pseudo-aléatoire
  randomSeed(analogRead(34));
}

/**
 * @brief Boucle principale
 *
 * @fn loop()
 */
void loop()
{
  static int compteur = 0;

  if (runEvery(PERIODE))
  {
    salle = salles[random(0, NB_SALLES)];
    ui.drawString(0, LIGNE_STATUS_WIFI, salle.c_str());

    message = salle + String("/") + String("temperature") + String("/") + getTemperature();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("humidite") + String("/") + getHumidite();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("confort") + String("/") + getIndiceNiveauConfort();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("luminosite") + String("/") + getLuminosite();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("co2") + String("/") + getCO2();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("air") + String("/") + getIndiceQualiteAir();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("fenetres") + String("/") + getEtatFenetres();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("lumieres") + String("/") + getEtatLumieres();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    message = salle + String("/") + String("occupation") + String("/") + getEtatOccupation();
    #ifdef LORA_ON
    sendMessage(message.c_str());
    #endif
    #ifdef DEBUG
    Serial.print("Message LoRa envoyé : ");
    Serial.println(message);
    #endif
    delay(DELAI);

    ++compteur;
    #ifdef DEBUG
    Serial.print("Compteur messages : ");
    Serial.println(compteur);
    Serial.println("");
    #endif

    String messageCompteur = "";
    messageCompteur += compteur;
    String messageUI = "-> " + messageCompteur;
    ui.clearLine(LIGNE_DATA_LORA);
    ui.drawString(0, LIGNE_DATA_LORA, messageUI.c_str());
  }
}

/**
* @brief Retourne la luminosité simulée en lux
* @return String
*/
String getLuminosite()
{
  luminosite = random(10, 1000);
  return String(luminosite);
}

/**
* @brief Retourne la température simulée en °C
* @return String
*/
String getTemperature()
{
  float delta = (float(random(0, 200)) / 10.);
  temperature = 15.0 + delta;
  return String(temperature, 1);
}

/**
* @brief Retourne l'humidité simulée en %
* @return String
*/
String getHumidite()
{
  humidite = random(30, 80);
  return String(humidite);
}

/**
* @brief Retourne le niveau de CO2 simulé en ppm
* @return String
*/
String getCO2()
{
  // Bon : jusqu’à 1000 ppm
  // Mauvais : niveaux supérieurs à 2000 ppm
  // Plage 450 - 2450
  int taus = random(0, 5); // 1 fois sur 5
  if(taus == 1)
    co2 = 400 + random(0, 2000);
  else
    co2 = 400 + random(0, 800);
  return String(co2);
}

/**
* @brief Retourne l'état des fenêtres simulé
* @return String
*/
String getEtatFenetres()
{
  int taus = random(0, 5); // 1 fois sur 5
  if(taus == 1)
    etatFenetres = true;
  else
    etatFenetres = false;
  return String(etatFenetres);
}

/**
* @brief Retourne l'état des lumières simulé
* @return String
*/
String getEtatLumieres()
{
  int taus = random(0, 5); // 1 fois sur 5
  if(taus == 1)
  {
    etatLumieres = true;
    etatOccupation = true;
  }
  else
  {
    etatLumieres = false;
  }
  return String(etatLumieres);
}

/**
* @brief Retourne l'état d'occupation simulé d'une salle
* @return String
*/
String getEtatOccupation()
{
  int taus = random(0, 5); // 1 fois sur 5
  if(taus == 1)
      etatOccupation = true;
    else
      etatOccupation = false;
  return String(etatOccupation);
}

/**
* @brief Retourne le niveau de confort simulé
* @return String le niveau de confort simulé
*/
String getIndiceNiveauConfort()
{
  if(temperature >= 24.0)
  {
    indiceNiveauConfort = 2;
  }
  else if(temperature >= 21.0)
  {
    indiceNiveauConfort = 1;
  }
  else if(temperature >= 19.0)
  {
    indiceNiveauConfort = 0;
  }
  else
  {
    if(temperature <= 16.0)
    {
      indiceNiveauConfort = -2;
    }
    else
    {
      indiceNiveauConfort = -1;
    }
  }

  if(humidite >= 60 && temperature >= 26.0)
  {
    indiceNiveauConfort = 3;
  }
  if(humidite <= 40 && temperature <= 22.0)
  {
    indiceNiveauConfort = -3;
  }

  return String(indiceNiveauConfort);
}

/**
* @brief Retourne l'indice de qualité d'air simulé
* @return String l'indice de qualité d'air simulé
*/
String getIndiceQualiteAir()
{
  // Bon : jusqu’à 1000 ppm
  // Mauvais : niveaux supérieurs à 2000 ppm
  if(co2 >= 2200)
    indiceQualiteAir = 6;
  else if(co2 >= 2000)
    indiceQualiteAir = 5;
  else if(co2 >= 1600)
    indiceQualiteAir = 4; // médiocre
  else if(co2 >= 1000)
    indiceQualiteAir = 3; // moyen
  else
  {
    if(co2 <= 800)
      indiceQualiteAir = 1;
    else
      indiceQualiteAir = 2; // bon
  }

  return String(indiceQualiteAir);
}
