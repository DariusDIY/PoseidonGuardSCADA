/*
 Boton 1 = cancel= 800 - 850
 Boton 2 = down  = 600 - 650
 Boton 3 = up    = 350 - 400
 Boton 4 = OK    = 150 - 200
 Boton 5 = Menu  = 0   -  50
*/

int botonera(){
  int valorADC = analogRead(pinADC); // Leer el valor del ADC
  //Serial.println(valorADC);

  if(valorADC > 1000){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 1;
  }

  if(valorADC > 800){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 2;
  }

  if(valorADC > 600){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 3;
  }

  if(valorADC > 400){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 4;
  }

  if(valorADC > 200){ 
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1); 
    return 5;
  }else{
    return 0;
  }
}
