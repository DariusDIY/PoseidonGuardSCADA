import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HomesiteComponent } from './home/homesite/homesite.component';
import { PanelsiteComponent } from './panel/panelsite/panelsite.component';
import { AuthGuard } from './panel/auth.guard';

const routes: Routes = [
  {
    path:'',
    component:HomesiteComponent,
    pathMatch:'full'
  },
  {
    path:'Poseidon',
    canActivate:[AuthGuard],
    loadChildren: ()=> import('./panel/panel.module').then( m=>m.PanelModule )
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
