void resetBotonPresionado(){
  botonPresionado = 0;
}

void Pantallas(int pantallaSeleccionada){
  pantalla = pantallaSeleccionada;
  resetBotonPresionado();
  switch(pantalla){
    case -1:
      pantallaPrincipalTemperatura();      
      break;
    case -2:
      pantallaPrincipalPh();      
      break;
    case -3:
      pantallaPrincipalAlimentador();      
      break;
    case -4:
      pantallaPrincipalIluminacion();      
      break;  
    case -5:
      pantallaPrincipalConectividad();      
      break;  
        
    case 0:
      pantallaPrincipal();      
      break;
    case 1:
      pantallaMenu(1);
      break;
    case 2:
      pantallaMenu(2);
      break;
    case 10:
      pantallaAlimentador();      
      break;
    case 11:
      pantallaAlimentadorHorario(horarioConfiguracioSelect);
      break;
    case 20:
      pantallaTemperatura();
      break;
    case 30:
      pantallaLuz();
      break;
    case 40:
      pantallaPh();
      break;
    case 50:
      pantallaConectividad();
      break;
    case 51:
      pantallaConectividadModo();
      break;
    case 52:
      pantallaConectividadID();
      break;
    case 53:
      pantallaConectividadWifi();
      break;
    case 60:
      pantallaHoraFecha();
      break; 
    case 100:
      pantallaIluminacion(1);
      break;   
    case 101:
      pantallaIluminacion(0);
      break;   
    default:
      break;
  }
  
}

void cursorPosicionSel(int cursorPosicionSeleccionado){
  cursorPosicion = cursorPosicionSeleccionado;
  resetBotonPresionado();
  
  if( (pantalla == 1) || (pantalla == 2) || (pantalla == 10) || (pantalla == 50) ){
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(0, 2);
    lcd.print(" ");
    lcd.setCursor(0, 3);
    lcd.print(" ");
  }
  
  
  
  switch(cursorPosicion){
    case 1:      
      lcd.setCursor(0, 1);
      lcd.print(">");
      break;
    case 2:
      lcd.setCursor(0, 2);
      lcd.print(">");
      break;
    case 3:
      lcd.setCursor(0, 3);
      lcd.print(">");
      break;
    default:
      break;
    
  }

  

  
}


void cursorPosicionSettings(int posicion, int longitud){
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print(" ");
  lcd.setCursor(19, 3);
  lcd.print(" ");
  
  resetBotonPresionado();
  if( (posicion > 0) || (posicion <= 20) ){
    lcd.setCursor(posicion-1, 2);
    for(int i=1; i<=longitud; i++){
      lcd.print("^");  
    }    
  }
  if(posicion==21){
    lcd.setCursor(0, 3);
    lcd.print(">");  
  }
  if(posicion==22){
    lcd.setCursor(19, 3);
    lcd.print("<");  
  }
  
}





void pantallaPrincipal(){
  lcd.setCursor(0, 0);
  lcd.print("              ");
  lcd.setCursor(14, 0);
  lcd.write(0);
  lcd.print("     ");

  lcd.setCursor(0, 1);
  lcd.write(5);
  imprimirHorarioAlimentacion(1, 0);
  lcd.print("  ");

  lcd.setCursor(0, 2);
  lcd.write(5);
  imprimirHorarioAlimentacion(2, 0);
  lcd.print("  ");

  lcd.setCursor(0, 3);
  lcd.write(5);
  imprimirHorarioAlimentacion(3, 0);
  lcd.print("  ");
  

  lcd.setCursor(13, 1);
  lcd.write(2);
  lcd.print(temperatura[0],0);
  lcd.write(1);
  lcd.print("C");

  lcd.setCursor(13, 2);
  lcd.write(4);
  lcd.print(ph[0],1);

  lcd.setCursor(13, 3);
  lcd.write(3);
  lcd.print(arregloIluminacion(iluminacion[0]));
}


void pantallaPrincipalTemperatura(){
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.write(2);
  lcd.print("Temperatura");
    
  lcd.setCursor(0, 1);
  lcd.print("T1:");
  lcd.print(temperatura[5],0);
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(12, 1);
  lcd.print("T2:");
  lcd.print(temperatura[6],0);
  lcd.write(1);
  lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print("C1:");
  if(int(temperatura[8])==1){lcd.print("ON");}else{lcd.print("OFF");}  
  lcd.setCursor(12, 2);
  lcd.print("C2:");
  if(int(temperatura[9])==1){lcd.print("ON");}else{lcd.print("OFF");}  

  lcd.setCursor(0, 3);
  lcd.print("Min:");
  lcd.print(temperatura[1],0);
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(12, 3);
  lcd.print("Max:");
  lcd.print(temperatura[3],0);
  lcd.write(1);
  lcd.print("C");
}

void pantallaPrincipalPh(){
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.write(4);
  lcd.print("pH");

  lcd.setCursor(0, 1);
  lcd.print("Actual:");
  lcd.print(ph[0],1);

  lcd.setCursor(0, 2);
  lcd.print("Min:");
  lcd.print(ph[1],1);
  lcd.setCursor(12, 2);
  lcd.print("Max:");
  lcd.print(ph[3],1);
}


void pantallaPrincipalAlimentador(){
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.write(5);
  lcd.print("Alimentador");

  lcd.setCursor(0, 1);
  imprimirHorarioAlimentacion(1, 0);

  lcd.setCursor(0, 2);
  imprimirHorarioAlimentacion(2, 0);

  lcd.setCursor(0, 3);
  imprimirHorarioAlimentacion(3, 0);

  lcd.setCursor(14, 1);
  lcd.print("T:");
  lcd.print(horariosAlimentacion[12]);  

  lcd.setCursor(14, 2);
  lcd.print("A:");
  lcd.print(horariosAlimentacion[13]);  
}



void pantallaPrincipalIluminacion(){
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.write(3);
  lcd.print("Luz");

  lcd.setCursor(0, 1);
  lcd.print("ON:");
  lcd.print(arregloNumerico(iluminacion[1],2));
  lcd.print(":");
  lcd.print(arregloNumerico(iluminacion[3],2));
  
  lcd.setCursor(11, 1);
  lcd.print("OFF:");
  lcd.print(arregloNumerico(iluminacion[5],2));
  lcd.print(":");
  lcd.print(arregloNumerico(iluminacion[7],2));

  lcd.setCursor(0, 2);
  lcd.print("Estado actual:");
  if(iluminacion[0]==1){lcd.print("ON");}else{lcd.print("OFF");}
  
  lcd.setCursor(0, 3);
  lcd.print("Estado sensor:");
  if(iluminacion[9]==1){lcd.print("ON");}else{lcd.print("OFF");}
}


void pantallaPrincipalConectividad(){
  lcd.clear();
    
  lcd.setCursor(0, 0);
  lcd.write(6);
  lcd.print("Conectividad");

  lcd.setCursor(15, 0);
  lcd.print("PG-01");

  lcd.setCursor(0, 1);
  lcd.print("Modo:Internet");

  lcd.setCursor(0, 2);
  lcd.print("Estado:DesConectado");
  
}




void pantallaMenu(int numero){
  if(numero == 1){
    lcd.clear();
    lcd.setCursor(8, 0);
    lcd.print("MENU     1/2");
    lcd.setCursor(1, 1);
    lcd.write(5);
    lcd.print("Alimentador");    
    lcd.setCursor(1, 2);
    lcd.write(2);
    lcd.print("Temperatura");
    lcd.setCursor(1, 3);
    lcd.write(3);
    lcd.print("Luz");
    }
  if(numero == 2){
    lcd.clear();
    lcd.setCursor(8, 0);
    lcd.print("MENU     2/2");
    lcd.setCursor(1, 1);
    lcd.write(4);
    lcd.print("Nivel de pH");
    lcd.setCursor(1, 2);
    lcd.write(6);
    lcd.print("Conectividad");
    lcd.setCursor(1, 3);
    lcd.write(0);
    lcd.print("Hora & Fecha");
    }
}



/*******************************************ALIMENTACION*******************************************/
void pantallaAlimentador(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>");
  lcd.write(5);
  lcd.print("ALIMENTADOR   1/1");
  lcd.setCursor(1, 1);
  lcd.print("Horario1 ");
  imprimirHorarioAlimentacion(1,0);
  lcd.setCursor(1, 2);
  lcd.print("Horario2 ");
  imprimirHorarioAlimentacion(2,0);
  lcd.setCursor(1, 3);
  lcd.print("Horario3 ");
  imprimirHorarioAlimentacion(3,0);
}

void pantallaAlimentadorHorario(int horarioImpreso){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>>");
  lcd.write(5);
  lcd.print("ALIMENTADOR  1/1");
  lcd.setCursor(0, 1);
  lcd.print("HORARIO");
  lcd.print(horarioConfiguracioSelect);
  lcd.print(": ");
  imprimirHorarioAlimentacion(horarioImpreso,1);

  lcd.setCursor(0, 3);
  lcd.print(" Guardar   Cancelar");
}

void ActualizarPantallaAlimentadorHorario(int horarioImpreso){
  lcd.setCursor(10, 1);
  lcd.print("  :       ");
  
  lcd.setCursor(10, 1);
  imprimirHorarioAlimentacion(horarioImpreso,1);
}

void imprimirHorarioAlimentacion(int horarioAlimentacionImpreso, int modoConfig){
  switch(horarioAlimentacionImpreso){
    case 1:
      if( modoConfig == 1 ){
        lcd.print(arregloNumerico(horariosAlimentacionConf[0],2));
        lcd.print(":");
        lcd.print(arregloNumerico(horariosAlimentacionConf[1],2));
        if(horariosAlimentacionConf[3]==1){lcd.write(5);}else{lcd.print(" ");}      
        lcd.print(arregloNumerico(horariosAlimentacionConf[2],3));
        lcd.print('"');
      }else{
        lcd.print(arregloNumerico(horariosAlimentacion[0],2));
        lcd.print(":");
        lcd.print(arregloNumerico(horariosAlimentacion[1],2));
        if(horariosAlimentacion[3]==1){lcd.write(5);}else{lcd.print(" ");}      
        lcd.print(arregloNumerico(horariosAlimentacion[2],3));
        lcd.print('"');
      }
      break;
    case 2:
      if( modoConfig == 1 ){
        lcd.print(arregloNumerico(horariosAlimentacionConf[4],2));
        lcd.print(":");
        lcd.print(arregloNumerico(horariosAlimentacionConf[5],2));
        if(horariosAlimentacionConf[7]==1){lcd.write(5);}else{lcd.print(" ");}      
        lcd.print(arregloNumerico(horariosAlimentacionConf[6],3));
        lcd.print('"');
      }else{
        lcd.print(arregloNumerico(horariosAlimentacion[4],2));
        lcd.print(":");
        lcd.print(arregloNumerico(horariosAlimentacion[5],2));
        if(horariosAlimentacion[7]==1){lcd.write(5);}else{lcd.print(" ");}      
        lcd.print(arregloNumerico(horariosAlimentacion[6],3));
        lcd.print('"');
      }      
      break;
    case 3:
      if( modoConfig == 1 ){
        lcd.print(arregloNumerico(horariosAlimentacionConf[8],2));
        lcd.print(":");
        lcd.print(arregloNumerico(horariosAlimentacionConf[9],2));
        if(horariosAlimentacionConf[11]==1){lcd.write(5);}else{lcd.print(" ");}      
        lcd.print(arregloNumerico(horariosAlimentacionConf[10],3));
        lcd.print('"');    
      }else{
        lcd.print(arregloNumerico(horariosAlimentacion[8],2));
        lcd.print(":");
        lcd.print(arregloNumerico(horariosAlimentacion[9],2));
        if(horariosAlimentacion[11]==1){lcd.write(5);}else{lcd.print(" ");}      
        lcd.print(arregloNumerico(horariosAlimentacion[10],3));
        lcd.print('"');   
      }      
      break;
    default:
      break;
    }
}






/*******************************************TEMPERATURA*******************************************/
void pantallaTemperatura(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>");
  lcd.write(2);
  lcd.print("TEMPERATURA   1/1");
  lcd.setCursor(0, 1);
  lcd.print("Min:"); 
  lcd.print(temperatura[1],0);
  lcd.write(1);
  lcd.print("C"); 
  lcd.setCursor(12, 1);
  lcd.print("Max:");
  lcd.print(temperatura[3],0);
  lcd.write(1);
  lcd.print("C");
  

  lcd.setCursor(0, 3);
  lcd.print(" Guardar   Cancelar");
}

void actualizarTemperaturaMinMax(){
  lcd.setCursor(4, 1);
  lcd.print("    ");
  lcd.setCursor(4, 1);
  lcd.print(temperatura[2],0);
  lcd.write(1);
  lcd.print("C");
  
  lcd.setCursor(16, 1);
  lcd.print("    ");
  lcd.setCursor(16, 1);
  lcd.print(temperatura[4],0);
  lcd.write(1);
  lcd.print("C");
}







/*******************************************ILUMINACION*******************************************/
void pantallaLuz(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>");
  lcd.write(3);
  lcd.print("LUZ           1/1");
  lcd.setCursor(0, 1);
  lcd.print("On:");
  lcd.setCursor(11, 1);
  lcd.print("Off:");
  
  lcd.setCursor(3, 1);
  lcd.print(arregloNumerico(iluminacion[1],2));
  lcd.print(":");
  lcd.print(arregloNumerico(iluminacion[3],2));

  lcd.setCursor(15, 1);
  lcd.print(arregloNumerico(iluminacion[5],2));
  lcd.print(":");
  lcd.print(arregloNumerico(iluminacion[7],2));

  lcd.setCursor(0, 3);
  lcd.print(" Guardar   Cancelar");
}

void actualizarHorariosOnOff(){
  lcd.setCursor(3, 1);
  lcd.print(arregloNumerico(iluminacion[2],2));
  lcd.print(":");
  lcd.print(arregloNumerico(iluminacion[4],2));

  lcd.setCursor(15, 1);
  lcd.print(arregloNumerico(iluminacion[6],2));
  lcd.print(":");
  lcd.print(arregloNumerico(iluminacion[8],2));
}




/*******************************************NIVEL DE PH*******************************************/
void pantallaPh(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>");
  lcd.write(4);
  lcd.print("NIVEL DE PH   1/1");
  lcd.setCursor(0, 1);
  lcd.print("Min:");
  lcd.setCursor(13, 1);
  lcd.print("Max:");
  
  lcd.setCursor(4, 1);
  lcd.print(ph[1], 1);

  lcd.setCursor(17, 1);
  lcd.print(ph[3], 1);

  lcd.setCursor(0, 3);
  lcd.print(" Guardar   Cancelar");
}

void actualizarPhMinMax(){
  lcd.setCursor(4, 1);
  lcd.print(ph[2], 1);

  lcd.setCursor(17, 1);
  lcd.print(ph[4], 1);
}




/*******************************************CONECTIVIDAD******************************************/
void pantallaConectividad(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>");
  lcd.write(6);
  lcd.print("CONECTIVIDAD  1/1");
  if(modoConectividad == 1){
    lcd.setCursor(1, 1);
    lcd.print("Modo (Internet)");  
    lcd.setCursor(1, 2);
    lcd.print("ID: PG-");
    lcd.print(arregloNumerico(IDDISPOSITIVO_API[0], 2));
  }else{
    lcd.setCursor(1, 1);
    lcd.print("Modo (Local)");     
  }
}

void pantallaConectividadModo(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>>");
  lcd.write(6);
  lcd.print("CONECTIVIDAD 1/1");
  lcd.setCursor(0, 1);
  if(modoConectividad == 1){
    lcd.print(">Cambiar a Local");  
  }else{
    lcd.print(">Cambiar a Internet");  
  }
}

void pantallaConectividadID(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>>");
  lcd.write(6);
  lcd.print("CONECTIVIDAD 1/1");
  lcd.setCursor(5, 1);
  lcd.print("ID:PG-");
  lcd.print(arregloNumerico(IDDISPOSITIVO_API[1], 2));
  
  
  lcd.setCursor(0, 3);
  lcd.print(" Guardar   Cancelar");
}

void actualizarPantallaConectividadID(){
  Serial.println(IDDISPOSITIVO_API[1]);
  lcd.setCursor(11, 1);
  lcd.print(arregloNumerico(IDDISPOSITIVO_API[1], 2));
}



void pantallaConectividadWifi(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>>");
  lcd.write(6);
  lcd.print("CONECTIVIDAD 1/1");  
  lcd.setCursor(0, 1);
  lcd.print("Red:");
  lcd.print(ssidConf);  
  lcd.setCursor(0, 2);
  lcd.print("Pass:");
  lcd.print(passConf); 
  lcd.setCursor(0, 3);
  lcd.print("URL: 192.168.4.1");
  modoconf();
}




/********************************************HORA&FECHA*******************************************/
void pantallaHoraFecha(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">>");
  lcd.write(0);
  lcd.print("HORA & FECHA  1/1");
  lcd.setCursor(1, 1);
  lcd.print(arregloNumerico(fechaHoraConfig[0], 2));
  lcd.print("/");
  lcd.print(nombreMeses[fechaHoraConfig[1]-1]);
  lcd.print("/");
  lcd.print(fechaHoraConfig[2]);
  
  lcd.setCursor(13, 1);
  lcd.write(0);
  lcd.print(arregloNumerico(fechaHoraConfig[3], 2));
  lcd.print(":");
  lcd.print(arregloNumerico(fechaHoraConfig[4], 2));

  lcd.setCursor(0, 3);
  lcd.print(" Guardar   Cancelar");
}

void actualizarPantallaHoraFecha(){
  lcd.setCursor(1, 1);
  lcd.print("           ");
    
  lcd.setCursor(13, 1);
  lcd.print("     ");

  lcd.setCursor(1, 1);
  lcd.print(arregloNumerico(fechaHoraConfig[0], 2));
  lcd.print("/");
  lcd.print(nombreMeses[fechaHoraConfig[1]-1]);
  lcd.print("/");
  lcd.print(fechaHoraConfig[2]);
  
  lcd.setCursor(13, 1);
  lcd.write(0);
  lcd.print(arregloNumerico(fechaHoraConfig[3], 2));
  lcd.print(":");
  lcd.print(arregloNumerico(fechaHoraConfig[4], 2));
}






/**********************************************EXTRAS*********************************************/
void pantallaGuardado(){
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("GUARDANDO.");
  
  lcd.setCursor(5, 2);
  for(int i=1; i<=10; i++){
    lcd.write(1);
    delay(150);
  }
  Pantallas(pantalla);
}

void pantallaSincronizacion(){
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("SINCRONICANDO.");
  
  lcd.setCursor(5, 2);
  for(int i=1; i<=10; i++){
    lcd.write(1);
    delay(150);
  }
  Pantallas(pantalla);
}




void pantallaIluminacion(int estado){
  if(estado == 1){
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.write(3);
    lcd.print("LUZ ENCENDIDA");
  }else{
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.write(3);
    lcd.print("LUZ APAGADA");
  }
}


String arregloNumerico(int numero, int digitos){
  String retorno = "";  
  int longitud = String(numero).length();
  int ceros = digitos - longitud;
  for(int i=1; i<=ceros; i++){
    retorno += "0";
  }
  retorno += String(numero);
  return retorno;
}

String arregloIluminacion(int valorIluminacion){
  if(valorIluminacion==1){
    return "ON ";
  }else{
    return "OFF";
  }
}



