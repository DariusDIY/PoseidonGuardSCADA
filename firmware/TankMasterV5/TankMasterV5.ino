/*******************************************************************************/
/********************************LIBRERIAS**************************************/
#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
/********************************LIBRERIAS**************************************/
/*******************************************************************************/



#define PIN_LUZ D0
#define PIN_CALENTADOR1 D3
#define PIN_CALENTADOR2 D4
#define PIN_TEMP D5
#define PIN_ALIMENTADOR D6
#define PIN_BUZZER D8

#define PIN_LDR D7

#define EstadoOn LOW
#define EstadoOff HIGH


String jsonString;

LiquidCrystal_I2C lcd(0x27, 20, 4); // Dirección I2C común: 0x27 o 0x3F
const int pinADC = A0; // Pin ADC del Wemos D1 Mini

byte relojIcon[] = {B00000,B00000,B01110,B10101,B10111,B10001,B01110,B00000};
byte gradosIcon[] = {B00100,B01010,B00100,B00000,B00000,B00000,B00000,B00000};
byte termometroIcon[] = {B00100,B01010,B01010,B01010,B01110,B01110,B01110,B00100};
byte luzIcon[] = {B00100,B01010,B10001,B10001,B10001,B01010,B01110,B01110};
byte phIcon[] = {B11100,B10100,B11100,B10000,B10101,B00111,B00111,B00101};
byte pezIcon[] = {B01000,B00100,B10110,B11101,B11111,B10110,B00100,B01000};
byte wifiIcon[] = {B00000,B01110,B10001,B00100,B01010,B00000,B00100,B00000};



int pantalla = 0;
int cursorPosicion = 1;
int botonPresionado = 0;
int modoConfiguracion = 0;





//HORARIOS DE ALIMENTACION
// hora1[0], minuto1[1], cantidad1[2], horarioEstado1[3]
// hora2[4], minuto2[5], cantidad2[6], horarioEstado2[7]
// hora3[8], minuto3[9], cantidad3[10], horarioEstado3[11]
// alimentadorCapacidad[12], alimentadorActual[13]
int horariosAlimentacion[14]= {9,30,5,1,12,15,30,1,21,30,150,0,1000,1000}; 
int horariosAlimentacionConf[14]= {9,30,5,1,12,15,30,1,21,30,150,0,1000,1000}; 
int estadoAlimentador = 0;

int horarioConfiguracioSelect = 0;


//TEMPERATURA
//TempActualPromedio[0]
//TempMinFija[1], TempMinConf[2]
//TempMaxFija[3], TempMaxConf[4]
//TempActualTermometro1[5]
//TempActualTermometro2[6]
//SelectorCalentador[7]
//EstadoCalentador1[8]
//EstadoCalentador1[9]
float temperatura[10] = {18,16,16,22,22,18,18,1,1,0};
float rangoSup,rangoInf,rangoInfCritico, rangoInfSuperCritico = 0.0;
int calentando = 0;


OneWire oneWire(PIN_TEMP);
DallasTemperature sensors(&oneWire);
// Direcciones únicas de los sensores (se detectan automáticamente)
DeviceAddress sensor1, sensor2;
float sensorTemp1, sensorTemp2 = 0.0;

// Función para imprimir la dirección de un sensor
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
}




//ILUMINACION
// estado[0]
//onHoraFija[1], onHoraConfig[2], onMinutoFija[3], OnMinutoConfig[4]
//offHoraFija[5], offHoraConfig[6], offMinutoFija[7], OffMinutoConfig[8],
//estadoSensor[9]
int iluminacion[10] = {0,9,9,5,5,21,21,35,35,0};

//NIVEL DE PH
//pH Actual[0]
//pHMinfijo[1], pHMinConfig[2]
//pHMaxfijo[3], pHMaxConfig[4]
float ph[5] = {7.5, 6.5, 6.5, 8.6, 8.6}; 


//ESTADO DE ACUARIO
int estadoAcuario = 1;


//CONECTIVIDAD
//0=SinInternet   1=ConInternetWifi
int modoConectividad = 0; 

int IDDISPOSITIVO_API[2] = {1,1}; //IDFijo[0], IDConfig[1]



/*******************************************************************************/
/**********************SERVIDOR CONFIGURACION DE RED****************************/

String ssid ="";      
String pass = "";
String USUARIO_API = "darius360";
String PASSWORD_API = "123456";

ESP8266WebServer server(80); //Puerto del servidor
int contconexion = 0;

int ssidEEPROMAddr = 100;
int passEEPROMAddr = 150;
const char *ssidConf = "TankMaster";
const char *passConf = "123456789";
String mensaje = "";
String contenidoHTML = "";


String URL_API = "https://poseidonGuard.dariusdiy.com/api/v1/";

int ssidEEPROMStartAddr = 100;
int passEEPROMStartAddr = 131;
int ssidPassEEPROMSizeAddr = 30;

int usuarioStartAddr = 161;
int passwordStartAddr = 181;
int usuarioPasswordSize = 20;




/**********************SERVIDOR CONFIGURACION DE RED****************************/
/*******************************************************************************/


int diaVerificacion[2] = {0, 0}; // Actual, Anterior
String fecha = "";
String hora = "";
int horaEnMinutos = 0;
int fechaHoraConfig[5] = {19,12,2024,9,32};

/********************************************************************************/
/*********************************RTC********************************************/
RTC_DS3231 rtc;
String diasDeLaSemana[7] = { "DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB" };
String nombreMeses[12] = { "ENE", "FEB", "MAR", "ABR", "MAY",  "JUN", "JUL","AGO","SEP","OCT","NOV","DIC" };
/*********************************RTC********************************************/
/********************************************************************************/













// Variables para la petición HTTP asíncrona
int estadoPeticion = 0;
int estadoPeticion2 = -1;
unsigned long tiempoInicioPeticion = 0;
const unsigned long timeoutPeticion = 10000;  // Timeout de 10 segundos

unsigned long temporizadorPantallaActual = 0;
const unsigned long temporizadorPantalla = 10000;  // 10 segundos


bool estadoPantalla = true;


int httpCode = 0;

WiFiClientSecure client;
HTTPClient https;
String URLPETICION;
String metodoTipo;
String cargaDatos;
String respuesta;


StaticJsonDocument<1024> jsonDoc; // Crear un buffer de 1024 bytes para el JSON



void setup() {  

  pinMode(PIN_LUZ, OUTPUT);
  pinMode(PIN_CALENTADOR1, OUTPUT);
  pinMode(PIN_CALENTADOR2, OUTPUT);
  pinMode(PIN_ALIMENTADOR, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  pinMode(PIN_LDR, INPUT);

  digitalWrite(PIN_LUZ, EstadoOff);
  digitalWrite(PIN_CALENTADOR1, EstadoOff);
  digitalWrite(PIN_CALENTADOR2, EstadoOff);
  digitalWrite(PIN_ALIMENTADOR, EstadoOff);
  digitalWrite(PIN_BUZZER, LOW);

  

  Serial.begin(115200);
  
  EEPROM.begin(512);Serial.println("Memoria EEPROM inicializada =>OK");delay(500);

  //Inicializamos el reloj RTC 
  if (!rtc.begin()){
    Serial.println("Reloj RTC no encontrado");while (1);
  }else{
      Serial.println("Reloj RTC =>OK");
  }

  // Inicializar los sensores de temperatura
  sensors.begin();
  // Detectar y mostrar las direcciones de los sensores
  if (!sensors.getAddress(sensor1, 0)) {
    Serial.println("Error: No se encontró el primer sensor DS18B20");
  }
  if (!sensors.getAddress(sensor2, 1)) {
    Serial.println("Error: No se encontró el segundo sensor DS18B20");
  }

  // Mostrar las direcciones de los sensores
  Serial.print("Sensor 1: ");
  printAddress(sensor1);
  Serial.print("Sensor 2: ");
  printAddress(sensor2);

  

  
  

  lcd.init();   
  lcd.createChar(0, relojIcon);
  lcd.createChar(1, gradosIcon); 
  lcd.createChar(2, termometroIcon);  
  lcd.createChar(3, luzIcon);
  lcd.createChar(4, phIcon);
  lcd.createChar(5, pezIcon);
  lcd.createChar(6, wifiIcon);
 
  recuperarVariablesEEPROMtoFLASH();

  String nombreSSIDLocal = "TankMaster PG-"+arregloNumerico(IDDISPOSITIVO_API[0], 2);
  
  WiFi.softAP(nombreSSIDLocal, "123456789");
  Serial.print("IP AP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", paginaconfiguracioRedWifi);
  server.on("/guardarConfiguracionWiFi", guardarConfiguracionWiFi);
  server.on("/guardarPhLeido", guardarPhLeido);

  
  server.begin();

  if(modoConectividad){
    setup_wifi();
  }

  tonoInicio();
  lcd.backlight(); 
  pantallaPrincipal();

  temporizadorPantallaActual = millis();




  
  //eepromDefault();
}






void loop() {


  /*
  if(millis() - tiempoPantallasPrincipalesAnterior >= tiempoPantallasPrincipales){
   tiempoPantallasPrincipalesAnterior = millis();
     
   if(pantalla <= 0){
    pantalla-=1;
    if(pantalla == -6){
      pantalla = 0;      
    }
    //Serial.println(pantalla);
    Pantallas(pantalla);
   }
   
 }



  if(millis() - temporizadoPantallaAnterior >= temporizadoPantalla){
    temporizadoPantallaAnterior = millis();
    if(estadoPantalla){
      estadoPantalla = false;
      Serial.println("Apagar pantalla");
      lcd.noBacklight(); estadoPantalla = false;
    }    
  }

  */
 
  
 

  


  
/*
  pantallaPrincipalTemperatura(); delay(10000);
  pantallaPrincipalPh(); delay(10000);
  pantallaPrincipalAlimentador(); delay(10000);
  pantallaPrincipalIluminacion(); delay(10000);
  pantallaPrincipalConectividad(); delay(10000);
*/


  server.handleClient();

  procesoFechaHora();
  procesoMenuNavegacion();
  procesoAlimentacion();
  procesoTemperatura();
  procesoIluminacion();
  procesoNivelpH();
  procesoPantalla();
  procesoPeticionesHtttp();
  

  
  

  delay(30);

  






  
}






