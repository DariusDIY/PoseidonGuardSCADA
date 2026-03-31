import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ApiConfigService {

  public API_URL: string = "Aqui_Url_api";
  //public API_URL: string = "/api/";

  getApiUrl(){
    return this.API_URL;
  }




  public API_KEY_NAME: string = "POSEIDON-API-KEY";

  getApiKeyName(){
    return this.API_KEY_NAME;
  }




  public API_KEY: string = "Aqui_Api_key";

  getApiKey(){
    return this.API_KEY;
  }





  public API_VERSION: string = "v1";

  getApiKeyVersion(){
    return this.API_VERSION;
  }

}
