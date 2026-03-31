import { ChangeDetectorRef, Component, inject, Input, PLATFORM_ID } from '@angular/core';
import { WebPanelService } from '../../services/web-panel.service';
import { HistorialPh } from 'src/app/interfaces/web.interface';
import { isPlatformBrowser } from '@angular/common';

@Component({
  selector: 'app-historial-ph',
  templateUrl: './historial-ph.component.html',
  styleUrls: ['./historial-ph.component.css']
})
export class HistorialPhComponent {

  @Input() keypass!:string;
  @Input() idacuario!:number;

  PhTrimestreInicio!: string;
  PhTrimestreFin!: string;

  trimestreSeleccionado!:number;
  anioSeleccionado!:number;



  constructor( private ws:WebPanelService,
               private cd: ChangeDetectorRef){
      const hoy = new Date();
      const mesActual = hoy.getMonth(); // 0 (Enero) - 11 (Diciembre)
      this.anioSeleccionado = hoy.getFullYear();

      console.log("MES:"+mesActual);
      console.log("anio:"+this.anioSeleccionado);

      if( (mesActual>=0) && (mesActual<=2) ){
        // primer trimestre Ene 1 - MAR 31
        this.trimestreSeleccionado = 1;
        this.armarFechas();
      }

      if( (mesActual>=3) && (mesActual<=5) ){
        // segundo trimestre ABR 1 - JUN 30
        this.trimestreSeleccionado = 2;
        this.armarFechas();
      }

      if( (mesActual>=6) && (mesActual<=8) ){
        // tercer trimestre JUL 1 - SEP 30
        this.trimestreSeleccionado = 3;
        this.armarFechas();
      }

      if( (mesActual>=9) && (mesActual<=11) ){
        // cuarto trimestre OCT 1 - DIC 31
        this.trimestreSeleccionado = 4;
        this.armarFechas();
      }



  }

  armarFechas(){
    let mesInicioSeleccionado:String="";
    let diaInicioSeleccionado:String="01";
    let mesFinSeleccionado:String="";
    let diaFinSeleccionado:String="";

    switch(this.trimestreSeleccionado){
      case 1:
        mesInicioSeleccionado = "01";
        mesFinSeleccionado ="03";
        diaFinSeleccionado ="31";
        break;
      case 2:
        mesInicioSeleccionado = "04";
        mesFinSeleccionado ="06";
        diaFinSeleccionado ="30";
        break;
      case 3:
        mesInicioSeleccionado = "07";
        mesFinSeleccionado ="09";
        diaFinSeleccionado ="30";
        break;
      case 4:
        mesInicioSeleccionado = "10";
        mesFinSeleccionado ="12";
        diaFinSeleccionado ="31";
        break;
      default:
        break;
    }

    this.PhTrimestreInicio = String(this.anioSeleccionado) + "-" + mesInicioSeleccionado + "-" + diaInicioSeleccionado + " 00:00:00";
    this.PhTrimestreFin = String(this.anioSeleccionado) + "-" + mesFinSeleccionado + "-" + diaFinSeleccionado + " 23:59:59";
  }



  ngOnInit(): void {
    this.getHistorialPh();
    this.initChartPh();
  }

  phAnteriorTrimestre(){
    if(this.trimestreSeleccionado==1){
      this.anioSeleccionado -= 1;
      this.trimestreSeleccionado = 4;
    }else{
      this.trimestreSeleccionado -= 1;
    }
    this.armarFechas();
    this.getHistorialPh();
  }

  phSiguienteTrimestre(){
    if(this.trimestreSeleccionado==4){
      this.anioSeleccionado += 1;
      this.trimestreSeleccionado = 1;
    }else{
      this.trimestreSeleccionado += 1;
    }
    this.armarFechas();
    this.getHistorialPh();
  }


  historialPh!:HistorialPh[];
  historialPhEstado!:boolean;

  chartLabelsPh:string[] = [];
  chartPh:number[] = [];

  getHistorialPh(){
    let data = {
      "keypass":this.keypass,
       "idacuario":this.idacuario,
       "variable":"ph",
       "fechaHoraInicio":this.PhTrimestreInicio,
       "fechaHoraFin":this.PhTrimestreFin
    };
    this.ws.getHistorialAcuarioSelect(data).subscribe((resp)=>{
      console.log(data);

      this.historialPh = resp.historial;
      this.historialPhEstado = resp.estado;
      this.chartLabelsPh = [];
      this.chartPh = [];

      if(this.historialPh){
        this.historialPh.forEach(reg => {
          this.chartLabelsPh.push(String(reg.registro));
          this.chartPh.push(reg.nivel);
          this.initChartPh();
        });
      }
    })
  }


  data: any;
  options: any;
  platformId = inject(PLATFORM_ID);

  initChartPh() {
      if (isPlatformBrowser(this.platformId)) {
          const documentStyle = getComputedStyle(document.documentElement);
          const textColorSecondary = documentStyle.getPropertyValue('--p-text-muted-color');

          this.data = {
              labels: this.chartLabelsPh,
              datasets: [
                  {
                      label: 'Nivel de pH',
                      data: this.chartPh,
                      fill: false,
                      borderColor: 'red',
                      backgroundColor: 'red',
                      tension: 0.1
                  }
              ]
          };

          this.options = {
              maintainAspectRatio: false,
              aspectRatio: 0.6,
              plugins: {
                  legend: {
                      labels: {
                          color: 'black'
                      }
                  }
              },
              scales: {
                  x: {
                      ticks: {
                          color: textColorSecondary
                      },
                      grid: {
                          color: 'blue',
                          drawBorder: true
                      }
                  },
                  y: {
                    stack: 'temp',
                    stackWeight: 2,
                      ticks: {
                          color: 'black'
                      },
                      grid: {
                          color: 'blue',
                          drawBorder: true
                      }
                  }
              }
          };
          this.cd.markForCheck()
      }
  }





}
