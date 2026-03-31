import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { CookieService } from 'ngx-cookie-service';
import { Observable } from 'rxjs';
import { Acuarista } from 'src/app/interfaces/web.interface';
import { ApiConfigService } from 'src/app/shared/api-config.service';

@Injectable({
  providedIn: 'root'
})
export class HomeService {

  private urlApi = "";
  private apiKeyName = "";
  private apiKey = "";
  private apikeyVersion = "";

  constructor( private http:HttpClient,
               private cookieService:CookieService,
               private apiConfig:ApiConfigService  ) {
    this.urlApi = apiConfig.getApiUrl();
    this.apiKeyName = apiConfig.getApiKeyName();
    this.apiKey = apiConfig.getApiKey();
    this.apikeyVersion = apiConfig.getApiKeyVersion();
  }



  Login(username:string, password:string):Observable<Acuarista>{
    const DataLogin = {
      "username":username,
      "password":password
    }
    const headers = new HttpHeaders().set(this.apiKeyName, this.apiKey);
    return this.http.post<Acuarista>(`${this.urlApi}${this.apikeyVersion}/WebSite/Login`, DataLogin ,{ headers });
  }


  public crearCookieToken(token:string):void{
    const currentDate = new Date();
    const expirationDate = new Date(currentDate.getTime() + 120 * 60 * 1000); // 14 minutos * 60 segundos * 1000 milisegundos = 15 minutos
    this.cookieService.set('PGTOKEN', token, { expires: expirationDate, path: '/' });
    console.log("Cookie creada");
  }
}
