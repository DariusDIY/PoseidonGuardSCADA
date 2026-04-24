

void procesoIluminacion(){
  int horarioIluminacionOn = transformarHorarioEnMinutos(iluminacion[1], iluminacion[3]);
  int horarioIluminacionOff = transformarHorarioEnMinutos(iluminacion[5], iluminacion[7]);

  verificarSensorLuminosidad();
  

  if( (horaEnMinutos >= horarioIluminacionOn) && (horaEnMinutos < horarioIluminacionOff) && (iluminacion[0] == 0) ){
    lcd.backlight(); estadoPantalla = true;
    Pantallas(100);
    digitalWrite(PIN_LUZ, EstadoOn);
    iluminacion[0] = 1;
    tonoLuz(1);    
    delay(3000);
    verificarSensorLuminosidad();
    Pantallas(0);
  }else if( ((horaEnMinutos < horarioIluminacionOn) || (horaEnMinutos >= horarioIluminacionOff) ) && (iluminacion[0] == 1) ){
    lcd.backlight(); estadoPantalla = true;
    Pantallas(101);
    digitalWrite(PIN_LUZ, EstadoOff);  
    iluminacion[0] = 0;
    tonoLuz(0);    
    delay(3000);
    verificarSensorLuminosidad();
    Pantallas(0);
  }   
}


void verificarSensorLuminosidad(){
  iluminacion[9] = digitalRead(PIN_LDR);

  if (iluminacion[9] == HIGH) {
    //Serial.println("💡 Luz ENCENDIDA");
    if( (iluminacion[9] == HIGH) && (iluminacion[0] == 0)){
      tonoErrorIluminacion();
    }
  } else {
    //Serial.println("💤 Luz APAGADA");
    if( (iluminacion[9] == LOW) && (iluminacion[0] == 1)){
      tonoErrorIluminacion();
    }
  }
}
