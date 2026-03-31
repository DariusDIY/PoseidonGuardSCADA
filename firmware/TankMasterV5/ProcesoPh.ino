void procesoNivelpH(){
  if(ph[0] < ph[1]){
    tonoErrorPh(0);
  }

  if(ph[0] > ph[3]){
    tonoErrorPh(1);
  }
}



/*
//NIVEL DE PH
//pH Actual[0]
//pHMinfijo[1], pHMinConfig[2]
//pHMaxfijo[3], pHMaxConfig[4]
float ph[5] = {7.5, 6.5, 6.5, 8.6, 8.6}; 
*/
