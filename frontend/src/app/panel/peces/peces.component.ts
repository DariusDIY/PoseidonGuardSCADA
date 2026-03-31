import { Component } from '@angular/core';
import { Pez } from 'src/app/interfaces/web.interface';
import { WebPanelService } from '../services/web-panel.service';

@Component({
  selector: 'app-peces',
  templateUrl: './peces.component.html',
  styleUrls: ['./peces.component.css']
})
export class PecesComponent {

  listaPeces!:Pez[];

  constructor( private ws:WebPanelService ){
    this.ws.getListaPeces().subscribe((resp)=>{
      this.listaPeces = resp;
    })
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


  archivo!: File;

  agregarNuevoPez() {
    if (!this.archivo) { return alert('Selecciona la foto primero'); }

    const formData = new FormData();
    formData.append('foto', this.archivo);           // 🔑 archivo

    // 🔑 resto de campos
    const infoPez = {
      keypass:         'aed53fcf3378d190a5243ca725c20a2e',
      nombreCientifico:'nombreCientificoooooooo',
      nombreComun:     'nombreComun',
      temperamento:    'temperamento',
      tempMin:         'tempMin',
      tempMax:         'tempMax',
      nivelPhMin:      'nivelPhMin',
      nivelPhMax:      'nivelPhMax',
      dieta:           'dieta',
      longitud:        'longitud'
    };

    Object.entries(infoPez)
          .forEach(([k, v]) => formData.append(k, v));

    this.ws.postNuevoPez(formData)
        .subscribe(res => console.log(res),
                   err => console.error(err));
  }


  recibirDatoPez(pezSeleccionado:Pez){
    console.log(pezSeleccionado);
  }

}
