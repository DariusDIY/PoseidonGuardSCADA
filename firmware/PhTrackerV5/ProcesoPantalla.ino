
void Pantallas(int pantallaSeleccionada){
  pantalla = pantallaSeleccionada;
  resetBotonPresionado();
  switch(pantalla){
    case 0:
      pantallaInicio();      
      break;
   case 1:
      seleccionaDispositivo();      
      break;
   case 2:
      conectandoDispositivo();      
      break;
   case 3:
      dispositivoConectado();
      cursorPosicion(1);      
      break;
   case 4:
      errorConexion();      
      break;
     
    default:
      break;
  }
}


void cursorPosicion(int posicion){
  cursorPosicionSelect = posicion;
  lcd.setCursor(15, 0);
  lcd.print(" ");
  lcd.setCursor(15, 1);
  lcd.print(" ");
  switch(posicion){
   case 1:      
      lcd.setCursor(15, 0);
      lcd.print("<");     
      break;
   case 2:
      lcd.setCursor(15, 1);
      lcd.print("<");     
      break;
    default:
      break;
  }
}









/*PANTALLA DE INICIO DEL DISPOSITIVO*/
void pantallaInicio(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("***pH Tracker***");
  lcd.setCursor(4, 1);
  lcd.print("Iniciando");
  lcd.write(2);
  delay(2000);
  Pantallas(1);
}


/*PANTALLA DE SELECCION DE DISPOSITIVO TANKMASTER*/
void seleccionaDispositivo(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Disp: PG-");
  lcd.print(arregloNumerico(IDDISPOSITIVO_API, 2));
  lcd.setCursor(6, 1);
  lcd.print("^^^^^");
}

void actualizarDispositivo(){
  lcd.setCursor(9, 0);
  lcd.print("  ");
  lcd.setCursor(9, 0);
  lcd.print(arregloNumerico(IDDISPOSITIVO_API, 2));
}


void conectandoDispositivo(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando con:");
  lcd.setCursor(0, 1);
  lcd.print("PG-");
  lcd.print(arregloNumerico(IDDISPOSITIVO_API, 2));
}


void dispositivoConectado(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.print("PG-");  
  lcd.print(arregloNumerico(IDDISPOSITIVO_API, 2));
  lcd.setCursor(0, 1);
  lcd.write(1);
  lcd.print("7.5"); 

  lcd.setCursor(10, 0);
  lcd.print("Medir");  
  lcd.setCursor(7, 1);
  lcd.print("Cancelar"); 
}


void errorConexion(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ERROR CONEXION");    
  lcd.setCursor(0, 1);
  lcd.print("PG-");  
  lcd.print(arregloNumerico(IDDISPOSITIVO_API, 2));
  delay(3000);
  Pantallas(1);
}

/*PANTALLA DE LECTURA DE PH*/












/*EXTRAS*/

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
