/*
  0  Modo conectividad
  1  APIKeyAcuario
  
  2 AlimentacionHorario1H
  3 AlimentacionHorario1M
  4 AlimentacionHorario1Cantidad
  5 AlimentacionHorario1Estado
  6 AlimentacionHorario2H
  7 AlimentacionHorario2M
  8 AlimentacionHorario2Cantidad
  9 AlimentacionHorario2Estado
  10 AlimentacionHorario3H
  11 AlimentacionHorario3M
  12 AlimentacionHorario3Cantidad
  13 AlimentacionHorario3Estado

  14 TemperaturaMin
  15 TemperaturaMax
  
  16 IluminacionHorarioOnH
  17 IluminacionHorarioOnM
  18 IluminacionHorarioOffH
  19 IluminacionHorarioOffM
  
  20 - 23 phMin
  24 - 27 phMax
  28 - 31 phActual
  
  32 EstadoAcuario
  
  33 diaVerificacion[1]

  40 - 43 Alimentador Capacidad
  44 - 47 Alimentador Actual
  


  100 - 130 WIFI-SSID
  131 - 160WIFI-PASS

  161 - 180 UsuarioSlot1-20
  181 - 200 PasswordSlot1-20
*/

void recuperarVariablesEEPROMtoFLASH(){
  modoConectividad = EEPROM.read(0);
  IDDISPOSITIVO_API[0] = EEPROM.read(1);
  IDDISPOSITIVO_API[1] = EEPROM.read(1);

  for(int a=0; a<12; a++){
    horariosAlimentacion[a] = EEPROM.read(a+2);
    horariosAlimentacionConf[a] = EEPROM.read(a+2);
  }
  EEPROM.get(40, horariosAlimentacion[12]);
  EEPROM.get(40, horariosAlimentacionConf[12]);
  EEPROM.get(44, horariosAlimentacion[13]);
  EEPROM.get(44, horariosAlimentacionConf[13]);

  temperatura[1] = EEPROM.read(14);
  temperatura[2] = EEPROM.read(14);
  temperatura[3] = EEPROM.read(15);
  temperatura[4] = EEPROM.read(15);

  iluminacion[1] = EEPROM.read(16);
  iluminacion[2] = EEPROM.read(16);
  iluminacion[3] = EEPROM.read(17);
  iluminacion[4] = EEPROM.read(17);
  iluminacion[5] = EEPROM.read(18);
  iluminacion[6] = EEPROM.read(18);
  iluminacion[7] = EEPROM.read(19);
  iluminacion[8] = EEPROM.read(19);
  
  EEPROM.get(20, ph[1]);
  EEPROM.get(20, ph[2]);
  EEPROM.get(24, ph[3]);
  EEPROM.get(24, ph[4]);
  EEPROM.get(28, ph[0]);

  estadoAcuario = EEPROM.read(32);

  diaVerificacion[1] = EEPROM.read(33);

  ssid = leer(ssidEEPROMStartAddr, ssidPassEEPROMSizeAddr);
  pass = leer(passEEPROMStartAddr, ssidPassEEPROMSizeAddr);
  USUARIO_API = leer(usuarioStartAddr, usuarioPasswordSize);
  PASSWORD_API = leer(passwordStartAddr, usuarioPasswordSize);

  mostrarVariables();
}

void alimentacionToEEPROM(){
  for(int a=0; a<12; a++){
    EEPROM.write(a+2, horariosAlimentacion[a]);
  }
  EEPROM.put(40, horariosAlimentacion[12]);
  EEPROM.put(44, horariosAlimentacion[13]);
  EEPROM.commit();
}

void temperaturaToEEPROM(){
  EEPROM.write(14, temperatura[1]);
  EEPROM.write(15, temperatura[3]);
  EEPROM.commit();
}

void iluminacionToEEPROM(){
  EEPROM.write(16, iluminacion[1]);  
  EEPROM.write(17, iluminacion[3]);  
  EEPROM.write(18, iluminacion[5]);  
  EEPROM.write(19, iluminacion[7]);  
  EEPROM.commit();
}

void phToEEPROM(){
  EEPROM.put(20, ph[1]);
  EEPROM.put(24, ph[3]);
  EEPROM.put(28, ph[0]);
  EEPROM.commit();
}

void modoConectividadToEEPROM(){
  EEPROM.write(0, modoConectividad);  
  EEPROM.commit();
}

void idDispositivoToEEPROM(){
  EEPROM.write(1, IDDISPOSITIVO_API[1]);  
  EEPROM.commit();
}


void mostrarVariables(){
  Serial.println("VARIABLES");  
  Serial.println("");

  Serial.print("Modo conectividad:");  
  Serial.println(modoConectividad);  
  Serial.print("APIKeyAcuario:");  
  Serial.println(IDDISPOSITIVO_API[0]); 
  Serial.println(""); 
  
  Serial.print("horario1:");  
  Serial.println(String(horariosAlimentacion[0]) + ":" + String(horariosAlimentacion[1]) + "/" + String(horariosAlimentacion[2]) + "<" + String(horariosAlimentacion[3]) + ">");  
  Serial.print("horario2:");  
  Serial.println(String(horariosAlimentacion[4]) + ":" + String(horariosAlimentacion[5]) + "/" + String(horariosAlimentacion[6]) + "<" + String(horariosAlimentacion[7]) + ">");  
  Serial.print("horario3:");  
  Serial.println(String(horariosAlimentacion[8]) + ":" + String(horariosAlimentacion[9]) + "/" + String(horariosAlimentacion[10]) + "<" + String(horariosAlimentacion[11]) + ">");  
  Serial.print("alimentadorCapacidad:");  
  Serial.println(String(horariosAlimentacion[12]));  
  Serial.print("alimentadorActual:");  
  Serial.println(String(horariosAlimentacion[13]));  
  Serial.println("");

  Serial.print("Temperatura Min:");  
  Serial.println(String(temperatura[1]));  
  Serial.print("Temperatura Max:");  
  Serial.println(String(temperatura[3]));  
  Serial.println("");

  Serial.print("Luz On:");  
  Serial.println(String(iluminacion[1]) + ":" + String(iluminacion[1]));  
  Serial.print("Luz Off:");  
  Serial.println(String(iluminacion[5]) + ":" + String(iluminacion[7]));  
  Serial.println(""); 

  Serial.print("pH Min:");  
  Serial.println(String(ph[1]));  
  Serial.print("pH Max:");  
  Serial.println(String(ph[3]));  
  Serial.print("pH Actual:");  
  Serial.println(String(ph[0])); 
  Serial.println(""); 

  Serial.print("estadoAcuario:");  
  Serial.println(estadoAcuario); 
  Serial.println(""); 

  Serial.print("fechaVerificacion Actual:");  
  Serial.println(diaVerificacion[0]); 
  Serial.print("fechaVerificacion Anterior:");  
  Serial.println(diaVerificacion[1]); 
  Serial.println(""); 

}


void eepromDefault(){
  
  EEPROM.put(0, 0);
  EEPROM.put(1, 2);

  EEPROM.put(2, 9);
  EEPROM.put(3, 10);
  EEPROM.put(4, 10);
  EEPROM.put(5, 1);
  EEPROM.put(6, 12);
  EEPROM.put(7, 30);
  EEPROM.put(8, 10);
  EEPROM.put(9, 1);
  EEPROM.put(10, 18);
  EEPROM.put(11, 30);
  EEPROM.put(12, 10);
  EEPROM.put(13, 1);
  
  EEPROM.put(14, 18);
  EEPROM.put(15, 25);

  EEPROM.put(16, 8);
  EEPROM.put(17, 10);
  EEPROM.put(18, 20);
  EEPROM.put(19, 10);

  EEPROM.put(20, 2);
  EEPROM.put(24, 7);
  EEPROM.put(28, 5);

  EEPROM.put(32, 1);

  EEPROM.put(33, 0);

  EEPROM.put(40, 10);
  EEPROM.put(44, 5);



  

  



  EEPROM.commit();
}

