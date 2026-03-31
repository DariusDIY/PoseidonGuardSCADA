void procesoFechaHora(){
  obtenerFechaHora();
}

void obtenerFechaHora(){
  DateTime date = rtc.now();
  fecha = diasDeLaSemana[date.dayOfTheWeek()] + " " + date.day() + "/" + nombreMeses[date.month()-1] + "/" + String(date.year() % 100);  
  hora = arregloDigitos(date.hour()) + ":" + arregloDigitos(date.minute());
  
  diaVerificacion[0] = date.day();
  horaEnMinutos = (date.hour()*60)+date.minute();
  actualizarPantallaFechaHora();
  
  if(diaVerificacion[0] != diaVerificacion[1]){
    diaVerificacion[1] = diaVerificacion[0];
    EEPROM.write(33, diaVerificacion[1]);
    EEPROM.commit();
    resetearEstadosAlimentacionPorCambioDiario();
  }  
}


void actualizarPantallaFechaHora(){
  if(pantalla == 0){
    lcd.setCursor(15, 0);
    lcd.print(hora);
    lcd.setCursor(0, 0);
    lcd.print(fecha);

    lcd.setCursor(13, 3);
    lcd.write(3);
    lcd.print(arregloIluminacion(iluminacion[0]));
  } 
}


void fijarHoraFechaConf(){
  DateTime date = rtc.now();
  fechaHoraConfig[0] = date.day();
  fechaHoraConfig[1] = date.month();
  fechaHoraConfig[2] = date.year();
  fechaHoraConfig[3] = date.hour();
  fechaHoraConfig[4] = date.minute();
}

void fijaHoraFecha(){
  rtc.adjust(DateTime(fechaHoraConfig[2], fechaHoraConfig[1], fechaHoraConfig[0], fechaHoraConfig[3], fechaHoraConfig[4], 0)); // YYYY MM DD hh mm ss  
}








String arregloDigitos(int datoIn){
  String retornoArreglado = "";
  if(datoIn<10){
    retornoArreglado = "0" + (String)datoIn;
  }else{
    retornoArreglado = (String)datoIn;    
  }
  return retornoArreglado;
}


int transformarHorarioEnMinutos(int horarioH, int horarioM){
  int calculo = (horarioH*60) + horarioM;
  return calculo;
}

