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


void tonoLecturaCorrecta() {   // Tono de inicio
    tone(PIN_BUZZER, 262,100);  // DO - C4 262 / C5 523
    delay(150);               // Esperamos 150ms
    tone(PIN_BUZZER, 349,100);  // FA - F4 349 / F5 698
    delay(150);               // Esperamos 150ms
    tone(PIN_BUZZER, 440,500);  // LA - A4 440 / A5 880
    delay(500);      // Esperamos 500ms
    digitalWrite(PIN_BUZZER, 0);
    noTone(PIN_BUZZER);        // Apagamos el buzzer
}

void tonoOk(){
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


