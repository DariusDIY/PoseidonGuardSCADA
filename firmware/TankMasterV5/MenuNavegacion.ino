void procesoMenuNavegacion(){
  botonPresionado = botonera();

  /*NAVEGACION MENU PRINCIPAL*/
  if( (pantalla == 0) && (botonPresionado==5) ){ //Va al menu principal   
    Pantallas(1);
    cursorPosicionSel(1);
    peticionModoActualizacionData(1);
  }


  if( (pantalla == 1) || (pantalla == 2) ){
    if( (botonPresionado == 2) && (cursorPosicion == 1) ){
      cursorPosicionSel(2);
    }
    if( (botonPresionado == 2) && (cursorPosicion == 2) ){
      cursorPosicionSel(3);
    }
    if( (pantalla == 1) && (botonPresionado == 2) && (cursorPosicion == 3) ){
      Pantallas(2);
      cursorPosicionSel(1);
    }
    if( (pantalla == 2) && (botonPresionado == 3) && (cursorPosicion == 1) ){
      Pantallas(1);
      cursorPosicionSel(3);
    }
    if( (botonPresionado == 3) && (cursorPosicion == 3) ){
      cursorPosicionSel(2);
    }
    if( (botonPresionado == 3) && (cursorPosicion == 2) ){
      cursorPosicionSel(1);
    }    
  }


  if( (botonPresionado == 1) && ( (pantalla == 1) || (pantalla == 2) ) ){  //Volver a pantalla principal desde el menu
    Pantallas(0);
    cursorPosicionSel(0);
    peticionModoActualizacionData(0);
  }
   
  /*ENTRANDO A MENUS*/
  if( (pantalla == 1) && (botonPresionado == 4) && (cursorPosicion == 1) ){
    Pantallas(10); //Alimentacion
    cursorPosicionSel(1);
  }
  if( (pantalla == 1) && (botonPresionado == 4) && (cursorPosicion == 2) ){
    Pantallas(20); //Temperatura    
  }
  if( (pantalla == 1) && (botonPresionado == 4) && (cursorPosicion == 3) ){
    Pantallas(30); //Luz       
  }
  if( (pantalla == 2) && (botonPresionado == 4) && (cursorPosicion == 1) ){
    Pantallas(40); //pH  
  }
  if( (pantalla == 2) && (botonPresionado == 4) && (cursorPosicion == 2) ){
    Pantallas(50); //Conectividad  
    cursorPosicionSel(1);
  }
  if( (pantalla == 2) && (botonPresionado == 4) && (cursorPosicion == 3) ){    
    fijarHoraFechaConf();
    Pantallas(60); //Hora & Fecha
  }

  /*NAVEGACION ALIMENTADOR*/ 
  if(pantalla == 10){
    if( (botonPresionado == 2) && (cursorPosicion == 1) ){
      cursorPosicionSel(2);   
    }
    if( (botonPresionado == 2) && (cursorPosicion == 2) ){    
      cursorPosicionSel(3);   
    }
    if( (botonPresionado == 3) && (cursorPosicion == 3) ){
      cursorPosicionSel(2);   
    }
    if( (botonPresionado == 3) && (cursorPosicion == 2) ){
      cursorPosicionSel(1);   
    }

    if( (botonPresionado == 4) && (cursorPosicion <= 3) ){
      horarioConfiguracioSelect = cursorPosicion;
      Pantallas(11);       
    }
  
    if( (botonPresionado == 1) ){
      Pantallas(1);   
      cursorPosicionSel(1);   
    }
  }

  if(pantalla == 11){  //EDITANDO ALIMENTACION
    if( (botonPresionado == 1) && (modoConfiguracion == 0) ){
      Pantallas(10);   
      cursorPosicionSel(horarioConfiguracioSelect);   
    }
    if( (botonPresionado == 5) && (modoConfiguracion == 0) ){
      modoConfiguracion = 1;
      cursorPosicionSettings(11, 2);
    }
    if( modoConfiguracion > 0 ){
      if( modoConfiguracion == 1 ){ //hora seleccionada
        if( botonPresionado == 4 ){modoConfiguracion = 2; cursorPosicionSettings(14, 2);}
        
        if( botonPresionado == 3 ){ //+            
            if( (horarioConfiguracioSelect == 1) && (horariosAlimentacionConf[0] < 23) ){
              horariosAlimentacionConf[0]+= 1;
            }   
            if( (horarioConfiguracioSelect == 2) && (horariosAlimentacionConf[4] < 23) ){
              horariosAlimentacionConf[4]+= 1; 
            }  
            if( (horarioConfiguracioSelect == 3) && (horariosAlimentacionConf[8] < 23) ){
              horariosAlimentacionConf[8]+= 1; 
            }    
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);
        }  
        if( botonPresionado == 2 ){ //-           
            if( (horarioConfiguracioSelect == 1) && (horariosAlimentacionConf[0] > 0) ){
              horariosAlimentacionConf[0]-= 1;
            }  
            if( (horarioConfiguracioSelect == 2) && (horariosAlimentacionConf[4] > 0) ){
              horariosAlimentacionConf[4]-= 1;
            }  
            if( (horarioConfiguracioSelect == 3) && (horariosAlimentacionConf[8] > 0) ){
              horariosAlimentacionConf[8]-= 1;
            } 
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);     
        } 
      }
      
      if( modoConfiguracion == 2 ){ //minuto seleccionado
        if( botonPresionado == 4 ){modoConfiguracion = 3; cursorPosicionSettings(16, 1);}
        if( botonPresionado == 1 ){modoConfiguracion = 1; cursorPosicionSettings(11, 2);}       
        if( botonPresionado == 3 ){ //+            
            if( (horarioConfiguracioSelect == 1) && (horariosAlimentacionConf[1] < 59) ){
              horariosAlimentacionConf[1]+= 1;
            }   
            if( (horarioConfiguracioSelect == 2) && (horariosAlimentacionConf[5] < 59) ){
              horariosAlimentacionConf[5]+= 1; 
            }  
            if( (horarioConfiguracioSelect == 3) && (horariosAlimentacionConf[9] < 59) ){
              horariosAlimentacionConf[9]+= 1; 
            }    
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);
        }
        if( botonPresionado == 2 ){ //-
            if( (horarioConfiguracioSelect == 1) && (horariosAlimentacionConf[1] > 0) ){
              horariosAlimentacionConf[1]-= 1;
            }   
            if( (horarioConfiguracioSelect == 2) && (horariosAlimentacionConf[5] > 0) ){
              horariosAlimentacionConf[5]-= 1; 
            }  
            if( (horarioConfiguracioSelect == 3) && (horariosAlimentacionConf[9] > 0) ){
              horariosAlimentacionConf[9]-= 1; 
            }    
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);
        }   
      }
      
      if( modoConfiguracion == 3 ){ //estado seleccionado
        if( botonPresionado == 4 ){modoConfiguracion = 4; cursorPosicionSettings(17, 4);}
        if( botonPresionado == 1 ){modoConfiguracion = 2; cursorPosicionSettings(14, 2);} 
        if( (botonPresionado == 3 ) ){ //+            
            if( horarioConfiguracioSelect == 1 ){horariosAlimentacionConf[3] = 1;}
            if( horarioConfiguracioSelect == 2 ){horariosAlimentacionConf[7] = 1;}
            if( horarioConfiguracioSelect == 3 ){horariosAlimentacionConf[11] = 1;}
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);
        }
        if( (botonPresionado == 2 ) ){ //-            
            if( horarioConfiguracioSelect == 1 ){horariosAlimentacionConf[3] = 0;}
            if( horarioConfiguracioSelect == 2 ){horariosAlimentacionConf[7] = 0;}
            if( horarioConfiguracioSelect == 3 ){horariosAlimentacionConf[11] = 0;}
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);
        }              
      }
      
      if( modoConfiguracion == 4 ){ //cantidad seleccionada
        if( botonPresionado == 4 ){modoConfiguracion = 5; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 1 ){modoConfiguracion = 3; cursorPosicionSettings(16, 1);}
        if( botonPresionado == 3 ){ //+            
            if( (horarioConfiguracioSelect == 1) && (horariosAlimentacionConf[2] < 255) ){
              horariosAlimentacionConf[2]+= 1;
            }   
            if( (horarioConfiguracioSelect == 2) && (horariosAlimentacionConf[6] < 255) ){
              horariosAlimentacionConf[6]+= 1; 
            }  
            if( (horarioConfiguracioSelect == 3) && (horariosAlimentacionConf[10] < 255) ){
              horariosAlimentacionConf[10]+= 1; 
            }    
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);
        }
        if( botonPresionado == 2 ){ //-
            if( (horarioConfiguracioSelect == 1) && (horariosAlimentacionConf[2] > 0) ){
              horariosAlimentacionConf[2]-= 1;
            }   
            if( (horarioConfiguracioSelect == 2) && (horariosAlimentacionConf[6] > 0) ){
              horariosAlimentacionConf[6]-= 1; 
            }  
            if( (horarioConfiguracioSelect == 3) && (horariosAlimentacionConf[10] > 0) ){
              horariosAlimentacionConf[10]-= 1; 
            }    
            ActualizarPantallaAlimentadorHorario(horarioConfiguracioSelect);
        }
      }
      
      if( modoConfiguracion == 5 ){ //guardar seleccionado
        if( botonPresionado == 4 ){modoConfiguracion = 6; cursorPosicionSettings(22, 0);}
        if( botonPresionado == 1 ){modoConfiguracion = 4; cursorPosicionSettings(17, 4);}
        if( botonPresionado == 5 ){          
          for(int e=0; e<12; e++){
            horariosAlimentacion[e] = horariosAlimentacionConf[e];
          }              
          modoConfiguracion = 0;
          alimentacionToEEPROM();
          if(modoConectividad == 1){
            peticionActualizarAlimentacion();
          }   
          pantallaGuardado();
          Pantallas(10);   
          cursorPosicionSel(horarioConfiguracioSelect);
        }
      }
      if( modoConfiguracion == 6 ){ //cancelar seleccionado
        if( botonPresionado == 1 ){modoConfiguracion = 5; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 5 ){          
          for(int e=0; e<12; e++){
            horariosAlimentacionConf[e] = horariosAlimentacion[e];
          }                        
          modoConfiguracion = 0;                          
          Pantallas(10);   
          cursorPosicionSel(horarioConfiguracioSelect);
        }
      }
    }
  }


  /*NAVEGACION TEMPERATURA*/  
  if(pantalla == 20){
    if( (botonPresionado == 1) && (modoConfiguracion == 0) ){
      Pantallas(1);   
      cursorPosicionSel(2);   
    }
    if( (botonPresionado == 5) && (modoConfiguracion == 0) ){
      modoConfiguracion = 1;
      cursorPosicionSettings(5, 4);
    }

    if( modoConfiguracion > 0 ){
      if( modoConfiguracion == 1 ){ //minimo seleccionado
        if( botonPresionado == 4 ){modoConfiguracion = 2; cursorPosicionSettings(17, 4);}        
        if( (botonPresionado == 3) && (temperatura[2] < temperatura[4]-1) ){temperatura[2]+= 1; actualizarTemperaturaMinMax();} //+
        if( (botonPresionado == 2) && (temperatura[2] > 1) ){temperatura[2]-= 1; actualizarTemperaturaMinMax();} //-
      }
      if( modoConfiguracion == 2 ){ //maximo seleccionado
        if( botonPresionado == 4 ){modoConfiguracion = 3; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 1 ){modoConfiguracion = 1; cursorPosicionSettings(5, 4);}   
        if( (botonPresionado == 3) &&(temperatura[4] < 50) ){temperatura[4]+= 1; actualizarTemperaturaMinMax();} //+
        if( (botonPresionado == 2) &&(temperatura[4] > temperatura[2]+1) ){temperatura[4]-= 1; actualizarTemperaturaMinMax();} //-                         
      }
      if( modoConfiguracion == 3 ){ //guardar seleccionado
        if( botonPresionado == 4 ){modoConfiguracion = 4; cursorPosicionSettings(22, 0);}  
        if( botonPresionado == 1 ){modoConfiguracion = 2; cursorPosicionSettings(17, 4);}                          
        if( botonPresionado == 5 ){ // guardar
          modoConfiguracion = 0;
          temperatura[1]=temperatura[2];
          temperatura[3]=temperatura[4];
          temperaturaToEEPROM();
          if(modoConectividad == 1){
            peticionActualizarTemperatura();
          }                   
          pantallaGuardado();
          }
      }
      if( modoConfiguracion == 4 ){ //cancelar seleccionado
        if( botonPresionado == 1 ){modoConfiguracion = 3; cursorPosicionSettings(21, 0);}          
        if( botonPresionado == 5 ){          
          temperatura[2]=temperatura[1];
          temperatura[4]=temperatura[3];
          modoConfiguracion = 0;
          actualizarTemperaturaMinMax();
          cursorPosicionSettings(0, 0);
        }
      }
    }
     
  }



  /*NAVEGACION LUZ*/  
  if(pantalla == 30){
    if( (botonPresionado == 1) && (modoConfiguracion == 0) ){
      Pantallas(1);   
      cursorPosicionSel(3);   
    }
    if( (botonPresionado == 5) && (modoConfiguracion == 0) ){
      modoConfiguracion = 1;  
      cursorPosicionSettings(4, 2);          
    }

    if( modoConfiguracion > 0 ){
      if(modoConfiguracion == 1){ //ON hora seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 2; cursorPosicionSettings(7, 2);}
        if( (botonPresionado == 3) && (iluminacion[2] < 23) ){iluminacion[2]+= 1; actualizarHorariosOnOff();} //+
        if( (botonPresionado == 2) && (iluminacion[2] > 0) ){iluminacion[2]-= 1; actualizarHorariosOnOff();} //-
      }
      if(modoConfiguracion == 2){ //ON minuto seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 3; cursorPosicionSettings(16, 2);}
        if( botonPresionado == 1 ){modoConfiguracion = 1; cursorPosicionSettings(4, 2);}   
        if( (botonPresionado == 3) && (iluminacion[4] < 59) ){iluminacion[4]+= 1; actualizarHorariosOnOff();} //+
        if( (botonPresionado == 2) && (iluminacion[4] > 0) ){iluminacion[4]-= 1; actualizarHorariosOnOff();} //-     
      }
      if(modoConfiguracion == 3){ //OFF hora seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 4; cursorPosicionSettings(19, 2);}
        if( botonPresionado == 1 ){modoConfiguracion = 2; cursorPosicionSettings(7, 2);}
        if( (botonPresionado == 3) && (iluminacion[6] < 23) ){iluminacion[6]+= 1; actualizarHorariosOnOff();} //+
        if( (botonPresionado == 2) && (iluminacion[6] > 0) ){iluminacion[6]-= 1; actualizarHorariosOnOff();} //-        
      }
      if(modoConfiguracion == 4){ //OFF minuto seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 5; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 1 ){modoConfiguracion = 3; cursorPosicionSettings(16, 2);}
        if( (botonPresionado == 3) && (iluminacion[8] < 59) ){iluminacion[8]+= 1; actualizarHorariosOnOff();} //+
        if( (botonPresionado == 2) && (iluminacion[8] > 0) ){iluminacion[8]-= 1; actualizarHorariosOnOff();} //-     
      }
      if(modoConfiguracion == 5){ //guardar seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 6; cursorPosicionSettings(22, 0);}
        if( botonPresionado == 1 ){modoConfiguracion = 4; cursorPosicionSettings(19, 2);}
        if( botonPresionado == 5 ){ // guardar
          modoConfiguracion = 0;
          iluminacion[1]=iluminacion[2];
          iluminacion[3]=iluminacion[4];
          iluminacion[5]=iluminacion[6];
          iluminacion[7]=iluminacion[8];
          iluminacionToEEPROM();
          if(modoConectividad == 1){
            peticionActualizarIluminacion();
          }     
          pantallaGuardado();
        }
      }
      if(modoConfiguracion == 6){ //cancelar seleccionado        
        if( botonPresionado == 1 ){modoConfiguracion = 5; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 5 ){
          iluminacion[2]=iluminacion[1];
          iluminacion[4]=iluminacion[3];
          iluminacion[6]=iluminacion[5];
          iluminacion[8]=iluminacion[7];
          modoConfiguracion = 0;
          actualizarHorariosOnOff();
          cursorPosicionSettings(0, 0);
        }
      }
    }    
  }


  /*NAVEGACION PH*/  
  if(pantalla == 40){
    if( (botonPresionado == 1) && (modoConfiguracion == 0) ){
      Pantallas(2);   
      cursorPosicionSel(1);   
    }
    if( (botonPresionado == 5) && (modoConfiguracion == 0) ){
      modoConfiguracion = 1;  
      cursorPosicionSettings(5, 3);          
    }

    if( modoConfiguracion > 0 ){
      if(modoConfiguracion == 1){ //ph min seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 2; cursorPosicionSettings(18, 3);}
        if( (botonPresionado == 3) && (ph[2] < 9.0) && (ph[2] < ph[4]-0.2) ){ph[2]+= 0.1; actualizarPhMinMax();} //+
        if( (botonPresionado == 2) && (ph[2] > 5.1) ){ph[2]-= 0.1; actualizarPhMinMax();} //-
      }
      if(modoConfiguracion == 2){ //ph max seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 3; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 1 ){modoConfiguracion = 1; cursorPosicionSettings(5, 3);}
        if( (botonPresionado == 3) && (ph[4] < 9.0) ){ph[4]+= 0.1; actualizarPhMinMax();} //+
        if( (botonPresionado == 2) && (ph[4] > 5.1) && (ph[4] > ph[2]+0.1) ){ph[4]-= 0.1; actualizarPhMinMax();} //-
        
      }
      if(modoConfiguracion == 3){ //guardar seleccionado        
        if( botonPresionado == 4 ){modoConfiguracion = 4; cursorPosicionSettings(22, 0);}
        if( botonPresionado == 1 ){modoConfiguracion = 2; cursorPosicionSettings(18, 3);}
        if( botonPresionado == 5 ){ // guardar
          modoConfiguracion = 0;
          ph[1]=ph[2];
          ph[3]=ph[4];
          phToEEPROM();
          if(modoConectividad == 1){
            peticionActualizarPh();
          } 
          pantallaGuardado();
        }        
      }
      if(modoConfiguracion == 4){ //cancelar seleccionado        
        if( botonPresionado == 1 ){modoConfiguracion = 3; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 5 ){ // cancelar
          modoConfiguracion = 0;
          ph[2]=ph[1];
          ph[4]=ph[3];
          actualizarPhMinMax();
          cursorPosicionSettings(0, 0);
        } 
      }
    }
  }


  /*NAVEGACION CONECTIVIDAD*/  
  if(pantalla == 50){
    if( (botonPresionado == 1) ){
      Pantallas(2);   
      cursorPosicionSel(2);   
    }

    if( (botonPresionado == 2) && (cursorPosicion == 1) && (modoConectividad == 1) ){
      cursorPosicionSel(2);   
    }
    if( (botonPresionado == 3) && (cursorPosicion == 2) && (modoConectividad == 1) ){
      cursorPosicionSel(1);   
    }

    if( (botonPresionado == 4) && (cursorPosicion == 1) ){
      Pantallas(51);
      cursorPosicionSel(1);
    }

    if( (botonPresionado == 4) && (cursorPosicion == 2) ){
      modoConfiguracion = 0;
      Pantallas(52);      
    }

  }

  if(pantalla == 51){ //Cambiar de modo
    if( (botonPresionado == 5) ){
      if(modoConectividad == 0){
        modoConectividad = 1;
        modoConectividadToEEPROM();
        pantallaGuardado();
        Pantallas(53);        
      }else{
        modoConectividad = 0;
        modoConectividadToEEPROM();
        pantallaGuardado();
        Pantallas(50);
        cursorPosicionSel(1);
      }
    }
  }

  if(pantalla == 52){ //Cambiar ID de dispositivo

    if( ( botonPresionado == 1 ) && (modoConfiguracion == 0) ){ //Retroceder
      Pantallas(50);
      cursorPosicionSel(2);
    }
    
    if( ( botonPresionado == 5 ) && (modoConfiguracion == 0) ){ //Entrar en modo configuracion
      modoConfiguracion = 1;
      cursorPosicionSettings(9, 5);
    }
    
    if( modoConfiguracion > 0 ){
      if( modoConfiguracion == 1 ){ //ID seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 2; cursorPosicionSettings(21, 0);}
        if( (botonPresionado == 3) && (IDDISPOSITIVO_API[1] < 99) ){ IDDISPOSITIVO_API[1] += 1; actualizarPantallaConectividadID();}//+
        if( (botonPresionado == 2) && (IDDISPOSITIVO_API[1] >  1) ){ IDDISPOSITIVO_API[1] -= 1; actualizarPantallaConectividadID();}//-
      }
      
      if( modoConfiguracion == 2 ){ //guardar seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 3; cursorPosicionSettings(22, 0);}
        if( botonPresionado == 1 ){ modoConfiguracion = 1; cursorPosicionSettings(9, 5);}
        if( botonPresionado == 5 ){
          modoConfiguracion = 0;
          cursorPosicionSettings(0, 0);
          IDDISPOSITIVO_API[0] = IDDISPOSITIVO_API[1];
          idDispositivoToEEPROM();
          pantallaGuardado();
          Pantallas(52);
        }
      }
      
      if( modoConfiguracion == 3 ){ //cancelar seleccionado
        if( botonPresionado == 1 ){ modoConfiguracion = 2; cursorPosicionSettings(21, 0);}
        if( botonPresionado == 5 ){
          modoConfiguracion = 0;
          cursorPosicionSettings(0, 0);
          IDDISPOSITIVO_API[1] = IDDISPOSITIVO_API[0];
          Pantallas(52);
        }
      }
    }
   
  }





  /*HORA Y FECHA*/
  if(pantalla == 60){
    if( (botonPresionado == 1) && (modoConfiguracion == 0) ){
      Pantallas(2);   
      cursorPosicionSel(3);   
    }
    if( (botonPresionado == 5) && (modoConfiguracion == 0) ){      
      modoConfiguracion = 1;  
      cursorPosicionSettings(2, 2);          
    }

    if( modoConfiguracion > 0 ){
      if( modoConfiguracion == 1 ){ //dia seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 2; cursorPosicionSettings(5, 3);}
        if( (botonPresionado == 3) && (fechaHoraConfig[0]<31) ){ fechaHoraConfig[0] += 1; actualizarPantallaHoraFecha();} //+
        if( (botonPresionado == 2) && (fechaHoraConfig[0]>1) ){ fechaHoraConfig[0] -= 1; actualizarPantallaHoraFecha();} //-     
      }

      if( modoConfiguracion == 2 ){ //mes seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 3; cursorPosicionSettings(9, 4);}
        if(botonPresionado == 1){ modoConfiguracion = 1; cursorPosicionSettings(2, 2);}
        if( (botonPresionado == 3) && (fechaHoraConfig[1]<12) ){ fechaHoraConfig[1] += 1; actualizarPantallaHoraFecha();} //+
        if( (botonPresionado == 2) && (fechaHoraConfig[1]>1) ){ fechaHoraConfig[1] -= 1; actualizarPantallaHoraFecha();} //-     
      }

      if( modoConfiguracion == 3 ){ //anio seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 4; cursorPosicionSettings(15, 2);}
        if(botonPresionado == 1){ modoConfiguracion = 2; cursorPosicionSettings(5, 3);}
        if( (botonPresionado == 3) && (fechaHoraConfig[2]<9999) ){ fechaHoraConfig[2] += 1; actualizarPantallaHoraFecha();} //+
        if( (botonPresionado == 2) && (fechaHoraConfig[2]>2025) ){ fechaHoraConfig[2] -= 1; actualizarPantallaHoraFecha();} //-             
      }

      if( modoConfiguracion == 4 ){ //hora seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 5; cursorPosicionSettings(18, 2);}
        if(botonPresionado == 1){ modoConfiguracion = 3; cursorPosicionSettings(9, 4);}
        if( (botonPresionado == 3) && (fechaHoraConfig[3]<23) ){ fechaHoraConfig[3] += 1; actualizarPantallaHoraFecha();} //+
        if( (botonPresionado == 2) && (fechaHoraConfig[3]>0) ){ fechaHoraConfig[3] -= 1; actualizarPantallaHoraFecha();} //-             
      }

      if( modoConfiguracion == 5 ){ //minutos seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 6; cursorPosicionSettings(21, 0);}
        if(botonPresionado == 1){ modoConfiguracion = 4; cursorPosicionSettings(15, 2);}
        if( (botonPresionado == 3) && (fechaHoraConfig[4]<59) ){ fechaHoraConfig[4] += 1; actualizarPantallaHoraFecha();} //+
        if( (botonPresionado == 2) && (fechaHoraConfig[4]>0) ){ fechaHoraConfig[4] -= 1; actualizarPantallaHoraFecha();} //-             
      }

      if( modoConfiguracion == 6 ){ //guardar seleccionado
        if(botonPresionado == 4){ modoConfiguracion = 7; cursorPosicionSettings(22, 0);}
        if(botonPresionado == 1){ modoConfiguracion = 5; cursorPosicionSettings(18, 2);}
        if(botonPresionado == 5){ modoConfiguracion = 0; fijaHoraFecha(); Pantallas(60);}        
      }

      if( modoConfiguracion == 7 ){ //cancelar seleccionado
        if(botonPresionado == 1){ modoConfiguracion = 6; cursorPosicionSettings(21, 0);}
        if(botonPresionado == 5){ modoConfiguracion = 0; fijarHoraFechaConf(); Pantallas(60);}
      }
    }
  
  }
  
  
}
