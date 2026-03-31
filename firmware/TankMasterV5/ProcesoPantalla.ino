void procesoPantalla(){


  if(millis() >= temporizadorPantallaActual + temporizadorPantalla){
    if(pantalla != 0){
        lcd.clear();
        Pantallas(0);
        peticionModoActualizacionData(0);  
        temporizadorPantallaActual = millis();    
      }else{
        pantallaOff();    
      }    
  }

  
}


void pantallaOff(){
 lcd.noBacklight(); estadoPantalla = false; 
}

void pantallaOn(){
 lcd.backlight(); estadoPantalla = true; 
}
