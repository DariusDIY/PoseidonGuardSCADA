export interface Acuario {
  pecesLista:   Pez[]|null;
  acuarioInfo:  AcuarioInfo;
  alimentacion: Alimentacion;
  temperatura:  Temperatura;
  iluminacion:  Iluminacion;
  ph:           Ph;
}

export interface AcuarioInfo {
  idacuario:              number;
  keyAcuario:             string;
  peces:                  string;
  estado:                 boolean;
  rfidConfig:             number;
  modo:                   number;
  conexion:               string;
}

export interface Alimentacion {
  horarios:  HorariosAlimentacion;
  dias:      DiasAlimentacion;
  contenido: ContenidoAlimentador;
}

export interface HorariosAlimentacion {
  horario1:  string;
  cantidad1: number;
  estado1:   number;
  horario2:  string;
  cantidad2: number;
  estado2:   number;
  horario3:  string;
  cantidad3: number;
  estado3:   number;
}

export interface DiasAlimentacion {
  lunes:     DiaAlimentacion[] | null;
  martes:    DiaAlimentacion[] | null;
  miercoles: DiaAlimentacion[] | null;
  jueves:    DiaAlimentacion[] | null;
  viernes:   DiaAlimentacion[] | null;
  sabado:    DiaAlimentacion[] | null;
  domingo:   DiaAlimentacion[] | null;
}

export interface ContenidoAlimentador {
  total:            number;
  actual:           number;
  actualPorcentual: number;
}


export interface DiaAlimentacion {
  idalimentacion:   number;
  horario:          number;
  cantidad:         number;
  registro:         Date;
}



export interface Iluminacion {
  on:     string;
  off:    string;
  estado: boolean;
  sensor: boolean;
}

export interface Ph {
  phMin:    number;
  phMax:    number;
  phActual: number;
}

export interface Temperatura {
  tempMin:    number;
  tempMax:    number;
  tempActual: TempActual;
}

export interface TempActual {
  temperatura1: number;
  temperatura2: number;
  calentador1:  number;
  calentador2:  number;
}









export interface Pez {
  idpez:            number;
  nombreCientifico: string;
  nombreComun:      string;
  temperamento:     string;
  tempMin:          number;
  tempMax:          number;
  nivelPhMin:       number;
  nivelPhMax:       number;
  dieta:            string;
  longitud:         string;
}







export interface Acuarista {
  status:         boolean;
  nombreCompleto: string;
  key:            string;
  caducidad:      Date;
}











export interface HistorialRespuesta {
  estado:    boolean;
  historial: HistorialAlimentacion[] | HistorialTemperatura[] | HistorialIluminacion[] | HistorialPh[];
}

export interface HistorialAlimentacion {
  idalimentacion: number;
  idacuario:      number;
  horario:        string|null;
  cantidad:       number|null;
  registro:       Date;
}


export interface HistorialTemperatura {
  idtemperatura: number;
  idacuario:     number;
  temperatura1:  number;
  temperatura2:  number;
  calentador1:   number;
  calentador2:   number;
  registro:      Date;
}


export interface HistorialIluminacion {
  idiluminacion: number;
  idacuario:     number;
  estado:        boolean|null;
  sensor:        boolean|null;
  registro:      Date;
}

export interface HistorialPh {
  idnivelpH: number;
  idacuario: number;
  nivel:     number;
  registro:  Date;
}



