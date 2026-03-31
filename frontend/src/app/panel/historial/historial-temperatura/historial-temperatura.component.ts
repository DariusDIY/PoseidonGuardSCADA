import { ChangeDetectorRef, Component, inject, Input, PLATFORM_ID } from '@angular/core';
import { format } from 'date-fns';
import { es } from 'date-fns/locale';
import { WebPanelService } from '../../services/web-panel.service';
import { HistorialTemperatura } from 'src/app/interfaces/web.interface';
import { isPlatformBrowser } from '@angular/common';

@Component({
  selector: 'app-historial-temperatura',
  templateUrl: './historial-temperatura.component.html',
  styleUrls: ['./historial-temperatura.component.css']
})
export class HistorialTemperaturaComponent {

  @Input() keypass!:string;
  @Input() idacuario!:number;

  TemperaturaHoyInicio!: string;
  TemperaturaHoyFin!:string;

  constructor( private ws:WebPanelService,
               private cd: ChangeDetectorRef){
      const hoy = new Date();
      this.TemperaturaHoyInicio = format(hoy, 'yyyy-MM-dd', { locale: es }) + " 00:00:00";
      this.TemperaturaHoyFin = format(hoy, 'yyyy-MM-dd', { locale: es }) + " 23:59:59";
  }

  ngOnInit(): void {
    this.getHistorialTemperatura();
    this.initChartTemperatura();
  }




  temperaturaAnteriorDia(){
    this.TemperaturaHoyInicio = this.ws.restarDias(this.TemperaturaHoyInicio, 1) + " 00:00:00";
    this.TemperaturaHoyFin = this.ws.restarDias(this.TemperaturaHoyFin, 1) + " 23:59:59";
    this.getHistorialTemperatura();
  }
  temperaturaSiguienteDia(){
    this.TemperaturaHoyInicio = this.ws.sumarDias(this.TemperaturaHoyInicio, 1) + " 00:00:00";
    this.TemperaturaHoyFin = this.ws.sumarDias(this.TemperaturaHoyFin, 1) + " 23:59:59";
    this.getHistorialTemperatura();
  }

  historialTemperatura!:HistorialTemperatura[];
  historialTemperaturaEstado!:boolean;

  chartLabelsTemperatura:string[] = [];
  chartTemperatura1:number[] = [];
  chartTemperatura2:number[] = [];
  chartCalentador1:string[] = [];
  chartCalentador2:string[] = [];

  getHistorialTemperatura(){
    let data = {
      "keypass":this.keypass,
       "idacuario":this.idacuario,
       "variable":"temperatura",
       "fechaHoraInicio":this.TemperaturaHoyInicio,
       "fechaHoraFin":this.TemperaturaHoyFin
    };
    this.ws.getHistorialAcuarioSelect(data).subscribe((resp)=>{
      //console.log(data);

      this.historialTemperatura = resp.historial;
      this.historialTemperaturaEstado = resp.estado;
      this.chartLabelsTemperatura = [];
      this.chartTemperatura1 = [];
      this.chartTemperatura2 = [];
      this.chartCalentador1 = [];
      this.chartCalentador2 = [];
      if(this.historialTemperatura){
        this.historialTemperatura.forEach(reg => {

          this.chartLabelsTemperatura.push(String(reg.registro).split(' ')[1]);
          if(reg.temperatura1 != -127){this.chartTemperatura1.push(reg.temperatura1);}
          if(reg.temperatura2 != -127){this.chartTemperatura2.push(reg.temperatura2);}
          if(reg.calentador1 == 100){this.chartCalentador1.push("ON");}else{this.chartCalentador1.push("OFF");}
          if(reg.calentador2 == 100){this.chartCalentador2.push("ON");}else{this.chartCalentador2.push("OFF");}
          this.initChartTemperatura();
        });
      }
    })
  }


  data: any;
  options: any;
  platformId = inject(PLATFORM_ID);

  initChartTemperatura() {
      if (isPlatformBrowser(this.platformId)) {
          const documentStyle = getComputedStyle(document.documentElement);
          const textColor = documentStyle.getPropertyValue('--p-text-color');
          const textColorSecondary = documentStyle.getPropertyValue('--p-text-muted-color');
          const surfaceBorder = documentStyle.getPropertyValue('--p-content-border-color');

          this.data = {
              labels: this.chartLabelsTemperatura,
              datasets: [
                  {
                      label: 'Termometro 1',
                      data: this.chartTemperatura1,
                      fill: false,
                      borderColor: 'red',
                      backgroundColor: 'red',
                      tension: 0.1
                  },
                  {
                      label: 'Termometro 2',
                      data: this.chartTemperatura2,
                      fill: false,
                      borderColor: 'blue',
                      backgroundColor: 'blue',
                      tension: 0.1
                  },
                  {
                      label: 'Calentador 1',
                      data: this.chartCalentador1,
                      borderColor: 'red',
                      backgroundColor: 'gray',
                      stepped: true,
                      yAxisID: 'y2',
                  },
                  {
                      label: 'Calentador 2',
                      data: this.chartCalentador2,
                      borderColor: 'orange',
                      backgroundColor: 'gray',
                      stepped: true,
                      yAxisID: 'y3',
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
                  },
                  y2: {
                    type: 'category',
                    labels: ['ON', 'OFF'],
                    offset: true,
                    position: 'left',
                    stack: 'temp',
                    stackWeight: 1,
                    border: {
                      color: 'red',
                    }
                  },
                  y3: {
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
