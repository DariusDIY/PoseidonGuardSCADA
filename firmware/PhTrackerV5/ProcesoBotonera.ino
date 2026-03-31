int botonera(){

  if(digitalRead(PIN_BTN1)==HIGH){
    delay(100);
    return 1;
  }

  if(digitalRead(PIN_BTN2)==HIGH){
    delay(100);
    return 2;
  }
  
  if(digitalRead(PIN_BTN3)==HIGH){
    delay(100);
    return 3;
  }

  delay(100);
  return 0;
}



void resetBotonPresionado(){
  botonPresionado = 0;
}
