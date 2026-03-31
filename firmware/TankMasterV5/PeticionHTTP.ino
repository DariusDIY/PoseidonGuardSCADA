void procesoPeticionesHtttp(){

  if(modoConectividad == 1){
    if( (pantalla == 0) && (estadoAlimentador == 0) ){
      respuesta = peticionHttp("Reporte", "POST", reportarDispositivo());
      procesarRespuesta(respuesta);
    }
    
    
  }
  
  
  
}

String peticionHttp(String funcion, String tipoPeticion, const String& datosCargados){
  URLPETICION = URL_API + "TankMaster" + "/" + funcion;
  metodoTipo = tipoPeticion;
  cargaDatos = "";
  cargaDatos = datosCargados;
  tiempoInicioPeticion = millis();  // Guardar el tiempo de inicio

  client.setInsecure();  // Ignorar certificado SSL
  if (https.begin(client, URLPETICION)) {
    https.addHeader("Content-Type", "application/json");
    https.addHeader("POSEIDON-API-KEY", "Aqui_api_key");
    httpCode = 0;  // Declarar la variable dentro de un ámbito local
    if (metodoTipo == "GET") {httpCode = https.GET();} else if (metodoTipo == "POST") {httpCode = https.POST(cargaDatos);}
    //Serial.print(httpCode);
    while(millis() - tiempoInicioPeticion < timeoutPeticion){    
      if ((httpCode == HTTP_CODE_OK) || (httpCode == HTTP_CODE_MOVED_PERMANENTLY) ) {
        respuesta = https.getString();  // Leer la respuesta del servidor
        //Serial.println("Respuesta del servidor: " + respuesta);         
        https.end();
        return respuesta;        
      }else{
        return "No hay Respuesta.";
      }
    }
    return "";
  } else {
    Serial.println("Error al iniciar la conexión HTTPS");
    Serial.println("Error en la petición HTTP"); //sin conexion
    https.end(); 
    return "";
  }
}






void procesarRespuesta(const String& respuestaServidor) {  
    
  jsonDoc.clear();
  DeserializationError error = deserializeJson(jsonDoc, respuestaServidor); // Deserializar el JSON
  
  if (error) { // Verificar si hay errores
    Serial.print("Error al parsear JSON: ");
    Serial.println(error.c_str());
    return;
  }

  // Obtener el valor de "modo"
  boolean modo = jsonDoc["modo"]; // true o false

  if (modo) {
    lcd.backlight(); estadoPantalla = true;
    // Procesar los datos solo si "modo" es true
    JsonObject datos = jsonDoc["datos"];

    // Extraer valores individuales
    const char* apiKeyAcuario = datos["apiKeyAcuario"];

    
    horariosAlimentacion[0] = datos["horario1H"];
    horariosAlimentacion[1] = datos["horario1M"];
    horariosAlimentacion[2] = datos["cantidad1"];
    
    horariosAlimentacion[4] = datos["horario2H"];
    horariosAlimentacion[5] = datos["horario2M"];
    horariosAlimentacion[6] = datos["cantidad2"];
    
    horariosAlimentacion[8] = datos["horario3H"];
    horariosAlimentacion[9] = datos["horario3M"];
    horariosAlimentacion[10] = datos["cantidad3"];
    
    horariosAlimentacion[12] = datos["alimentadorCapacidad"];
    horariosAlimentacion[13] = datos["alimentadorActual"];
    alimentacionToEEPROM();

    temperatura[1] = datos["temperaturaMin"];
    temperatura[3] = datos["temperaturaMax"];
    temperaturaToEEPROM();

    iluminacion[1] = datos["iluminacionOnTimeH"];
    iluminacion[3] = datos["iluminacionOnTimeM"];
    iluminacion[5] = datos["iluminacionOffTimeH"];
    iluminacion[7] = datos["iluminacionOffTimeM"];
    iluminacionToEEPROM();

    ph[1] = datos["phMin"];
    ph[3] = datos["phMax"];
    ph[0] = datos["phActual"];
    phToEEPROM();

    bool estado = datos["estado"];

    recuperarVariablesEEPROMtoFLASH();
    
    peticionModoActualizacionData(0);
    pantallaSincronizacion();
    tonoActualizacion();
    
    Pantallas(0);
  }
}








String reportarDispositivo(){
  jsonDoc.clear();

  JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
  datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
  datosAPI["usuario"] = USUARIO_API;
  datosAPI["password"] = PASSWORD_API;

  JsonObject temperaturaAPI = jsonDoc.createNestedObject("temperatura");
  temperaturaAPI["termometro1"] = int(temperatura[5]);
  temperaturaAPI["termometro2"] = int(temperatura[6]);
  temperaturaAPI["calentador1"] = temperatura[8];
  temperaturaAPI["calentador2"] = temperatura[9];

  JsonObject iluminacionAPI = jsonDoc.createNestedObject("iluminacion");
  iluminacionAPI["estado"] = transformarIntToBool(iluminacion[0]);
  iluminacionAPI["sensor"] = transformarIntToBool(iluminacion[9]);

  jsonString = "";
  serializeJson(jsonDoc, jsonString);

  return jsonString;
}


void reportarAlimentacion(int horarioAlimentacionRegistro, int cantidadAlimentacionRegistro){
  jsonDoc.clear();

  JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
  datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
  datosAPI["usuario"] = USUARIO_API;
  datosAPI["password"] = PASSWORD_API;

  JsonObject alimentacionAPI = jsonDoc.createNestedObject("alimentacion");
  alimentacionAPI["horario"] = horarioAlimentacionRegistro;
  alimentacionAPI["cantidad"] = cantidadAlimentacionRegistro;

  jsonString = "";
  serializeJson(jsonDoc, jsonString);

  respuesta = peticionHttp("ReporteAlimentacion", "POST", jsonString);
}


void reportarPh(){
  jsonDoc.clear();

  JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
  datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
  datosAPI["usuario"] = USUARIO_API;
  datosAPI["password"] = PASSWORD_API;

  JsonObject phAPI = jsonDoc.createNestedObject("ph");
  phAPI["phActual"] = ph[0];
  phAPI["phMin"] = ph[1];
  phAPI["phMax"] = ph[3];

  jsonString = "";
  serializeJson(jsonDoc, jsonString);

  respuesta = peticionHttp("ReportePh", "POST", jsonString);
  Serial.println(respuesta);
}



void peticionModoActualizacionData(int modoActualizacion){
 jsonDoc.clear();
 
 JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
 datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
 datosAPI["usuario"] = USUARIO_API;
 datosAPI["password"] = PASSWORD_API;

 jsonDoc["modo"] = modoActualizacion;

 jsonString = "";
 serializeJson(jsonDoc, jsonString); 
 respuesta = peticionHttp("ModoActualizacion", "POST", jsonString);
}













void peticionActualizarAlimentacion(){
 jsonDoc.clear();
 
 JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
 datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
 datosAPI["usuario"] = USUARIO_API;
 datosAPI["password"] = PASSWORD_API;

 jsonDoc["horario1"] = String(horariosAlimentacion[0]) + ":" + String(horariosAlimentacion[1]);
 jsonDoc["cantidad1"] = horariosAlimentacion[2];
 jsonDoc["horario2"] = String(horariosAlimentacion[4]) + ":" + String(horariosAlimentacion[5]);
 jsonDoc["cantidad2"] = horariosAlimentacion[6];
 jsonDoc["horario3"] = String(horariosAlimentacion[8]) + ":" + String(horariosAlimentacion[9]);
 jsonDoc["cantidad3"] = horariosAlimentacion[10];

 jsonString = "";
 serializeJson(jsonDoc, jsonString); 
 respuesta = peticionHttp("ActualizarParametrosAlimentacion", "POST", jsonString);
 if(respuesta == "true"){
  tonoActualizacion();
 }else{
  tonoError();
 }
}


void peticionActualizarTemperatura(){
 jsonDoc.clear();
 
 JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
 datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
 datosAPI["usuario"] = USUARIO_API;
 datosAPI["password"] = PASSWORD_API;

 jsonDoc["temperaturaMin"] = temperatura[1];
 jsonDoc["temperaturaMax"] = temperatura[3];

 jsonString = "";
 serializeJson(jsonDoc, jsonString); 
 respuesta = peticionHttp("ActualizarParametrosTemperatura", "POST", jsonString);
 if(respuesta == "true"){
  tonoActualizacion();
 }else{
  tonoError();
 }
}




void peticionActualizarIluminacion(){
 jsonDoc.clear();
 
 JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
 datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
 datosAPI["usuario"] = USUARIO_API;
 datosAPI["password"] = PASSWORD_API;

 jsonDoc["iluminacionOnTime"] = String(iluminacion[1]) + ":" + String(iluminacion[3]);
 jsonDoc["iluminacionOffTime"] = String(iluminacion[5]) + ":" + String(iluminacion[7]);

 jsonString = "";
 serializeJson(jsonDoc, jsonString); 
 respuesta = peticionHttp("ActualizarParametrosIluminacion", "POST", jsonString);
 if(respuesta == "true"){
  tonoActualizacion();
 }else{
  tonoError();
 }
}


void peticionActualizarPh(){
 jsonDoc.clear();
 
 JsonObject datosAPI = jsonDoc.createNestedObject("datosAPI");
 datosAPI["apiKeyAcuario"] = "PG-" + arregloNumerico(IDDISPOSITIVO_API[0], 2);
 datosAPI["usuario"] = USUARIO_API;
 datosAPI["password"] = PASSWORD_API;

 jsonDoc["phMin"] = ph[1];
 jsonDoc["phMax"] = ph[3];

 jsonString = "";
 serializeJson(jsonDoc, jsonString); 
 respuesta = peticionHttp("ActualizarParametrosPh", "POST", jsonString);
 if(respuesta == "true"){
  tonoActualizacion();
 }else{
  tonoError();
 }
}




bool transformarIntToBool(int valor){
  if(valor==1){
    return true;
  }else{
    return false;
  }
}
