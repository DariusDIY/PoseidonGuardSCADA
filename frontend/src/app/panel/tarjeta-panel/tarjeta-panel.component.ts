import { Component, Input } from '@angular/core';
import { Acuario, DiaAlimentacion } from 'src/app/interfaces/web.interface';
import { Router } from '@angular/router';

@Component({
  selector: 'app-tarjeta-panel',
  templateUrl: './tarjeta-panel.component.html',
  styleUrls: ['./tarjeta-panel.component.css']
})
export class TarjetaPanelComponent {

  constructor( private router:Router ){

  }

  @Input() Acuario!:Acuario;

  @Input() ventana:number = 0;


  temperatura = 0;


  calcularTemperatura(temperatura1:number, temperatura2:number): number{
    if( (temperatura1 == -127) && (temperatura2 == -127) ){
      this.temperatura = -127;
    }
    if ( (temperatura1 != -127) && (temperatura2 == -127) ){
      this.temperatura = temperatura1;
    }
    if ( (temperatura1 == -127) && (temperatura2 != -127) ){
      this.temperatura = temperatura2;
    }
    if ( (temperatura1 != -127) && (temperatura2 != -127) ){
      this.temperatura = (temperatura1 + temperatura2) / 2;
    }
    return this.temperatura
  }



  claseTemperatura(tempMin:number, tempMax:number):string{
    if( (this.temperatura >= tempMin) && (this.temperatura <= tempMax) ){
      return "colorVerde";
    }

    if( this.temperatura < tempMin){
      return "colorAzulClaro animate__animated animate__flash animate__infinite";
    }else{
      return "colorRojo animate__animated animate__flash animate__infinite";
    }
  }




  clasePh(valor:number, minimo:number, maximo:number):string{
    if( (valor >= minimo) && (valor <= maximo) ){
      return "colorVerde";
    }

    if( valor < minimo){
      return "colorAzulClaro animate__animated animate__flash animate__infinite";
    }else{
      return "colorRojo animate__animated animate__flash animate__infinite";
    }
  }


  claseIluminacion(estado:boolean, sensor:boolean):string{
    if(estado == sensor){
      if(estado){
        return "colorNaranja";
      }else{
        return "colorAzulClaro";
      }
    }else{
      return "colorRojo animate__animated animate__flash animate__infinite";
    }
  }



  claseHorariosAlimentacion(estado:number):string{
    if(estado>0){
      return "colorVerde";
    }else{
      return "colorNaranja";
    }
  }


  claseDiasAlimentacion(alimentacionDia:DiaAlimentacion[]|null):string{
    if(alimentacionDia == null){
      return "colorRojo";
    }else{
      if(alimentacionDia.length<3){
        return "colorNaranja";
      }
      return "colorVerde";
    }
  }

  conteoAlimentaciondia(alimentacionDia:DiaAlimentacion[]|null):string{
    let conteo = 0;
    if(alimentacionDia != null){
      conteo = alimentacionDia.length;
    }
    return "(+"+conteo+")";
  }

  claseAlimentadorCantidad(valor:number):string{
    if(valor > 50){
      return "progress-barVerde";
    }else if(valor <= 50 && valor >=25){
      return "progress-barNaranja";
    }else{
      return "progress-barRojo";
    }
  }



  calentadorEstado1:string = "";
  calentadorEstado2:string = "";
  claseCalentador(valor:number, calentador:number):string{
    if(valor == 100){
      if(calentador == 1){this.calentadorEstado1 = "ON";}
      if(calentador == 2){this.calentadorEstado2 = "ON";}
      return "colorNaranja";
    }else{
      if(calentador == 1){this.calentadorEstado1 = "OFF";}
      if(calentador == 2){this.calentadorEstado2 = "OFF";}
      return "colorAzulClaro";
    }

  }




  claseVerificarAntiguedad(modalidad:number, fechaReporte:string):string {

    if( (modalidad == 1) || (modalidad == 2) ){
      return "colorAzulClaro";
    }

    if(modalidad == 0){
      const fechaRegistro = new Date(fechaReporte);
      const fechaActual = new Date();

      // Calcular diferencia en milisegundos
      const diferenciaMs = fechaActual.getTime() - fechaRegistro.getTime();
      const diferenciaSegundos = diferenciaMs / 1000;

      // Verificar si es mayor a 15 segundos
      if(diferenciaSegundos > 11){
        return "colorRojo animate__animated animate__flash animate__infinite";
      }else{
        return "colorVerde";
      }
    }else{
      return "colorAzulClaro";
    }
  }





  irConfiguraciones(idacuario:number){
    this.router.navigate(['Poseidon/Panel/Configuraciones', idacuario]);
  }

  irHistorial(idacuario:number){
    this.router.navigate(['Poseidon/Panel/Historial', idacuario]);
  }



}
