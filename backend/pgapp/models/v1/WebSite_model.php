<?php

class WebSite_model extends CI_Model {


  private function fechayHoraActual(){
    $currentDateTimeBolivia = new DateTime('now', new DateTimeZone('America/La_Paz'));
    $currentDateTimeBoliviaFormato = $currentDateTimeBolivia->format('Y-m-d H:i:s');
    return $currentDateTimeBoliviaFormato;
  }

  private function SubstraccionString($texto, $desde, $hasta){
	if($texto != null){
		return substr($texto, $desde, $hasta);
	}else{
		return null;
	}
  }

  private function getFechasSemana(){
    $actual = $this->fechayHoraActual(); // Obtener fecha y hora actual de Bolivia
    $hoy = new DateTime($actual, new DateTimeZone('America/La_Paz')); // Crear objeto DateTime a partir de la fecha actual
    
    $lunes = clone $hoy; // Encontrar el lunes de esta semana
    $lunes->modify('monday this week');
        
    $semana = []; // Inicializar array para los días de la semana
        
    for ($i = 0; $i < 7; $i++) { // Agregar los 7 días de la semana (lunes a domingo)
        $dia = clone $lunes;
        $dia->modify("+$i days");
        $semana[] = $dia->format('Y-m-d');
    }
    
    return $semana;
  }


  public function traerInfoAcuarios($clave, $idacuario){
	//COMPROBAR CLAVE Y CADUCIDAD DE CODIGO
	$idacuarista = $this->comprobarClave($clave); //retorna el idacuarista

	//TRAER INFORMACION DE LOS ACUARIOS PERTENECIENTES
	if($idacuario>0){
		$pecesListaCompleta = $this->traerListaCompletaPeces();
		$pertenenciaAcuario = $this->comprobarPertenenciaAcuario($idacuarista, $idacuario);
	}else{
		$pecesListaCompleta = null;
		$pertenenciaAcuario = true;
	}

	if( ($idacuarista > 0) && ($pertenenciaAcuario) ){
		$fechasSemana = $this->getFechasSemana();
		$respuesta = array();
		$acuarios = $this->getAcuarios($idacuarista, $idacuario);
		if($acuarios){
			foreach ($acuarios as $acuario) {
				$tempIluminacion = $this->getIluminacionActual($acuario->idacuario);
				$temp = array(
					"pecesLista" => $pecesListaCompleta,
					"acuarioInfo"	=> array(
						"idacuario"					=> intval($acuario->idacuario),
						"keyAcuario"				=> $acuario->apiKeyAcuario,
						"peces"						=> $this->traerListaPecesAcuario($acuario->idacuario),						
						"estado"					=> boolval($acuario->estado),
						"modo"						=> intval($acuario->modo),
						"conexion"					=> $acuario->reporte
					),
					"alimentacion"	=> array(
						"horarios" => array(
							"horario1"	=> $this->SubstraccionString($acuario->horario1, 0, 5),
							"cantidad1"	=> intval($acuario->cantidad1),
							"estado1"	=> $this->verificarAlimentacionHoy($acuario->idacuario ,1),
							"horario2"	=> $this->SubstraccionString($acuario->horario2, 0, 5),
							"cantidad2"	=> intval($acuario->cantidad2),
							"estado2"	=> $this->verificarAlimentacionHoy($acuario->idacuario ,2),
							"horario3"	=> $this->SubstraccionString($acuario->horario3, 0, 5),
							"cantidad3"	=> intval($acuario->cantidad3),
							"estado3"	=> $this->verificarAlimentacionHoy($acuario->idacuario ,3)
						),
						"dias"	=> array(
							"lunes" 	=> $this->getAlimentacionDia($acuario->idacuario, $fechasSemana[0]),
							"martes" 	=> $this->getAlimentacionDia($acuario->idacuario, $fechasSemana[1]),
							"miercoles" => $this->getAlimentacionDia($acuario->idacuario, $fechasSemana[2]),
							"jueves" 	=> $this->getAlimentacionDia($acuario->idacuario, $fechasSemana[3]),
							"viernes" 	=> $this->getAlimentacionDia($acuario->idacuario, $fechasSemana[4]),
							"sabado" 	=> $this->getAlimentacionDia($acuario->idacuario, $fechasSemana[5]),
							"domingo" 	=> $this->getAlimentacionDia($acuario->idacuario, $fechasSemana[6])
						),
						"contenido" => array(
							"total"				=> intval($acuario->alimentadorCapacidad),
							"actual"			=> intval($acuario->alimentadorActual),
							"actualPorcentual"  => $this->calcularPorcentajeAlimentador($acuario->alimentadorCapacidad, $acuario->alimentadorActual)
						)
					),
					"temperatura" => array(
						"tempMin"		=> intval($acuario->temperaturaMin),
						"tempMax"		=> intval($acuario->temperaturaMax),
						"tempActual"	=> $this->getTemperaturaActual($acuario->idacuario)
					),
					"iluminacion" => array(
						"on"	=> $this->SubstraccionString($acuario->iluminacionOnTime, 0, 5), 
						"off"	=> $this->SubstraccionString($acuario->iluminacionOffTime, 0, 5 ), 
						"estado"=> $tempIluminacion['estado'],
						"sensor"=> $tempIluminacion['sensor']
					),
					"ph" => array(
						"phMin"		=> floatval($acuario->phMin),
						"phMax"		=> floatval($acuario->phMax),
						"phActual"	=> $this->getPhActual($acuario->idacuario)
					)
				);
				array_push($respuesta, $temp);
			}
		}
		return $respuesta;
	}else{
		return false;
	}
  }


  private function comprobarClave($clave){
	$fechaActual = $this->fechayHoraActual();
	$this->db->select('idacuarista');
	$this->db->from('acuarista');
	$this->db->where('keypass', $clave);
	$this->db->where('keypassCaducidad>', $fechaActual);
	$query = $this->db->get();
	$caducidad = $query->row();
	if($caducidad){
		return intval($caducidad->idacuarista);
	}else{
		return 0;
	}
  }

  private function comprobarPertenenciaAcuario($idacuarista, $idacuario){
	$this->db->select('*');
	$this->db->from('acuarista_acuario');
	$this->db->where('idacuarista', $idacuarista);
	$this->db->where('idacuario', $idacuario);
	$query = $this->db->get();
	$acuario = $query->row();
	if($acuario){
		return true;
	}else{
		return false;
	}
  }

  private function getAcuarios($idacuarista, $idacuario){
	$this->db->select('*');
	$this->db->from('acuarista_acuario');
	if( $idacuario !=0 ){$this->db->where('acuarista_acuario.idacuario', $idacuario);}
	$this->db->where('idacuarista', $idacuarista);
	$this->db->join('acuario', 'acuario.idacuario = acuarista_acuario.idacuario');
	$query = $this->db->get();
	$acuarios = $query->result();
	if($acuarios){
		return $acuarios;
	}else{
		return null;
	}
  }

  




private function calcularPorcentajeAlimentador($total, $actual){
	if($total == 0){
		$total = 1;
	}
	$calculo = ($actual*100) / $total;
	return intval($calculo);
}



private function traerListaPecesAcuario($idacuario){
    $this->db->select('nombreComun');
    $this->db->from('acuario_pez');
    $this->db->join('pez','pez.idpez = acuario_pez.idpez');
    $this->db->where('acuario_pez.idacuario', $idacuario);
    $query = $this->db->get();
    $peces = $query->result();

    $salida = "";
    $conteo = 0;
    foreach ($peces as $pez) {
      if($conteo==0){
        $salida = $pez->nombreComun;
      }else{
        $salida = $salida." - ".$pez->nombreComun;
      }
      $conteo++;
    }
    return $salida;
}


public function traerListaCompletaPeces(){
	$this->db->select('*');
    $this->db->from('pez');
    $query = $this->db->get();
    $peces = $query->result();
	return $peces;
}



private function getTemperaturaActual($idacuario){
	$respuesta = array(
		"temperatura1"	=> -127,
        "temperatura2"	=> -127,
        "calentador1"	=> -127,
        "calentador2"	=> -127
	);
	$this->db->select('temperatura1,temperatura2,calentador1,calentador2');
	$this->db->from('temperatura');
	$this->db->where('idacuario', $idacuario);
	$this->db->order_by('idtemperatura', 'DESC');
	$query = $this->db->get();
	$temperatura = $query->row();
	if($temperatura){
		$respuesta = array(
			"temperatura1"	=> intval($temperatura->temperatura1),
			"temperatura2"	=> intval($temperatura->temperatura2),
			"calentador1"	=> intval($temperatura->calentador1),
			"calentador2"	=> intval($temperatura->calentador2)
		);
	}
	return $respuesta;	
}

private function getPhActual($idacuario){
	$this->db->select('nivel');
	$this->db->from('nivelpH');
	$this->db->where('idacuario', $idacuario);
	$this->db->order_by('idnivelpH', 'DESC');
	$query = $this->db->get();
	$ph = $query->row();
	if($ph){
		return floatval($ph->nivel);
	}else{
		return -127.0;
	}
}

private function getIluminacionActual($idacuario){	
	$this->db->select('*');
	$this->db->from('iluminacion');
	$this->db->where('idacuario', $idacuario);
	$this->db->order_by('idiluminacion', 'DESC');
	$query = $this->db->get();
	$iluminacion = $query->row();
	if($iluminacion){
		return array(
			"estado" => boolval($iluminacion->estado),
			"sensor" => boolval($iluminacion->sensor)
		);
	}else{
		return array(
			"estado" => false,
			"sensor" => true
		);
	}
}


private function verificarAlimentacionHoy($idacuario, $horario){
	$fechaActual = $this->fechayHoraActual();
	$fechaBusquedaInicio = $this->SubstraccionString($fechaActual, 0, 10)." 00:00:00";
	$fechaBusquedaFin = $this->SubstraccionString($fechaActual, 0, 10)." 23:59:59";
	
	$this->db->select('*');
	$this->db->from('alimentacion');
	$this->db->where('idacuario', $idacuario);
	$this->db->where('horario', $horario);
	$this->db->where('registro>=', $fechaBusquedaInicio);
	$this->db->where('registro<=', $fechaBusquedaFin);
	$query = $this->db->get();
	$alimentacionHoy = $query->result();
	return count($alimentacionHoy);
	if($alimentacionHoy){
		switch($horario){
			case 1:
				if( $alimentacionHoy->horario != null ){return true;}else{return false;}
				break;
			case 2:
				if( $alimentacionHoy->horario != null ){return true;}else{return false;}
				break;
			case 3:
				if( $alimentacionHoy->horario != null ){return true;}else{return false;}
				break;
		}
	}else{
		return false;
	}
}


private function getAlimentacionDia($idacuario, $fechaBusqueda){
	$fechaBusquedaInicio = $fechaBusqueda." 00:00:00";
	$fechaBusquedaFin = $fechaBusqueda." 23:59:59";

	$this->db->select('*');
	$this->db->from('alimentacion');
	$this->db->where('idacuario', $idacuario);
	$this->db->where('registro>=', $fechaBusquedaInicio);
	$this->db->where('registro<=', $fechaBusquedaFin);
	$this->db->order_by('registro', 'ASC');
	$query = $this->db->get();
	$alimentacionDia = $query->result();	
	$respuesta = array();
	if($alimentacionDia){
		foreach ($alimentacionDia as $registroAlimentacion) {
			$temp = array(
				"idalimentacion"	=> intval($registroAlimentacion->idalimentacion),
				"horario"			=> intval($registroAlimentacion->horario),
				"cantidad"			=> intval($registroAlimentacion->cantidad),
				"registro"			=> $registroAlimentacion->registro
			);
			array_push($respuesta, $temp);
		}
	}else{
		$respuesta = null;
	}
	return $respuesta;
}

























public function RealizarLogin($datosUsuarioLogin){
	$infoUsuario = $this->verificarExistenciaUsuario($datosUsuarioLogin); //verificamos datos y sacamos datos para armar el keypass
	if($infoUsuario){
		return $infoUsuario;
	}else{
		return false;
	}
}

private function verificarExistenciaUsuario($datosUsuarioLogin){
	$fechaActual = $this->fechayHoraActual();
	$this->db->select('idacuarista, nombre, apellido, registro');
	$this->db->from('acuarista');
	$this->db->where('usuario', $datosUsuarioLogin->username);
	$this->db->where('password', md5($datosUsuarioLogin->password));
	$query = $this->db->get();
	$usuario = $query->row();
	if($usuario){
		$keypass = md5($usuario->idacuarista."-".$usuario->nombre."-".$usuario->apellido."-".$usuario->registro."-".$fechaActual);

		$fecha = new DateTime($fechaActual);
		$fecha->modify('+1 day');
		$caducidad = $fecha->format('Y-m-d H:i:s');
		$this->guardarKeyPass($usuario->idacuarista, $keypass, $caducidad);
		$respuesta = array(
			"status"			=> true,
			"nombreCompleto"	=> $usuario->nombre." ".$usuario->apellido,
			"key"				=> $keypass,
			"caducidad"			=> $caducidad
		);
		return $respuesta;
	}else{
		$respuesta = array(
			"status"			=> false,
			"nombreCompleto"	=> null,
			"key"				=> null,
			"caducidad"			=> null
		);
	}
}

private function guardarKeyPass($idacuarista, $keypass, $caducidad){
	$this->db->set('keypass', $keypass);
	$this->db->set('keypassCaducidad', $caducidad);
	$this->db->where('idacuarista', $idacuarista);
	$this->db->update('acuarista');	
}



public function RealizarAutenticacion($clave){
	$autenticacion = $this->comprobarClave($clave);
	if($autenticacion>0){
		return true;
	}else{
		return false;
	}
}





































public function GuardarConfiguraciones($datosConfiguraciones){
	$idacuarista = $this->comprobarClave($datosConfiguraciones->keypass);
	$pertenenciaAcuario = $this->comprobarPertenenciaAcuario($idacuarista, $datosConfiguraciones->idacuario);

	if( ($idacuarista>0) && ($pertenenciaAcuario) ){
		$this->db->set('horario1', $datosConfiguraciones->alimentacionHorario1);
		$this->db->set('cantidad1', $datosConfiguraciones->alimentacionCantidad1);
		$this->db->set('horario2', $datosConfiguraciones->alimentacionHorario2);
		$this->db->set('cantidad2', $datosConfiguraciones->alimentacionCantidad2);
		$this->db->set('horario3', $datosConfiguraciones->alimentacionHorario3);
		$this->db->set('cantidad3', $datosConfiguraciones->alimentacionCantidad3);
		$this->db->set('temperaturaMin', $datosConfiguraciones->tempMin);
		$this->db->set('temperaturaMax', $datosConfiguraciones->tempMax);
		$this->db->set('phMin', $datosConfiguraciones->phMin);
		$this->db->set('phMax', $datosConfiguraciones->phMax);
		$this->db->set('iluminacionOnTime', $datosConfiguraciones->IluminacionHorarioOn);
		$this->db->set('iluminacionOffTime', $datosConfiguraciones->IluminacionHorarioOff);
		$this->db->set('modo', 1);
		
		$this->db->where('idacuario', $datosConfiguraciones->idacuario);
		$this->db->update('acuario');	
		return true;
	}else{
		return false;
	}
}




public function agregarPezConfiguraciones($datosPez){
	$idacuarista = $this->comprobarClave($datosPez->keypass);
	$pertenenciaAcuario = $this->comprobarPertenenciaAcuario($idacuarista, $datosPez->idacuario);
	$pezNoExisteEnAcuario = $this->comprobarPezEnAcuario($datosPez->idacuario, $datosPez->idpez);

	if( ($idacuarista>0) && ($pertenenciaAcuario) && ($pezNoExisteEnAcuario) ){
		$data = array(
			'idacuario' => $datosPez->idacuario,
			'idpez' 	=> $datosPez->idpez
		);

		$this->db->insert('acuario_pez', $data);
		return true;		
	}else{
		return false;
	}
}


public function quitarPezConfiguraciones($datosPez){
	$idacuarista = $this->comprobarClave($datosPez->keypass);
	$pertenenciaAcuario = $this->comprobarPertenenciaAcuario($idacuarista, $datosPez->idacuario);
	$pezNoExisteEnAcuario = $this->comprobarPezEnAcuario($datosPez->idacuario, $datosPez->idpez);

	if( ($idacuarista>0) && ($pertenenciaAcuario) && (!$pezNoExisteEnAcuario) ){
		$this->db->where('idacuario', $datosPez->idacuario);
		$this->db->where('idpez', $datosPez->idpez);
		$this->db->delete('acuario_pez');
		return true;		
	}else{
		return false;
	}
}

private function comprobarPezEnAcuario($idacuario, $idpez){
	$this->db->select('*');
	$this->db->from('acuario_pez');
	$this->db->where('idacuario', $idacuario);
	$this->db->where('idpez', $idpez);
	$query = $this->db->get();
	$pez = $query->row();
	if($pez){
		return false;
	}else{
		return true;
	}
}










public function consultarHistorialAcuario($datosBusquedaHistorial){
	$idacuarista = $this->comprobarClave($datosBusquedaHistorial->keypass);
	$pertenenciaAcuario = $this->comprobarPertenenciaAcuario($idacuarista, $datosBusquedaHistorial->idacuario);

	$idacurio = $datosBusquedaHistorial->idacuario;
	$variable = $datosBusquedaHistorial->variable;
	$fechaHoraInicio = $datosBusquedaHistorial->fechaHoraInicio;
	$fechaHoraFin = $datosBusquedaHistorial->fechaHoraFin;

	if( ($idacuarista>0) && ($pertenenciaAcuario) ){
		switch($variable){
			case 'alimentacion':
				$respuesta = $this->traerHistorialAlimentacion($idacurio, $fechaHoraInicio, $fechaHoraFin);
				break;
			case 'temperatura':
				$respuesta = $this->traerHistorialTemperatura($idacurio, $fechaHoraInicio, $fechaHoraFin);
				break;
			case 'iluminacion':
				$respuesta = $this->traerHistorialIluminacion($idacurio, $fechaHoraInicio, $fechaHoraFin);
				break;
			case 'ph':
				$respuesta = $this->traerHistorialPh($idacurio, $fechaHoraInicio, $fechaHoraFin);
				break;
		}
		return $respuesta;
	}else{
		$respuesta = array(
			"estado"	=> false,
			"historial"	=> null
		);
	}
}

private function traerHistorialAlimentacion($idacuario ,$fechaInicio, $fechaFin){
	$this->db->select('*');
	$this->db->from('alimentacion');
	$this->db->where('idacuario', $idacuario);
	$this->db->where('registro>=', $fechaInicio);
	$this->db->where('registro<=', $fechaFin);
	$this->db->order_by('registro', 'ASC');
	$this->db->order_by('horario', 'ASC');
	$query = $this->db->get();
	$historial = $query->result();
	if($historial){
		$arregloHistorial = array();
		foreach ($historial as $h) {
			$temp = array(
				"idalimentacion"	=> intval($h->idalimentacion),
				"idacuario"			=> intval($h->idacuario),
				"horario"			=> intval($h->horario),
				"cantidad"			=> intval($h->cantidad),
				"registro"			=> $h->registro
			);
			array_push($arregloHistorial, $temp);
		}	
		$respuesta = array(
			"estado"	=> true,
			"historial"	=> $arregloHistorial
		);
	}else{
		$respuesta = array(
			"estado"	=> false,
			"historial"	=> null
		);
	}
	return $respuesta;
}


private function traerHistorialTemperatura($idacurio, $fechaInicio, $fechaFin){
	$this->db->select('*');
	$this->db->from('temperatura');
	$this->db->where('idacuario', $idacurio);
	$this->db->where('registro>=', $fechaInicio);
	$this->db->where('registro<=', $fechaFin);
	$this->db->order_by('registro', 'ASC');
	$query = $this->db->get();
	$historial = $query->result();
	if($historial){	
		$arregloHistorial = array();
		foreach ($historial as $h) {
			$temp = array(
				"idtemperatura"		=> intval($h->idtemperatura),
				"idacuario"			=> intval($h->idacuario),
				"temperatura1"		=> intval($h->temperatura1),
				"temperatura2"		=> intval($h->temperatura2),
				"calentador1"		=> intval($h->calentador1),
				"calentador2"		=> intval($h->calentador2),
				"registro"			=> $this->SubstraccionString($h->registro, 0, 19)
			);
			array_push($arregloHistorial, $temp);
		}	
		$respuesta = array(
			"estado"	=> true,
			"historial"	=> $arregloHistorial
		);
	}else{
		$respuesta = array(
			"estado"	=> false,
			"historial"	=> null
		);
	}
	return $respuesta;
}


private function traerHistorialIluminacion($idacurio, $fechaInicio, $fechaFin){
	$this->db->select('*');
	$this->db->from('iluminacion');
	$this->db->where('idacuario', $idacurio);
	$this->db->where('registro>=', $fechaInicio);
	$this->db->where('registro<=', $fechaFin);
	$this->db->order_by('registro', 'ASC');
	$query = $this->db->get();
	$historial = $query->result();

	if($historial){	
		$arregloHistorial = array();
		foreach ($historial as $h) {
			$temp = array(
				"idiluminacion"	=> intval($h->idiluminacion),
				"idacuario"		=> intval($h->idacuario),
				"estado"		=> boolval($h->estado),
				"sensor"		=> boolval($h->sensor),
				"registro"		=> $h->registro,
			);
			array_push($arregloHistorial, $temp);
		}	
		$respuesta = array(
			"estado"	=> true,
			"historial"	=> $arregloHistorial
		);
	}else{
		$respuesta = array(
			"estado"	=> false,
			"historial"	=> null
		);
	}

	return $respuesta;
}


private function traerHistorialPh($idacurio, $fechaInicio, $fechaFin){
	$this->db->select('*');
	$this->db->from('nivelpH');
	$this->db->where('idacuario', $idacurio);
	$this->db->where('registro>=', $fechaInicio);
	$this->db->where('registro<=', $fechaFin);
	$this->db->order_by('registro', 'ASC');
	$query = $this->db->get();
	$historial = $query->result();

	if($historial){	
		$arregloHistorial = array();
		foreach ($historial as $h) {
			$temp = array(
				"idnivelpH"	=> intval($h->idnivelpH),
				"idacuario"	=> intval($h->idacuario),
				"nivel"		=> floatval($h->nivel),
				"registro"	=> $h->registro
			);
			array_push($arregloHistorial, $temp);
		}	
		$respuesta = array(
			"estado"	=> true,
			"historial"	=> $arregloHistorial
		);
	}else{
		$respuesta = array(
			"estado"	=> false,
			"historial"	=> null
		);
	}
	return $respuesta;
}


















	

































public function RecargarAlimentadorAl100($clave, $idacuario){
	
	//COMPROBAR CLAVE Y CADUCIDAD DE CODIGO
	$idacuarista = $this->comprobarClave($clave); //retorna el idacuarista

	//COMPROBAR PERTENENCIA
	$infoAcuario = $this->traerInfoAcuarios($clave, $idacuario);


	if( ($idacuarista>0) && ($infoAcuario) ){
		$this->db->set('alimentadorActual', $infoAcuario[0]["alimentacion"]["contenido"]["total"]);
		$this->db->set('modo', 1);
		
		$this->db->where('idacuario', $idacuario);
		$this->db->update('acuario');
		return true;
	}else{
		return false;
	}


}













public function traerErroresPanel($clave){
	//COMPROBAR CLAVE Y CADUCIDAD DE CODIGO
	$idacuarista = $this->comprobarClave($clave); //retorna el idacuarista

	//COMPROBAR PERTENENCIA
	$infoAcuario = $this->traerInfoAcuarios($clave, 0);


	return $infoAcuario;
}


















public function AgregarAcuarioNuevo($datosAcuarioNuevo){	
	$idacuarista = $this->comprobarClave($datosAcuarioNuevo->keypass); //retorna el idacuarista

	if($idacuarista>0){
		$datos = array(
			"apiKeyAcuario"			=> "NEW",
			"horario1"				=> $datosAcuarioNuevo->alimentacionHorario1,
			"cantidad1"				=> $datosAcuarioNuevo->alimentacionCantidad1,
			"horario2"				=> $datosAcuarioNuevo->alimentacionHorario2,
			"cantidad2"				=> $datosAcuarioNuevo->alimentacionCantidad2,
			"horario3"				=> $datosAcuarioNuevo->alimentacionHorario3,
			"cantidad3"				=> $datosAcuarioNuevo->alimentacionCantidad3,
			"alimentadorCapacidad"	=> 1000,
			"alimentadorActual"		=> 1000,
			"temperaturaMin"		=> $datosAcuarioNuevo->tempMin,
			"temperaturaMax"		=> $datosAcuarioNuevo->tempMax,
			"iluminacionOnTime"		=> $datosAcuarioNuevo->IluminacionHorarioOn,
			"iluminacionOffTime"	=> $datosAcuarioNuevo->IluminacionHorarioOff,
			"phMin"					=> $datosAcuarioNuevo->phMin,
			"phMax"					=> $datosAcuarioNuevo->phMax,
			"estado"				=> 1,
			"modo"					=> 0,
			"registro"				=> $this->fechayHoraActual(),
			"reporte"				=> $this->fechayHoraActual()
		);		
		$this->db->insert('acuario', $datos);
		$idInsertado = $this->db->insert_id();
		$actualizarApiKey = $this->actualizarapiKeyAcuario($idInsertado);
	}
	return true;
}

private function actualizarapiKeyAcuario($idacuario){
	$numero = "";
	if($idacuario<10){
		$numero = "0".$idacuario;
	}else{
		$numero = $idacuario;
	}
	$apiKeyAcuario = "PG-".$numero;
	$this->db->set('apiKeyAcuario', $apiKeyAcuario);		
	$this->db->where('idacuario', $idacuario);
	$this->db->update('acuario');
	return true;
}








}

