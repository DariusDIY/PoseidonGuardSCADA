void Sonar(int cantidad){         // Función para sonar un tono en la cantidad requerida
  for(int i=0; i<cantidad; i++){  // Realizamos un loop con la cantidad de tonos
    tone(PIN_BUZZER, 349,100);  // FA - F4 349 / F5 698
    delay(100);                   // Esperamos 250ms
    noTone(PIN_BUZZER);        // Apagamos el buzzer
    digitalWrite(PIN_BUZZER, 0);
    delay(100);                   // Esperamos 250ms
  }  
}


void tonoInicio() {   // Tono de inicio
    tone(PIN_BUZZER, 262,100);  // DO  - C4 262
    delay(100);               
    tone(PIN_BUZZER, 330,100);  // MI  - E4 330
    delay(100);               
    tone(PIN_BUZZER, 392,100);  // SOL - G4 392
    delay(100);  
    tone(PIN_BUZZER, 523,500);  // DO  - C5 523
    delay(600);        
    tone(PIN_BUZZER, 523,100);  // DO  - C5 523
    delay(100);        
    tone(PIN_BUZZER, 392,100);  // SOL - G4 392
    delay(100);        
    tone(PIN_BUZZER, 330,100);  // MI  - E4 330
    delay(100);        
    tone(PIN_BUZZER, 262,500);  // DO  - C4 262
    delay(500);        
    noTone(PIN_BUZZER);        // Apagamos el buzzer
}


void tonoOk() {   // Tono de inicio
    tone(PIN_BUZZER, 262,100);  // DO - C4 262 / C5 523
    delay(150);               // Esperamos 150ms
    tone(PIN_BUZZER, 349,100);  // FA - F4 349 / F5 698
    delay(150);               // Esperamos 150ms
    tone(PIN_BUZZER, 440,500);  // LA - A4 440 / A5 880
    delay(500);      // Esperamos 500ms
    digitalWrite(PIN_BUZZER, 0);
    noTone(PIN_BUZZER);        // Apagamos el buzzer
}

void tonoActualizacion(){
    tone(PIN_BUZZER, 262,150); // DO4 - C4
    delay(150);
    tone(PIN_BUZZER, 349,150); // FA4 - F4
    delay(150);
    tone(PIN_BUZZER, 440,150); // LA4 - A4
    delay(150);
    tone(PIN_BUZZER, 523,150); // DO5 - C5
    delay(150);
    tone(PIN_BUZZER, 440,150); // LA4 - A4
    delay(150);
    tone(PIN_BUZZER, 523,500); // DO5 - C5
    delay(500);
    noTone(PIN_BUZZER);
}


void tonoError(){           // Función de tono de error
    tone(PIN_BUZZER, 110,100);  // LA - A - 440
    delay(150);               // Esperamos 150ms
    tone(PIN_BUZZER, 87,100);  // FA - F - 349
    delay(150);               // Esperamos 150ms
    tone(PIN_BUZZER, 65,1000);  // DO - C -262
    delay(500);               // Esperamos 500ms
    digitalWrite(PIN_BUZZER, 0);
    noTone(PIN_BUZZER);
}

void tonoErrorTermometro(){           // Función de tono de error
  tone(PIN_BUZZER, 33,500); // Suena una frecuencia de 33 con duración de 2 segundos
  delay(500);              // Esperamos 2 segundos
  noTone(PIN_BUZZER);        // Apagamos el buzzer
}


void tonoAlimentacion(int estado){
  if(estado == 1){
    tone(PIN_BUZZER, 262,300);  // DO - C4
    delay(150);                 
    tone(PIN_BUZZER, 349,300);  // FA - F4
    delay(150);                 
    tone(PIN_BUZZER, 440,300);  // LA - A4
    delay(150);                 
    tone(PIN_BUZZER, 523,500);  // DO - C5
    delay(500);                 
    noTone(PIN_BUZZER);  
  }else{    
    tone(PIN_BUZZER, 523,300);  // DO - C5
    delay(150);                     
    tone(PIN_BUZZER, 440,300);  // LA - A4
    delay(150);                 
    tone(PIN_BUZZER, 349,300);  // FA - F4
    delay(150);                 
    tone(PIN_BUZZER, 262,500);  // DO - C4
    delay(500);                 
    noTone(PIN_BUZZER);  
  }  
}


void tonoLuz(int estado){
  if(estado == 1){
    tone(PIN_BUZZER, 262,300);  // DO - C4
    delay(150);                 
    tone(PIN_BUZZER, 311,500);  // RE# - D4#
    delay(500);                 
    noTone(PIN_BUZZER);  
  }else{
    tone(PIN_BUZZER, 311,300);  // RE# - D4#
    delay(150);                 
    tone(PIN_BUZZER, 262,500);  // DO - C4
    delay(500);                 
    noTone(PIN_BUZZER);
  }
}

void tonoErrorTemperatura(int estado){
  if(estado == 0){ // Temperatura Baja
    tone(PIN_BUZZER, 932,250);  // LA# - A#5
    delay(500);                 
    tone(PIN_BUZZER, 1568,500);  // SOL - G6
    delay(500);     
    noTone(PIN_BUZZER);  
  }else if (estado == 1){    // Temperatura alta
    tone(PIN_BUZZER, 1568,250);  // SOL - G6
    delay(500);                 
    tone(PIN_BUZZER, 932,500);  // LA# - A#5
    delay(500);     
    noTone(PIN_BUZZER);
  }else{
    tone(PIN_BUZZER, 33,750);  // DO - C1
    delay(500);    
    noTone(PIN_BUZZER);  
  }
}

void tonoErrorPh(int estado){
  if(estado == 0){ // ph Bajo
    tone(PIN_BUZZER, 440,250);  // LA - A4
    delay(500);                 
    tone(PIN_BUZZER, 220,500);  // LA - A3
    delay(500);     
    noTone(PIN_BUZZER);  
  }else{    // ph alto
    tone(PIN_BUZZER, 220,250);  // LA - A3
    delay(500);                 
    tone(PIN_BUZZER, 440,500);  // LA - A4
    delay(500);     
    noTone(PIN_BUZZER);
  }

  void tonoErrorIluminacion(){           // Función de tono de error
    tone(PIN_BUZZER, 65,1000);  // DO - C -262
    delay(500);               // Esperamos 500ms
    tone(PIN_BUZZER, 65,1000);  // DO - C -262
    delay(500);               // Esperamos 500ms
    digitalWrite(PIN_BUZZER, 0);
    noTone(PIN_BUZZER);
}
}

void tonoErrorAlimentador(){
  tone(PIN_BUZZER, 110,1000);  // LA - A2
  delay(500);                 
  noTone(PIN_BUZZER); 
}
