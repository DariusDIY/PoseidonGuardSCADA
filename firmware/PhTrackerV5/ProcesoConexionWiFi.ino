void setup_wifi() {
  int contconexion = 0;
  String ssid ="TankMaster PG-"+arregloNumerico(IDDISPOSITIVO_API, 2);    
  String pass = "123456789";
  //WIFI
  WiFi.mode(WIFI_STA); //para que no inicie el SoftAP en el modo normal
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED and contconexion <15) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(500);
    Serial.print(".");
    lcd.setCursor(6, 1);
    lcd.print(" ");
    delay(500);
    lcd.setCursor(6, 1);
    lcd.write(0);
  }
  if (contconexion <15) { 
    tonoOk();  
    Serial.println("");
    Serial.print("WiFi conectado:");
    Serial.println(WiFi.localIP());
    Pantallas(3);
  }else { 
    tonoError();
    Serial.println("");
    Serial.println("Error de conexion");
    Pantallas(4);
  }
}
