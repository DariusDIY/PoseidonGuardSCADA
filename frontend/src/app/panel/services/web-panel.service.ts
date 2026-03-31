import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Acuario, Pez } from 'src/app/interfaces/web.interface';
import { CookieService } from 'ngx-cookie-service';
import { Router } from '@angular/router';
import { addDays, addMonths, format, parseISO, subDays, subMonths } from 'date-fns';
import { ApiConfigService } from 'src/app/shared/api-config.service';

@Injectable({
  providedIn: 'root'
})
export class WebPanelService {

  private urlApi = "";
  private apiKeyName = "";
  private apiKey = "";
  private apikeyVersion = "";

  constructor( private http:HttpClient,
               private cookieService:CookieService,
               private router:Router,
               private apiConfig:ApiConfigService
   ) {
    this.urlApi = apiConfig.getApiUrl();
    this.apiKeyName = apiConfig.getApiKeyName();
    this.apiKey = apiConfig.getApiKey();
    this.apikeyVersion = apiConfig.getApiKeyVersion();
   }


  getKeyPass():string{
    let TOKEN = this.cookieService.check('PGTOKEN');
    if(TOKEN){
      return this.cookieService.get('PGTOKEN');
    }
    this.router.navigate(['/']);
    return '000';

  }

  getAutenticacionToken(keypass:string):Observable<boolean>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.get<boolean>(`${this.urlApi}${this.apikeyVersion}/WebSite/LoginAuthGuard/${keypass}`, { headers });
  }




  getInfoAcuarios(keypass:string):Observable<Acuario[]>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.get<Acuario[]>(`${this.urlApi}${this.apikeyVersion}/WebSite/PanelControl/${keypass}`, { headers });
  }


  getInfoAcuarioSelect(keypass:string, idacuario:number):Observable<Acuario[]>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.get<Acuario[]>(`${this.urlApi}${this.apikeyVersion}/WebSite/Configuraciones/${keypass}/${idacuario}`, { headers });
  }


  postConfiguracionAcuarioSelect(dataAcuario:any):Observable<boolean>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.post<boolean>(`${this.urlApi}${this.apikeyVersion}/WebSite/Configuraciones/GuardarCambios`, dataAcuario, { headers });
  }

  postAgregarPezAcuarioSelect(dataAcuario:any):Observable<boolean>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.post<boolean>(`${this.urlApi}${this.apikeyVersion}/WebSite/Configuraciones/AgregarPez`, dataAcuario, { headers });
  }

  postQuitarPezAcuarioSelect(dataAcuario:any):Observable<boolean>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.post<boolean>(`${this.urlApi}${this.apikeyVersion}/WebSite/Configuraciones/QuitarPez`, dataAcuario, { headers });
  }





  getListaPeces():Observable<Pez[]>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.get<Pez[]>(`${this.urlApi}${this.apikeyVersion}/WebSite/Pez/ListaPeces`, { headers });
  }

  postNuevoPez(dataPez:any):Observable<Pez[]>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.post<Pez[]>(`${this.urlApi}${this.apikeyVersion}/WebSite/Pez/AgregarPez`, dataPez, { headers });
  }



  getHistorialAcuarioSelect(dataAcuario:any):Observable<any>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.post<any>(`${this.urlApi}${this.apikeyVersion}/WebSite/Historial`, dataAcuario, { headers });
  }







  RecargarAlimentadorAl1000(keypass:string,idacuario:number):Observable<boolean>{
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.get<boolean>(`${this.urlApi}${this.apikeyVersion}/WebSite/RecargarAlimentadorAl100/${keypass}/${idacuario}`, { headers });
  }














  sumarDias(fechaString:string, numeroDias:number):string{
    const fechaMasDias = addDays(parseISO(fechaString), numeroDias);
    const fechaResultado = format(fechaMasDias, 'yyyy-MM-dd');
    return fechaResultado;
  }

  restarDias(fechaString:string, numeroDias:number):string{
    const fechaMasDias = subDays(parseISO(fechaString), numeroDias);
    const fechaResultado = format(fechaMasDias, 'yyyy-MM-dd');
    return fechaResultado;
  }

  sumarMeses(fechaString:string, numeroMeses:number):string{
    const fechaMasDias = addMonths(parseISO(fechaString), numeroMeses);
    const fechaResultado = format(fechaMasDias, 'yyyy-MM-dd');
    return fechaResultado;
  }

  restarMeses(fechaString:string, numeroMeses:number):string{
    const fechaMasDias = subMonths(parseISO(fechaString), numeroMeses);
    const fechaResultado = format(fechaMasDias, 'yyyy-MM-dd');
    return fechaResultado;
  }


}
