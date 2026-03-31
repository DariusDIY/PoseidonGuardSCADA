import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AuthGuard } from './auth.guard';
import { PanelsiteComponent } from './panelsite/panelsite.component';
import { PecesComponent } from './peces/peces.component';
import { HistorialComponent } from './historial/historial.component';
import { ConfiguracionesComponent } from './configuraciones/configuraciones.component';
import { PerfilComponent } from './perfil/perfil.component';



const routes: Routes = [
  {
    path: 'Panel',
    component:PanelsiteComponent,
    canActivate:[AuthGuard]
  },
  {
    path: 'Peces',
    component:PecesComponent,
    canActivate:[AuthGuard]
  },
  {
    path: 'Panel/Configuraciones/:idacuario',
    component:ConfiguracionesComponent,
    canActivate:[AuthGuard]
  },
  {
    path: 'Panel/Historial/:idacuario',
    component:HistorialComponent,
    canActivate:[AuthGuard]
  },
  {
    path: 'Perfil',
    component:PerfilComponent,
    canActivate:[AuthGuard]
  },
  {
    path:'**',
    redirectTo:''
  }
]

@NgModule({
  imports: [
    RouterModule.forChild( routes)
  ],
  exports: [
    RouterModule
  ]
})
export class PanelRoutingModule { }
