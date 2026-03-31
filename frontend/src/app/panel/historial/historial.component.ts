import { ChangeDetectorRef, Component } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { WebPanelService } from '../services/web-panel.service';
import { Acuario } from 'src/app/interfaces/web.interface';

@Component({
  selector: 'app-historial',
  templateUrl: './historial.component.html',
  styleUrls: ['./historial.component.css']
})
export class HistorialComponent {

  keypass!:string;
  idacuario!:number;


  constructor( private route:ActivatedRoute,
               private ws:WebPanelService,
               private cdr: ChangeDetectorRef){
    this.keypass = this.ws.getKeyPass();
    this.idacuario = +this.route.snapshot.paramMap.get('idacuario')!;

    this.getAcuarioSelect();
      setInterval(() => {
        this.getAcuarioSelect();
      }, 2000); // 2000 milisegundos = 2 segundos

  }


  acuario!:Acuario;
  pecesString: string = "";
  idacuarioConf = 0;
  horario1 = "";
  cantidad1 = 0;
  horario2 = "";
  cantidad2 = 0;
  horario3 = "";
  cantidad3 = 0;

  tempMin = 0;
  tempMax = 0;

  phMin = 0;
  phMax = 0;

  luzHorarioOn = "";
  luzHorarioOff = "";
  formularioRecopilado:boolean = false;

  getAcuarioSelect(){
    this.ws.getInfoAcuarioSelect(this.keypass, this.idacuario).subscribe((resp)=>{
      this.acuario = resp[0];


      this.pecesString = resp[0].acuarioInfo.peces;

      if(!this.formularioRecopilado){
        this.idacuarioConf = resp[0].acuarioInfo.idacuario;
        this.horario1 = resp[0].alimentacion.horarios.horario1;
        this.cantidad1 = resp[0].alimentacion.horarios.cantidad1;
        this.horario2 = resp[0].alimentacion.horarios.horario2;
        this.cantidad2 = resp[0].alimentacion.horarios.cantidad2;
        this.horario3 = resp[0].alimentacion.horarios.horario3;
        this.cantidad3 = resp[0].alimentacion.horarios.cantidad3;
        this.tempMin = resp[0].temperatura.tempMin;
        this.tempMax = resp[0].temperatura.tempMax;
        this.phMin = resp[0].ph.phMin;
        this.phMax = resp[0].ph.phMax;
        this.luzHorarioOn = resp[0].iluminacion.on;
        this.luzHorarioOff = resp[0].iluminacion.off;
        this.formularioRecopilado = true;
      }

        let nombresBuscados = this.pecesString.split(' - ');


        this.cdr.detectChanges(); // Notifica a Angular del cambio

      });
  }






}



