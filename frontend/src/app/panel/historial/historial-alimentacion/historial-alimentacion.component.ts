import { Component, Input } from '@angular/core';
import { format, startOfWeek, endOfWeek } from 'date-fns';
import { es } from 'date-fns/locale';
import { WebPanelService } from '../../services/web-panel.service';
import { HistorialRespuesta } from 'src/app/interfaces/web.interface';

@Component({
  selector: 'app-historial-alimentacion',
  templateUrl: './historial-alimentacion.component.html',
  styleUrls: ['./historial-alimentacion.component.css']
})
export class HistorialAlimentacionComponent {

  @Input() keypass!:string;
  @Input() idacuario!:number;


  historialAlimentacion!:any;

  AlimentacionLunesSemana!: string;
  AlimentaciondomingoSemana!:string;

  constructor( private ws:WebPanelService){
      const hoy = new Date();
      this.AlimentacionLunesSemana = format(startOfWeek(hoy, { weekStartsOn: 1 }), 'yyyy-MM-dd', { locale: es }) + " 00:00:00";
      this.AlimentaciondomingoSemana = format(endOfWeek(hoy, { weekStartsOn: 1 }), 'yyyy-MM-dd', { locale: es }) + " 23:59:59";

  }

  ngOnInit(): void {
    this.getHistorialAlimentacion();
  }



  alimentacionAnteriorSemana(){
    this.AlimentacionLunesSemana = this.ws.restarDias(this.AlimentacionLunesSemana, 7) + " 00:00:00";
    this.AlimentaciondomingoSemana = this.ws.restarDias(this.AlimentaciondomingoSemana, 7) + " 23:59:59";
    this.getHistorialAlimentacion();
  }

  alimentacionSiguienteSemana(){
    this.AlimentacionLunesSemana = this.ws.sumarDias(this.AlimentacionLunesSemana, 7) + " 00:00:00";
    this.AlimentaciondomingoSemana = this.ws.sumarDias(this.AlimentaciondomingoSemana, 7) + " 23:59:59";
    this.getHistorialAlimentacion();
  }

  formatoArreglado:any;

  getHistorialAlimentacion(){
    let data = {
      "keypass":this.keypass,
       "idacuario":this.idacuario,
       "variable":"alimentacion",
       "fechaHoraInicio":this.AlimentacionLunesSemana,
       "fechaHoraFin":this.AlimentaciondomingoSemana
    };
    this.ws.getHistorialAcuarioSelect(data).subscribe((resp)=>{
        this.historialAlimentacion = resp;
        this.formatoArreglado = this.transformarAlimentaciones(resp.historial);
    })
  }


  transformarAlimentaciones(alimentaciones: any[]): any[] {
    const resultado: any[] = [];

    const agrupadoPorFecha: { [fecha: string]: any[] } = {};

    if(alimentaciones==null){
      return [];
    }

    alimentaciones.forEach((item) => {
      const [fecha, hora] = item.registro.split(' ');

      if (!agrupadoPorFecha[fecha]) {
        agrupadoPorFecha[fecha] = [];
      }

      agrupadoPorFecha[fecha].push({
        horario: item.horario,
        cantidad: item.cantidad,
        registro: hora
      });
    });



    for (const fecha in agrupadoPorFecha) {
      const alimentacionesDelDia = agrupadoPorFecha[fecha];

      const horarios:any = {
        horario1: [],
        horario2: [],
        horario3: []
      };

      alimentacionesDelDia.forEach((a) => {
        const key = `horario${a.horario}`;
        if (horarios[key as keyof typeof horarios]) {
          horarios[key as keyof typeof horarios].push(a);
        }
      });



      for (const key of ['horario1', 'horario2', 'horario3']) {
        if (horarios[key as keyof typeof horarios].length === 0) {
          horarios[key as keyof typeof horarios].push(null);
        }
      }

      resultado.push({
        fecha,
        horarios
      });
    }

    return resultado;
  }



}
