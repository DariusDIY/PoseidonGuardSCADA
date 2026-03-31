import { Component, EventEmitter, Input, Output } from '@angular/core';
import { Pez } from 'src/app/interfaces/web.interface';
import { WebPanelService } from '../services/web-panel.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-tarjeta-pez',
  templateUrl: './tarjeta-pez.component.html',
  styleUrls: ['./tarjeta-pez.component.css']
})
export class TarjetaPezComponent {

  constructor( private ws:WebPanelService,
               private router:Router
   ){
  }


  @Input() pezInfo!:Pez;

  @Input() idacuario:number = 0;
  @Input() keypass:string = "xxx";


  @Input() operacion!:string;

  @Output() pezEditar:EventEmitter<Pez> = new EventEmitter();





  agregarPezAcuario(){
    const data = {
      "keypass":this.keypass,
      "idacuario":this.idacuario,
      "idpez":this.pezInfo.idpez
    }
    this.ws.postAgregarPezAcuarioSelect(data).subscribe((resp)=>{
      console.log(resp);
    })
  }

  quitarPezAcuario(){
    const data = {
      "keypass":this.keypass,
      "idacuario":this.idacuario,
      "idpez":this.pezInfo.idpez
    }
    this.ws.postQuitarPezAcuarioSelect(data).subscribe((resp)=>{
      console.log(resp);
    })
  }


  editarPez(pezSeleccionado:Pez){
    this.pezEditar.emit(pezSeleccionado);
  }



}
