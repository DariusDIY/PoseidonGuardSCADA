import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, Router } from '@angular/router';
import { CookieService } from 'ngx-cookie-service';
import { WebPanelService } from './services/web-panel.service';
import { Observable, map, catchError, of } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AuthGuard implements CanActivate {

  token!:string;
  autorizacion:boolean = false;

  constructor(
              private cookieService:CookieService,
              private router: Router,
              private ws:WebPanelService) {
                this.token = this.ws.getKeyPass();
              }

  canActivate(route: ActivatedRouteSnapshot): Observable<boolean> {
    return this.ws.getAutenticacionToken(this.token).pipe(
      map((resp) => {
        this.autorizacion = resp;
        return this.autorizacion; // Asegúrate de que `resp` sea boolean
      }),
      catchError(() => {
        return of(false); // Retorna false si hay error
      })
    );
  }




}
