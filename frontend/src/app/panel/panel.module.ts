import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PanelsiteComponent } from './panelsite/panelsite.component';
import { TarjetaPanelComponent } from './tarjeta-panel/tarjeta-panel.component';
import { PanelRoutingModule } from './panel.routing.module';
import { PecesComponent } from './peces/peces.component';
import { ConfiguracionesComponent } from './configuraciones/configuraciones.component';
import { HistorialComponent } from './historial/historial.component';
import { TarjetaPezComponent } from './tarjeta-pez/tarjeta-pez.component';
import { FormsModule } from '@angular/forms';
import { ChartModule } from 'primeng/chart';
import { HistorialAlimentacionComponent } from './historial/historial-alimentacion/historial-alimentacion.component';
import { HistorialTemperaturaComponent } from './historial/historial-temperatura/historial-temperatura.component';
import { HistorialIluminacionComponent } from './historial/historial-iluminacion/historial-iluminacion.component';
import { HistorialPhComponent } from './historial/historial-ph/historial-ph.component';
import { SharedModule } from '../shared/shared.module';
import { PerfilComponent } from './perfil/perfil.component';
import { DiaSemanaPipe } from './pipes/dia-semana.pipe';





@NgModule({
  declarations: [
    PanelsiteComponent,
    PecesComponent,
    ConfiguracionesComponent,
    HistorialComponent,
    TarjetaPanelComponent,
    TarjetaPezComponent,
    HistorialAlimentacionComponent,
    HistorialTemperaturaComponent,
    HistorialIluminacionComponent,
    HistorialPhComponent,
    PerfilComponent,
    DiaSemanaPipe
  ],
  exports: [
    PanelsiteComponent
  ],
  imports: [
    CommonModule,
    FormsModule,
    PanelRoutingModule,
    ChartModule,
    SharedModule
  ]
})
export class PanelModule { }
