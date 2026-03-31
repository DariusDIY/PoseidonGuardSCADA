void procesoTemperatura(){
  if(pantalla == 0){obtenerTemperatura();}  
}

void obtenerTemperatura(){
  sensors.requestTemperatures();

  temperatura[5] = round(sensors.getTempC(sensor1) * 10) / 10.0; //Temperatura del sensor 1
  temperatura[6] = round(sensors.getTempC(sensor2) * 10) / 10.0; //Temperatura del sensor 2

  

  if( (temperatura[5] == -127) || (temperatura[6] == -127) ){
    if( (temperatura[5] == -127) && (temperatura[6] != -127) ){temperatura[0] = temperatura[6];Serial.println("Falla sensor 1 desconectado");}
    if( (temperatura[5] != -127) && (temperatura[6] != -127) ){temperatura[0] = temperatura[5];Serial.println("Falla sensor 1 desconectado");}
    if( (temperatura[5] == -127) && (temperatura[6] == -127) ){temperatura[0] = -1 ;Serial.println("Falla sensor 1 y sensor 2 desconectados");}
  }else{
    temperatura[0] = ( (temperatura[5] + temperatura[6]) / 2);
  }

  if(pantalla == 0){
    lcd.setCursor(14, 1);
    lcd.print("  ");
    lcd.setCursor(14, 1);
    lcd.print(temperatura[0],0);
  }

  rangoInf = temperatura[1] + 0.5;
  rangoSup = temperatura[3] - 0.5;

  rangoInfCritico = temperatura[1] - 1;
  rangoInfSuperCritico = temperatura[1] - 2;
  

  if(temperatura[0] <= rangoInf){
    calentando = 1; //calentamos
    if( (temperatura[0]<= rangoInfCritico) && (temperatura[0] > rangoInfSuperCritico) ){
      temperatura[7] = 2;
    }else if( (temperatura[0] <= rangoInfSuperCritico) ){
      tonoErrorTemperatura(3);
    }else{
      temperatura[7] = 1;
    }
  }
  if(temperatura[0] >= rangoSup){
    calentando = 0; //enfriamos
  }


  if(temperatura[0] < temperatura[1]){
    tonoErrorTemperatura(0); // alarma de temperatura baja
  }

  if(temperatura[0] > temperatura[3]){
    tonoErrorTemperatura(1); // alarma de temperatura baja
  }
  

  if(calentando == 1){
    if(temperatura[7]==1){
      digitalWrite(PIN_CALENTADOR1,EstadoOn); 
      temperatura[8] = 100;
      temperatura[9] = 0;
    }else{
      digitalWrite(PIN_CALENTADOR2,EstadoOn);  
      temperatura[8] = 0;
      temperatura[9] = 100;
    }    
  }else{
    digitalWrite(PIN_CALENTADOR1,EstadoOff);
    digitalWrite(PIN_CALENTADOR2,EstadoOff);
    temperatura[8] = 0;
    temperatura[9] = 0;
  }
  
}



//TEMPERATURA
//TempActualPromedio[0]
//TempMinFija[1], TempMinConf[2]
//TempMaxFija[3], TempMaxConf[4]
//TempActualTermometro1[5]
//TempActualTermometro2[6]
//SelectorCalentador[7]
//EstadoCalentador1[8]
//EstadoCalentador1[9]
