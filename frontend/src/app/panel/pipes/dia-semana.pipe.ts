import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'diaSemana'
})
export class DiaSemanaPipe implements PipeTransform {

  private dias = ['Lunes', 'Martes', 'Miércoles', 'Jueves', 'Viernes', 'Sábado','Domingo'];
  private meses = ['Enero', 'Febrero', 'Marzo', 'Abril', 'Mayo', 'Junio', 'Julio', 'Agosto', 'Septiembre', 'Octubre', 'Noviembre', 'Diciembre'];

  transform(value: string | null): string {
    if (!value) return '';

    const fecha = new Date(value);
    if (isNaN(fecha.getTime())) return '';  // Verifica si la fecha es válida

    const diaSemana = this.dias[fecha.getDay()];
    const diaMes = fecha.getDate()+1;
    const mes = this.meses[fecha.getMonth()];
    const anio = fecha.getFullYear();

    return `${diaSemana} ${diaMes} de ${mes} de ${anio}`;
  }
}