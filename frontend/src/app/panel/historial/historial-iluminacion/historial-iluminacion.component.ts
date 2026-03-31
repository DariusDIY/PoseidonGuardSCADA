import { ChangeDetectorRef, Component, inject, Input, PLATFORM_ID } from '@angular/core';
import { format, startOfWeek, endOfWeek } from 'date-fns';
import { es } from 'date-fns/locale';
import { WebPanelService } from '../../services/web-panel.service';
import { HistorialIluminacion } from 'src/app/interfaces/web.interface';
import { isPlatformBrowser } from '@angular/common';

@Component({
  selector: 'app-historial-iluminacion',
  templateUrl: './historial-iluminacion.component.html',
  styleUrls: ['./historial-iluminacion.component.css']
})
export class HistorialIluminacionComponent {


  @Input() keypass!:string;
  @Input() idacuario!:number;

  IluminacionLunesSemana!: string;
  IluminaciondomingoSemana!:string;

  constructor( private ws:WebPanelService,
               private cd: ChangeDetectorRef){
      const hoy = new Date();
      this.IluminacionLunesSemana = format(startOfWeek(hoy, { weekStartsOn: 1 }), 'yyyy-MM-dd', { locale: es }) + " 00:00:00";
      this.IluminaciondomingoSemana = format(endOfWeek(hoy, { weekStartsOn: 1 }), 'yyyy-MM-dd', { locale: es }) + " 23:59:59";
  }

  ngOnInit(): void {
    this.getHistorialIluminacion();
    this.initChartIluminacion();
  }


  iluminacionAnteriorSemana(){
    this.IluminacionLunesSemana = this.ws.restarDias(this.IluminacionLunesSemana, 7);
    this.IluminaciondomingoSemana = this.ws.restarDias(this.IluminaciondomingoSemana, 7);
    this.getHistorialIluminacion();
  }

  iluminacionSiguienteSemana(){
    this.IluminacionLunesSemana = this.ws.sumarDias(this.IluminacionLunesSemana, 7);
    this.IluminaciondomingoSemana = this.ws.sumarDias(this.IluminaciondomingoSemana, 7);
    this.getHistorialIluminacion();
  }



  historialIluminacion!:HistorialIluminacion[];
  historialIluminacionEstado!:boolean;

  chartLabelsIluminacion:string[] = [];
  chartIluminacion:string[] = [];
  chartSensor:string[] = [];

  getHistorialIluminacion(){
    let data = {
      "keypass":this.keypass,
       "idacuario":this.idacuario,
       "variable":"iluminacion",
       "fechaHoraInicio":this.IluminacionLunesSemana,
       "fechaHoraFin":this.IluminaciondomingoSemana
    };
    this.ws.getHistorialAcuarioSelect(data).subscribe((resp)=>{
      this.historialIluminacion = resp.historial;
      this.historialIluminacionEstado = resp.estado;
      this.chartIluminacion = [];
      this.chartSensor = [];
      this.chartLabelsIluminacion = [];
      if(this.historialIluminacion){

        this.historialIluminacion.forEach(reg => {
          if(reg.estado == true){
            this.chartIluminacion.push("ON");
            this.chartLabelsIluminacion.push(String(reg.registro));
          }else{
            this.chartIluminacion.push("OFF");
            this.chartLabelsIluminacion.push(String(reg.registro));
          }
          if(reg.sensor == true){
            this.chartSensor.push("ON");
          }else{
            this.chartSensor.push("OFF");
          }
          this.initChartIluminacion();
        });
      }
    })
  }


  data: any;
  options: any;
  platformId = inject(PLATFORM_ID);

  initChartIluminacion() {
      if (isPlatformBrowser(this.platformId)) {
          const documentStyle = getComputedStyle(document.documentElement);
          const textColorSecondary = documentStyle.getPropertyValue('--p-text-muted-color');

          this.data = {
              labels: this.chartLabelsIluminacion,
              datasets: [
                  {
                      label: 'Iluminación',
                      data: this.chartIluminacion,
                      borderColor: 'orange',
                      backgroundColor: 'orange',
                      stepped: true,
                  },
                  {
                      label: 'Sensor',
                      data: this.chartSensor,
                      borderColor: 'red',
                      backgroundColor: 'red',
                      stepped: true,
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
                    type: 'category',
                    labels: ['ON', 'OFF'],
                    offset: true,
                    position: 'left',
                    stack: 'temp',
                    stackWeight: 1,
                    border: {
                      color: 'orange',
                    }
                  }
              }
          };
          this.cd.markForCheck()
      }
  }





}
