import { Component } from '@angular/core';
import { HomeService } from '../services/home.service';
import { Acuarista } from 'src/app/interfaces/web.interface';
import { Router } from '@angular/router';

@Component({
  selector: 'app-homesite',
  templateUrl: './homesite.component.html',
  styleUrls: ['./homesite.component.css']
})
export class HomesiteComponent {

  constructor( private ws:HomeService,
               private router:Router
             ) {

  }

  datosAcuarista!:Acuarista;

  user:string = 'darius360';
  pass:string = '123456';

  loginAcuarista(){
    console.log("Logeando...");

    this.ws.Login(this.user, this.pass).subscribe((resp)=>{
      this.datosAcuarista = resp;
      if(this.datosAcuarista.status == true){
        const token = this.datosAcuarista.key;
        this.ws.crearCookieToken(token);
        console.log("navegar panel");
        this.router.navigateByUrl('/', { skipLocationChange: true }).then(() => {
          this.router.navigate(['/Poseidon/Panel']);
        });
      }

    })
  }

}
