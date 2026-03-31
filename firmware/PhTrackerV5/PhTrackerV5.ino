
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define PH_PIN A0

#define PIN_BUZZER D0

#define PIN_BTN1 D7
#define PIN_BTN2 D6
#define PIN_BTN3 D8


int botonPresionado = 0;
int pantalla = 0;
int cursorPosicionSelect = 0;
int IDDISPOSITIVO_API = 1;

float pHLeidoActual = 0.0;
float pHLeidoAnterior = 0.0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C común: 0x27 o 0x3F

byte wifiIcon[] = {B00000,B01110,B10001,B00100,B01010,B00000,B00100,B00000};
byte phIcon[] = {B11100,B10100,B11100,B10000,B10101,B00111,B00111,B00101};
byte okIcon[] = {B00000,B00000,B00001,B00010,B10100,B01000,B00000,B00000};

WiFiClient client;
HTTPClient http;
  
int httpCode = 0;
String respuesta;

void setup() {
  
  Serial.begin(115200);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BTN1, INPUT);
  pinMode(PIN_BTN2, INPUT);
  pinMode(PIN_BTN3, INPUT);

  

  
  lcd.init(); 
  lcd.createChar(0, wifiIcon);
  lcd.createChar(1, phIcon);
  lcd.createChar(2, okIcon);
  

  lcd.backlight(); 

  Serial.println("Dispositivo Iniciado");

  tonoInicio();

  Pantallas(0); //era 0

  

}

void loop() {
  if( pantalla == 3 ){
    procesoLecturaPh();
  }  

  
  botonPresionado = botonera();
  
  if( (pantalla == 1) ){
    if(botonPresionado == 1){
      Sonar(1);
      IDDISPOSITIVO_API += 1;
      if(IDDISPOSITIVO_API==100){IDDISPOSITIVO_API = 1;}
      actualizarDispositivo();
    }
    if(botonPresionado == 2){
      Sonar(1);
      IDDISPOSITIVO_API -= 1;
      if(IDDISPOSITIVO_API==0){IDDISPOSITIVO_API = 99;}
      actualizarDispositivo();
    }
    if(botonPresionado == 3){
      Sonar(1);
      Pantallas(2);
      setup_wifi();
    }
  }

 if( pantalla == 3){
  if( (botonPresionado == 1) && (cursorPosicionSelect == 2) ){
    Sonar(1);
    cursorPosicion(1);
  }
  if( (botonPresionado == 2) && (cursorPosicionSelect == 1) ){
    Sonar(1);
    cursorPosicion(2);
  }
 


  if( (botonPresionado == 3) && (cursorPosicionSelect == 1) ){
    Sonar(1);
    Serial.println("Funcion de guardado de ph");
    peticionHttp();
    Sonar(2);
    WiFi.disconnect();
    Pantallas(1);
    
  }
  if( (botonPresionado == 3) && (cursorPosicionSelect == 2) ){
    Sonar(3);
    WiFi.disconnect();
    delay(1000);
    Pantallas(1);
  }

  
 
 }

  

}






