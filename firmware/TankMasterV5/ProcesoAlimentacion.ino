 int horarioAlimentacion1, horarioAlimentacion2, horarioAlimentacion3;

void  procesoAlimentacion(){

/*
  Serial.print("Capacidad:");
  Serial.println(horariosAlimentacion[12]);
  Serial.print("Actual:");
  Serial.println(horariosAlimentacion[13]);
*/
  horarioAlimentacion1 = transformarHorarioEnMinutos(horariosAlimentacion[0], horariosAlimentacion[1]);
  horarioAlimentacion2 = transformarHorarioEnMinutos(horariosAlimentacion[4], horariosAlimentacion[5]);
  horarioAlimentacion3 = transformarHorarioEnMinutos(horariosAlimentacion[8], horariosAlimentacion[9]);


  if( (horariosAlimentacion[3] == 0) && (horaEnMinutos >= horarioAlimentacion1) ){
    lcd.backlight(); estadoPantalla = true;
    if(verificarCantidadAlimentoEnAlimentador(horariosAlimentacion[2])){
      estadoAlimentador = 1;    
      activarAlimentador(horariosAlimentacion[2], 1);  
    }else{
      tonoErrorAlimentador();
    }       
  }

  if( (horariosAlimentacion[7] == 0) && (horaEnMinutos >= horarioAlimentacion2) ){
    lcd.backlight(); estadoPantalla = true;
    if(verificarCantidadAlimentoEnAlimentador(horariosAlimentacion[6])){
      estadoAlimentador = 1;
      activarAlimentador(horariosAlimentacion[6], 2);
    }else{
      tonoErrorAlimentador();
    }    
  }

  if( (horariosAlimentacion[11] == 0) && (horaEnMinutos >= horarioAlimentacion3) ){
    lcd.backlight(); estadoPantalla = true;
    if(verificarCantidadAlimentoEnAlimentador(horariosAlimentacion[10])){
      estadoAlimentador = 1;    
      activarAlimentador(horariosAlimentacion[10], 3);
    }else{
      tonoErrorAlimentador();
    }    
  } 
  
}


void activarAlimentador(int cantidad, int horarioAlimentador){
  
  peticionModoActualizacionData(2);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Alimentando.");
  lcd.setCursor(5, 3);
  lcd.print(horariosAlimentacion[12]);
  lcd.print("/");
  lcd.print(horariosAlimentacion[13]);
  lcd.setCursor(0, 1);
  if(horarioAlimentador == 1){lcd.print("Horario1  ");imprimirHorarioAlimentacion(1, 0);}  
  if(horarioAlimentador == 2){lcd.print("Horario2  ");imprimirHorarioAlimentacion(2, 0);}  
  if(horarioAlimentador == 3){lcd.print("Horario3  ");imprimirHorarioAlimentacion(3, 0);}  
  lcd.setCursor(0, 2);
  float animacion =  (cantidad / 20.0) * 1000.0;
  digitalWrite(PIN_ALIMENTADOR, EstadoOn); 
  tonoAlimentacion(1);
  for(int tiempoA=0; tiempoA < 20; tiempoA++){
    lcd.write(5); 
    delay(animacion);
  }  
  digitalWrite(PIN_ALIMENTADOR, EstadoOff);  
  lcd.setCursor(5, 3);
  lcd.print("Finalizada");
  tonoAlimentacion(0);

  if(horarioAlimentador == 1){horariosAlimentacion[3] = 1; horariosAlimentacionConf[3] = 1; horariosAlimentacion[13] = horariosAlimentacion[13]-horariosAlimentacion[2];alimentacionToEEPROM();recuperarVariablesEEPROMtoFLASH();reportarAlimentacion(horarioAlimentador, cantidad);}
  if(horarioAlimentador == 2){horariosAlimentacion[7] = 1;horariosAlimentacionConf[7] = 1; horariosAlimentacion[13] = horariosAlimentacion[13]-horariosAlimentacion[6];alimentacionToEEPROM();recuperarVariablesEEPROMtoFLASH();reportarAlimentacion(horarioAlimentador, cantidad);}
  if(horarioAlimentador == 3){horariosAlimentacion[11] = 1;horariosAlimentacionConf[11] = 1; horariosAlimentacion[13] = horariosAlimentacion[13]-horariosAlimentacion[10];alimentacionToEEPROM();recuperarVariablesEEPROMtoFLASH();;reportarAlimentacion(horarioAlimentador, cantidad);}
  
  alimentacionToEEPROM();
  estadoAlimentador = 0;
  mostrarVariables();

  delay(2000);
  lcd.clear(); estadoPantalla = true;
  peticionModoActualizacionData(0);
  Pantallas(0);   
}


bool verificarCantidadAlimentoEnAlimentador(int cantidadAlimentacion){
  if(horariosAlimentacion[13] >= cantidadAlimentacion){
    return true;
  }else{
    return false;
  }
}





























void resetearEstadosAlimentacionPorCambioDiario(){
  horariosAlimentacion[3] = 0;
  horariosAlimentacion[7] = 0;
  horariosAlimentacion[11] = 0;

  horariosAlimentacionConf[3] = 0;
  horariosAlimentacionConf[7] = 0;
  horariosAlimentacionConf[11] = 0;
  
  EEPROM.write(5, horariosAlimentacion[3]);
  EEPROM.write(9, horariosAlimentacion[7]);
  EEPROM.write(13, horariosAlimentacion[11]);
  EEPROM.commit();

  Serial.println("Se han reseteado las variables");

  Pantallas(0);

}
