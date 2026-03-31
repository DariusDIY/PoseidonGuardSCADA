import { ChangeDetectorRef, Component } from '@angular/core';
import { WebPanelService } from '../services/web-panel.service';
import { Acuario } from 'src/app/interfaces/web.interface';

@Component({
  selector: 'app-panelsite',
  templateUrl: './panelsite.component.html',
  styleUrls: ['./panelsite.component.css']
})
export class PanelsiteComponent {

  keypass:string = "000";

  acuarios!:Acuario[];

  constructor( private ws:WebPanelService,
               private cdr: ChangeDetectorRef // Inyecta ChangeDetectorRef
   ){
    this.keypass = this.ws.getKeyPass();
    this.getAcuarios();

    setInterval(() => {
      this.getAcuarios();
    }, 2000); // 2000 milisegundos = 2 segundos

  }


  getAcuarios(){
    this.ws.getInfoAcuarios(this.keypass).subscribe((resp)=>{
      this.acuarios = resp;
      this.cdr.detectChanges(); // Notifica a Angular del cambio
    });
  }



  horario1 = "";
  cantidad1 = 0;
  horario2 = "";
  cantidad2 = 0;
  horario3 = "";
  cantidad3 = 0;

  tempMin = 0;
  tempMax = 0;

  phMin = 0;
  phMax = 0;

  luzHorarioOn = "";
  luzHorarioOff = "";

  agregarAcuario(){
    console.log('nuevoAcuario');

  }





  imgPreview: string | ArrayBuffer | null = null;

  onFileSelected(event: Event): void {
    const target = event.target as HTMLInputElement;

    if (target.files && target.files.length > 0) {
      const file = target.files[0];

      // Validar tipo MIME
      if (!file.type.startsWith('image/')) {
        alert('Solo se permiten archivos de imagen.');
        this.imgPreview = null;
        return;
      }

      const reader = new FileReader();
      reader.onload = () => {
        this.imgPreview = reader.result;
      };

      reader.readAsDataURL(file);
    }
  }


}
