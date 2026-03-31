/*************************************************************************************/
/*********************************HEADER HTML*****************************************/
String headerHTML = "<!DOCTYPE html>"
"<html lang='es'>"
"<head>"
"<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"<title>Tank Master - Configuración </title>"
"<style>"  
"body{margin-bottom: 50px;}"
".menu{display: flex;justify-content: center;align-items: center; background:#1A2A4F}"
".titulo{background: #1A2A4F;color: #ffffff;text-decoration: none;border: 2px #ffffff solid; text-align: center;padding: 10px; border-radius: 5px;}"
".contenido{display: flex;justify-content: center;}"
".canales{width: 250px;display: grid;}"
"hr{width: 100%;margin-top: 25px;border: 2px solid #1A2A4F;}"
"h2{color: #1A2A4F;text-align: center;margin-bottom: 5px}"
"label{color: #1A2A4F;font-weight: bold;}"
"button{background-color: #ffffff;color: #1A2A4F;height: 50px;cursor: pointer;border: 3px solid #1A2A4F; border-radius: 5px;}"
"button:hover{font-weight: bold; background-color: #1A2A4F;color: #ffffff;}"
"</style>"
"</head>"
"<body>";
/*********************************HEADER HTML*****************************************/
/*************************************************************************************/


/*************************************************************************************/
/*********************************FOOTER HTML*****************************************/
String footerHTML = "</body>"
"</html>";
/*********************************FOOTER HTML*****************************************/
/*************************************************************************************/


/*************************************************************************************/
/*******************************CONFIGURACION HTML************************************/
String contenidoConfiguracionRedWifiHTMLArmada(){
  contenidoHTML = "<div class='menu'>"
    "<h1 class='titulo'>POSEIDON GUARD TANKMASTER</h1>"
    "</div>"
    "<hr>"
    "<div class='contenido'>"
    "<form action='guardarConfiguracionWiFi' method='get'>"
    "<div class='canales'>"
    "<h1 class='titulo'>PG - 0"+String(IDDISPOSITIVO_API[0])+"</h1>"
    "<h2>API</h2>"
    "<label>USUARIO:</label>"
    "<input type='text' name='USUARIO_API' value='"+USUARIO_API+"'>"
    "<label>PASSWORD:</label>"
    "<input type='password' name='PASSWORD_API' value='"+PASSWORD_API+"'>"
    "<h2>WI-FI</h2>"
    "<label>SSID:</label><input type='text' name='ssid' value='"+ssid+"'><br>"
    "<label>PASSWORD:</label><input type='password' name='pass' value='"+pass+"'><br>"
    "<button type='submit'>GUARDAR</button>"
    "</div></form></div>";
    return contenidoHTML;
}

/*******************************CONFIGURACION HTML************************************/
/*************************************************************************************/








/*************************************************************************************/
/*******************************MODO CONFIGURACION************************************/
void modoconf() {
  WiFi.softAP(ssidConf, passConf);
  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("IP dispositivo: ");
  Serial.println(myIP);
  Serial.println("WebServer iniciado...");
  

  server.on("/", paginaconfiguracioRedWifi);
  server.on("/guardarConfiguracionWiFi", guardarConfiguracionWiFi);

  
  server.begin();

  while (true) {
      botonPresionado = botonera();
      server.handleClient();
      if( pantalla == 53){
        if( botonPresionado == 1 ){Serial.println("Reiniciando");ESP.restart();} // Reinicia el dispositivo
      }
         
      delay(3000);
  }
}
/*******************************MODO CONFIGURACION************************************/
/*************************************************************************************/





/*************************************************************************************/
/**************************PAGINA DE CONFIGURACION WIFI*******************************/
void paginaconfiguracioRedWifi() {
  server.send(200, "text/html", headerHTML + contenidoConfiguracionRedWifiHTMLArmada() + footerHTML); 
}
/**************************PAGINA DE CONFIGURACION WIFI*******************************/
/*************************************************************************************/




/*************************************************************************************/
/******************************GUARDAR CONFIGURACION**********************************/
void guardarConfiguracionWiFi() {  

  grabar(ssidEEPROMStartAddr,ssidPassEEPROMSizeAddr,server.arg("ssid"));
  grabar(passEEPROMStartAddr,ssidPassEEPROMSizeAddr,server.arg("pass"));

  grabar(usuarioStartAddr,usuarioPasswordSize,server.arg("USUARIO_API"));
  grabar(passwordStartAddr,usuarioPasswordSize,server.arg("PASSWORD_API"));

  Serial.println("Guardado correctamente");

  ssid = leer(ssidEEPROMStartAddr, ssidPassEEPROMSizeAddr);
  pass = leer(passEEPROMStartAddr, ssidPassEEPROMSizeAddr);
  USUARIO_API = leer(usuarioStartAddr, usuarioPasswordSize);
  PASSWORD_API = leer(passwordStartAddr, usuarioPasswordSize);

  Serial.print("SSID:");
  Serial.println(ssid);
  Serial.print("PASS:");
  Serial.println(pass);
  Serial.print("USUARIO_API:");
  Serial.println(USUARIO_API);
  Serial.print("PASSWORD_API:");
  Serial.println(PASSWORD_API);
  delay(1000);
  paginaconfiguracioRedWifi();
}
/******************************GUARDAR CONFIGURACION**********************************/
/*************************************************************************************/





/*************************************************************************************/
/***********************************GUARDAR PH****************************************/
void guardarPhLeido() {  

  Serial.print("ph:");
  Serial.println(server.arg("ph"));
  ph[0] = server.arg("ph").toFloat();
  phToEEPROM();
  recuperarVariablesEEPROMtoFLASH();
  lcd.backlight();
  Pantallas(0);
  reportarPh();

  String respuestaJSON = "{\"phGuardado\": " + server.arg("ph") + "}";
  server.send(200, "application/json", respuestaJSON); 
  
}
/***********************************GUARDAR PH****************************************/
/*************************************************************************************/



/*************************************************************************************/
/**************************FUNCION PARA GUARDAR EN EEPROM*****************************/
void grabar(int addrStart, int tamanoTotal, String stringIn) {
  int tamano = stringIn.length(); 
  char inchar[tamanoTotal]; 
  stringIn.toCharArray(inchar, tamano+1);
  for (int i = 0; i < tamano; i++) {
    EEPROM.write(addrStart+i, inchar[i]);
  }
  for (int i = tamano; i < tamanoTotal; i++) {
    EEPROM.write(addrStart+i, 255);
  }
  EEPROM.commit();
}
/**************************FUNCION PARA GUARDAR EN EEPROM*****************************/
/*************************************************************************************/


/*************************************************************************************/
/****************************FUNCION PARA LEER LA EEPROM******************************/
String leer(int addrStart, int tamanoTotal) {
   byte lectura;
   String strlectura;
   for (int i = addrStart; i < addrStart+tamanoTotal; i++) {
      lectura = EEPROM.read(i);
      if (lectura != 255) {
        strlectura += (char)lectura;
      }
   }
   return strlectura;
}
/****************************FUNCION PARA LEER LA EEPROM******************************/
/*************************************************************************************/



/*************************************************************************************/
/**********************************SETUP WIFI*****************************************/
void setup_wifi() {
  int contconexion = 0;
  //WIFI
  //WiFi.mode(WIFI_STA); //para que no inicie el SoftAP en el modo normal
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(250);
    Serial.print(".");
  }
  if (contconexion <50) {   
      Serial.println("");
      Serial.print("WiFi conectado:");
      Serial.println(WiFi.localIP());
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
}
/**********************************SETUP WIFI*****************************************/
/*************************************************************************************/
