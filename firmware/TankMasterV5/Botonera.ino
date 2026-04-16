/*
 Boton 1 = cancel= 205 - 182
 Boton 2 = down  = 409 - 386
 Boton 3 = up    = 614 - 591
 Boton 4 = OK    = 818 - 795
 Boton 5 = Menu  = 1023 -1000
*/

int botonera(){
  int valorADC = analogRead(pinADC); // Leer el valor del ADC
  //Serial.println(valorADC);

  if(valorADC > 1000){ 
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1); 
    return 5;
  }

  if(valorADC > 795){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 4;
  }

  if(valorADC > 591){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 3;
  }
  
  if(valorADC > 386){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 2;
  }
  
  if(valorADC > 182){
    lcd.backlight();
    temporizadorPantallaActual = millis();
    Sonar(1);
    return 1;
  }else{
    return 0;
  }

  

  

  

  
}
