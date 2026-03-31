import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HomesiteComponent } from './homesite/homesite.component';
import { FormsModule } from '@angular/forms';



@NgModule({
  declarations: [
    HomesiteComponent
  ],
  imports: [
    CommonModule,
    FormsModule
  ]
})
export class HomeModule { }
