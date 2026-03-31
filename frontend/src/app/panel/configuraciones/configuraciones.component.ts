import { ChangeDetectorRef, Component } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { WebPanelService } from '../services/web-panel.service';
import { Acuario, Pez } from 'src/app/interfaces/web.interface';

@Component({
  selector: 'app-configuraciones',
  templateUrl: './configuraciones.component.html',
  styleUrls: ['./configuraciones.component.css']
})
export class ConfiguracionesComponent {

  constructor( private route:ActivatedRoute,
               private ws:WebPanelService,
               private cdr: ChangeDetectorRef){
    this.idacuario = +this.route.snapshot.paramMap.get('idacuario')!;

    this.keypass = this.ws.getKeyPass();
    this.getAcuarioSelect();
    setInterval(() => {
      this.getAcuarioSelect();
    }, 2000); // 2000 milisegundos = 2 segundos
  }

  formularioRecopilado:boolean = false;

  idacuario!:number;

  keypass:string = "000";

  acuario!:Acuario;

  pecesLista!: Pez[] | null;
  pecesString: string = "";

  // Listas resultantes
  pecesAcuario: Pez[] = [];
  pecesNoEnAcuario: Pez[] = [];

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


  getAcuarioSelect(){
    this.ws.getInfoAcuarioSelect(this.keypass, this.idacuario).subscribe((resp)=>{
      this.acuario = resp[0];
      this.pecesLista = resp[0].pecesLista;


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
        if(this.pecesLista){
          this.pecesAcuario = this.pecesLista.filter(pez =>
            nombresBuscados.includes(pez.nombreComun)
          );
          this.pecesNoEnAcuario = this.pecesLista.filter(pez =>
            !nombresBuscados.includes(pez.nombreComun)
          );
        }

        this.cdr.detectChanges(); // Notifica a Angular del cambio

      });
  }


  guardarConfiguraciones(){
    const data ={
      "keypass":this.keypass,
      "idacuario":this.idacuarioConf,
      "alimentacionHorario1": this.horario1,
      "alimentacionCantidad1": this.cantidad1,
      "alimentacionHorario2": this.horario2,
      "alimentacionCantidad2": this.cantidad2,
      "alimentacionHorario3": this.horario3,
      "alimentacionCantidad3": this.cantidad3,
      "tempMin":this.tempMin,
      "tempMax":this.tempMax,
      "phMin":this.phMin,
      "phMax":this.phMax,
      "IluminacionHorarioOn":this.luzHorarioOn,
      "IluminacionHorarioOff":this.luzHorarioOff
    }
    this.ws.postConfiguracionAcuarioSelect(data).subscribe((resp)=>{console.log(resp);
    })
  }


  quitarPez(pezNombreComun:string){
    this.pecesString = "";
    console.log(pezNombreComun);

  }

  agregarPez(pezNombreComun:string){
    console.log(pezNombreComun);
  }



  recargarAlimentador(){
    this.ws.RecargarAlimentadorAl1000(this.keypass, this.idacuario).subscribe((resp)=>{
      console.log(resp);
    })
  }



}
