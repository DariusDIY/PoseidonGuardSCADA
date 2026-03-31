<?php

class TankMaster_model extends CI_Model {


  	public function __construct(){
		parent::__construct();
   		$this->load->model('v1/Error_model');
  	}


  private function fechayHoraActual(){
    $currentDateTimeBolivia = new DateTime('now', new DateTimeZone('America/La_Paz'));
    $currentDateTimeBoliviaFormato = $currentDateTimeBolivia->format('Y-m-d H:i:s');
    return $currentDateTimeBoliviaFormato;
  }


	public function ModoActualizacionSet($datosDispositivo){
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($datosDispositivo->datosAPI);
		if($infoAcuario){
			$this->ReportarActulizacionCompletada($infoAcuario->idacuario, $datosDispositivo->modo);
			return true;
		}else{
			return false;
		}
	}

	private function ReportarActulizacionCompletada($idacuario, $modo){
		$this->db->set('modo', $modo);
		$this->db->where('idacuario', $idacuario);
		$this->db->update('acuario');
	}


	public function recopilarInformacionAcuario($apiKeyAcuario){
		$this->db->select('*');
		$this->db->from('acuario');
		$this->db->where('apiKeyAcuario', $apiKeyAcuario);
		$query = $this->db->get();
		$respuesta = $query->row();
		return $respuesta;
	}


	private function ObtenerInformacionUsuarioAcuario($datosAPI, $idacuario){
		$this->db->select('idacuarista');
		$this->db->from('acuarista');
		$this->db->where('usuario', $datosAPI->usuario);
		$this->db->where('password', md5($datosAPI->password));
		$query = $this->db->get();
		$acuarista = $query->row();
		if($acuarista){
			$pertenenciaAcuario = $this->ComprobarPerteneciaAcuario($acuarista->idacuarista,$idacuario);
			if($pertenenciaAcuario == 200){
				return 200;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}

	private function ComprobarPerteneciaAcuario($idusuario, $idacuario){
		$this->db->select('*');
		$this->db->from('acuarista_acuario');
		$this->db->where('idacuarista', $idusuario);
		$this->db->where('idacuario', $idacuario);
		$query = $this->db->get();
		$pertenencia = $query->row();
		if($pertenencia){
			return 200;
		}else{
			return 0;
		}
	}


	private function comprorUsuarioAcuarioInformacion($datosAPI){
		$infoAcuario = $this->recopilarInformacionAcuario($datosAPI->apiKeyAcuario);
		if(!$infoAcuario){return false;}
		$infoUsuarioAcuario = $this->ObtenerInformacionUsuarioAcuario($datosAPI, $infoAcuario->idacuario);		
		if( ($infoAcuario) &&  ($infoUsuarioAcuario == 200) ){
			return $infoAcuario;
		}else{
			return false;
		}
	}







	public function reportarAcuario($datosDispositivo){		
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($datosDispositivo->datosAPI);
		//return $infoAcuario;
		$this->analisisDeErrores($infoAcuario, $datosDispositivo);
		if( $infoAcuario ){
			$reporteAcuario = $this->ReportarConexion($infoAcuario->idacuario);
			$infoTemperatura = $this->ReporteTemperatura($datosDispositivo->temperatura, $infoAcuario->idacuario);			
			$infoIluminacion = $this->ReporteIluminacion($datosDispositivo->iluminacion, $infoAcuario);		
			$infoPh = $this->ObtenerUltimoPh($infoAcuario->idacuario);

			if($infoAcuario->modo == 1){
				return $respuesta = array(
					"modo"						=> boolval($infoAcuario->modo),
					"datos"						=> array(
						"apiKeyAcuario"						=> $infoAcuario->apiKeyAcuario,
						"horario1H"							=> intval(substr($infoAcuario->horario1,0,2)),
						"horario1M"							=> intval(substr($infoAcuario->horario1,3,2)),
						"cantidad1"							=> intval($infoAcuario->cantidad1),
						"horario2H"							=> intval(substr($infoAcuario->horario2,0,2)),
						"horario2M"							=> intval(substr($infoAcuario->horario2,3,2)),
						"cantidad2"							=> intval($infoAcuario->cantidad2),
						"horario3H"							=> intval(substr($infoAcuario->horario3,0,2)),
						"horario3M"							=> intval(substr($infoAcuario->horario3,3,2)),
						"cantidad3"							=> intval($infoAcuario->cantidad3),
						"alimentadorCapacidad"				=> intval($infoAcuario->alimentadorCapacidad),
						"alimentadorActual"					=> intval($infoAcuario->alimentadorActual),
						"temperaturaMin"					=> floatval($infoAcuario->temperaturaMin),
						"temperaturaMax"					=> floatval($infoAcuario->temperaturaMax),
						"iluminacionOnTimeH"				=> intval(substr($infoAcuario->iluminacionOnTime,0,2)),
						"iluminacionOnTimeM"				=> intval(substr($infoAcuario->iluminacionOnTime,3,2)),
						"iluminacionOffTimeH"				=> intval(substr($infoAcuario->iluminacionOffTime,0,2)),
						"iluminacionOffTimeM"				=> intval(substr($infoAcuario->iluminacionOffTime,3,2)),
						"phMin"								=> floatval($infoAcuario->phMin),
						"phMax"								=> floatval($infoAcuario->phMax),
						"phActual"						    => floatval($infoPh),
						"estado"							=> boolval($infoAcuario->estado)
					)				
				);
			}else{
				return $respuesta = array(
					"modo"						=> false,
					"datos"						=> null
				);
			}
		}else{
			return $respuesta = array(
				"modo"						=> false,
				"datos"						=> null
			);
		}
	}



	private function analisisDeErrores($infoAcuario, $datosDispositivo){
		//analisis de temperatura
		$idacuario = $infoAcuario->idacuario;
		$temperaturaPromedio = 0;
		$rangoTempInfCritico = $infoAcuario->temperaturaMin - 1;
		$rangoTempInfSuperCritico = $infoAcuario->temperaturaMin - 2;

		if( ($datosDispositivo->temperatura->termometro1 == -127) && ($datosDispositivo->temperatura->termometro2 == -127) ){
			$temperaturaPromedio = 0;
		}
		if( ($datosDispositivo->temperatura->termometro1 != -127) && ($datosDispositivo->temperatura->termometro2 == -127) ){
			$temperaturaPromedio = $datosDispositivo->temperatura->termometro1;
		}
		if( ($datosDispositivo->temperatura->termometro1 == -127) && ($datosDispositivo->temperatura->termometro2 != -127) ){
			$temperaturaPromedio = $datosDispositivo->temperatura->termometro2;
		}
		if( ($datosDispositivo->temperatura->termometro1 != -127) && ($datosDispositivo->temperatura->termometro2 != -127) ){
			$temperaturaPromedio = ($datosDispositivo->temperatura->termometro1 + $datosDispositivo->temperatura->termometro2) / 2;
		}




		if($temperaturaPromedio < $infoAcuario->temperaturaMin){			
			$this->Error_model->activaInactivaError($idacuario, 201, 1, $temperaturaPromedio, $infoAcuario->temperaturaMin, $infoAcuario->temperaturaMax);
			//return "Error de Tempertarura Baja / 201";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 201, 0, $temperaturaPromedio, $infoAcuario->temperaturaMin, $infoAcuario->temperaturaMax);
		}

		if($temperaturaPromedio > $infoAcuario->temperaturaMax){
			$this->Error_model->activaInactivaError($idacuario, 202, 1, $temperaturaPromedio, $infoAcuario->temperaturaMin, $infoAcuario->temperaturaMax);
			//return "Error de Tempertarura Alta / 202";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 202, 0, $temperaturaPromedio, $infoAcuario->temperaturaMin, $infoAcuario->temperaturaMax);
		}

		if($datosDispositivo->temperatura->termometro1 == -127){
			$this->Error_model->activaInactivaError($idacuario, 203, 1);
			//return "Error de termometro 1 / 203";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 203, 0);
		}

		if($datosDispositivo->temperatura->termometro2 == -127){
			$this->Error_model->activaInactivaError($idacuario, 204, 1);
			//return "Error de termometro 2 / 204";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 204, 0);
		}

		if( ($datosDispositivo->temperatura->calentador2 == 100) && ($temperaturaPromedio <= $rangoTempInfCritico) && ($temperaturaPromedio > $rangoTempInfSuperCritico) ){
			$this->Error_model->activaInactivaError($idacuario, 205, 1);
			//return "Error de calentador 1 / 205";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 205, 0);
		}

		if( ($datosDispositivo->temperatura->calentador2 == 100) && ($temperaturaPromedio <= $rangoTempInfSuperCritico) ){
			$this->Error_model->activaInactivaError($idacuario, 206, 1);
			//return "Error de calentador 2 / 206";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 206, 0);
		}




		//analisis de alimentador
		$alimentadorPorcentaje = ( $infoAcuario->alimentadorActual * 100) / $infoAcuario->alimentadorCapacidad;
		if( ($alimentadorPorcentaje<50) && ($alimentadorPorcentaje>=25) ){
			$this->Error_model->activaInactivaError($idacuario, 301, 1);
			//return "301 Advertencia de alimentador debajo del 50%";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 301, 0);
		}

		if( ($alimentadorPorcentaje<25) && ($alimentadorPorcentaje>=1) ){
			$this->Error_model->activaInactivaError($idacuario, 302, 1);
			//return "302 Advertencia de alimentador debajo del 25%";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 302, 0);
		}

		if( $alimentadorPorcentaje<=0 ){
			$this->Error_model->activaInactivaError($idacuario, 303, 1);
			//return "303 Advertencia de alimentador vacio";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 303, 0);
		}


		//analisis de iluminacion
		if( ($datosDispositivo->iluminacion->estado) && (!$datosDispositivo->iluminacion->sensor ) ){
			$this->Error_model->activaInactivaError($idacuario, 401, 1);
			//return "401 Error de Iluminacion de encendido";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 401, 0);
		}

		if( (!$datosDispositivo->iluminacion->estado) && ($datosDispositivo->iluminacion->sensor ) ){
			$this->Error_model->activaInactivaError($idacuario, 402, 1);
			//return "402 Error de Iluminacion de apagado";
		}else{
			$this->Error_model->activaInactivaError($idacuario, 402, 0);
		}
	}


	


	private function ReportarConexion($idacuario){
		$fechaHoraReporte = $this->fechayHoraActual();
		$this->db->set('reporte', $fechaHoraReporte);
		$this->db->where('idacuario', $idacuario);
		$this->db->update('acuario');
	}

	/********************************************************************************************************************************/
	/****************************************************ALIMENTACION****************************************************************/

	public function ReporteAlimentacion($datosDispositivo){
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($datosDispositivo->datosAPI);
		//return $infoAcuario;

		if ($infoAcuario){
			$alimentacion = $this->CrearRegistroAlimentacion($infoAcuario->idacuario, $datosDispositivo->alimentacion);
			$alimentador = $this->restarAlimentoEnAlimentador($infoAcuario->idacuario, $infoAcuario->alimentadorCapacidad, $infoAcuario->alimentadorActual ,$datosDispositivo->alimentacion->cantidad);
			return $alimentacion;
		}else{
			return false;
		}
	}

	private function CrearRegistroAlimentacion($idacuario,$datosDispositivo){
		$datos = array(
			"idacuario"	=> $idacuario,
			"horario"	=> $datosDispositivo->horario,
			"cantidad"	=> $datosDispositivo->cantidad,
			"registro"	=> $this->fechayHoraActual()
		);		
		$this->db->insert('alimentacion', $datos);
		return true;
	}

	private function restarAlimentoEnAlimentador($idacuario, $cantidadTotal, $cantidadActual ,$cantidadRestada){
		$cantidadNueva = intval($cantidadActual) - intval($cantidadRestada);
		$porcentajeAlimentador = ($cantidadNueva * 100)/intval($cantidadTotal);
		$this->db->set('alimentadorActual', $cantidadNueva);
		$this->db->where('idacuario', $idacuario);
		$this->db->update('acuario');
		return true;
	}

	/****************************************************ALIMENTACION****************************************************************/
	/********************************************************************************************************************************/
	



	/********************************************************************************************************************************/
	/****************************************************TEMPERATURA*****************************************************************/
	private function ReporteTemperatura($datosTemperatura, $idacuario){			
		$temperatura = $this->TraerUltimoReporteTemperatura($idacuario);
		
		if($temperatura){
			if( ($temperatura->temperatura1 != $datosTemperatura->termometro1) || ($temperatura->temperatura2 != $datosTemperatura->termometro2) || ($temperatura->calentador1 != $datosTemperatura->calentador1) || ($temperatura->calentador2 != $datosTemperatura->calentador2)  ){
				$this->crearRegistroTemperatura($datosTemperatura, $idacuario);
				return $temperatura;
			}
		}else{
			$this->crearRegistroTemperatura($datosTemperatura, $idacuario);			
		}

	}

	private function TraerUltimoReporteTemperatura($idacuario){
		$this->db->select('*');
		$this->db->from('temperatura');
		$this->db->where('idacuario', $idacuario);
		$this->db->order_by('idtemperatura', 'DESC');		
		$query = $this->db->get();
		$temperatura = $query->row();
		return $temperatura;
	}

	private function crearRegistroTemperatura($datosTemperatura, $idacuario){
		$datos = array(
			"idacuario"	=> $idacuario,
			"temperatura1" => $datosTemperatura->termometro1,
			"temperatura2" => $datosTemperatura->termometro2,
			"calentador1"	 => $datosTemperatura->calentador1,
			"calentador2"	 => $datosTemperatura->calentador2,
			"registro"	=> $this->fechayHoraActual()
		);		
		$this->db->insert('temperatura', $datos);
	}

	/****************************************************TEMPERATURA*****************************************************************/
	/********************************************************************************************************************************/





	/********************************************************************************************************************************/
	/****************************************************ILUMINACION*****************************************************************/
	private function ReporteIluminacion($datosIluminacion, $infoAcuario){
		$iluminacion = $this->TraerUltimoReporteIluminacion($infoAcuario->idacuario);

		if($iluminacion){
			if( ($iluminacion['estado'] != $datosIluminacion->estado) || ($iluminacion['sensor'] != $datosIluminacion->sensor) ){			
				$this->RegistrarIluminacion($infoAcuario->idacuario, $datosIluminacion->estado, $datosIluminacion->sensor);
				return "registrado";
			}
		}else{
			$this->RegistrarIluminacion($infoAcuario->idacuario, $datosIluminacion->estado, $datosIluminacion->sensor);
			return "registrado";
		}
	}

	private function TraerUltimoReporteIluminacion($idacuario){
		$this->db->select('*');
		$this->db->from('iluminacion');
		$this->db->where('idacuario', $idacuario);
		$this->db->order_by('idiluminacion', 'DESC');
		$query = $this->db->get();
		$iluminacion = $query->row();
		if($iluminacion){			
			return array(
				"idiluminacion"=> intval($iluminacion->idiluminacion),
				"idacuario"=> intval($iluminacion->idacuario),
				"estado"=> boolval($iluminacion->estado),
				"sensor"=> boolval($iluminacion->sensor),
				"registro"=> $iluminacion->registro
			);
		}else{
			return false;
		}
	}


	private function RegistrarIluminacion($idacuario, $estado, $sensor){
		
		$datos = array(
			"idacuario"	=> $idacuario,
			"estado"	=> $estado,
			"sensor"	=> $sensor,
			"registro"	=> $this->fechayHoraActual()
		);		
		$this->db->insert('iluminacion', $datos);		
	}

	/****************************************************ILUMINACION*****************************************************************/
	/********************************************************************************************************************************/







	/********************************************************************************************************************************/
	/****************************************************NIVEL DE PH*****************************************************************/
	private function ObtenerUltimoPh($idacuario){
		$this->db->select('*');
		$this->db->from('nivelpH');
		$this->db->where('idacuario', $idacuario);		
		$this->db->order_by('registro', 'DESC');		
		$query = $this->db->get();
		$nivelpH = $query->row();
		if($nivelpH){
			return $nivelpH->nivel;
		}else{
			return -1.0;
		}
	}


	public function reportepH($datosReporte){
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($datosReporte->datosAPI);
		$idacuario = $infoAcuario->idacuario;
		$this->analisisDeErroresPH($idacuario, $datosReporte);
		if( $infoAcuario ){
			$this->RegistrarPh($infoAcuario->idacuario, $datosReporte->ph);
			return true;
		}else{
			return $respuesta = array(
				"modo"						=> false,
				"datos"						=> null
			);
		}		
	}

	private function analisisDeErroresPH($idacuario, $datosReporte){		
		//analisis de ph		
		if($datosReporte->ph->phActual < $datosReporte->ph->phMin){
			$this->Error_model->activaInactivaError($idacuario, 501, 1, $datosReporte->ph->phActual, $datosReporte->ph->phMin, $datosReporte->ph->phMax);
		}else{
			$this->Error_model->activaInactivaError($idacuario, 501, 0, $datosReporte->ph->phActual, $datosReporte->ph->phMin, $datosReporte->ph->phMax);
		}

		if($datosReporte->ph->phActual > $datosReporte->ph->phMax){
			$this->Error_model->activaInactivaError($idacuario, 502, 1, $datosReporte->ph->phActual, $datosReporte->ph->phMin, $datosReporte->ph->phMax);
		}else{
			$this->Error_model->activaInactivaError($idacuario, 502, 0, $datosReporte->ph->phActual, $datosReporte->ph->phMin, $datosReporte->ph->phMax);
		}
	}


	private function RegistrarPh($idacuario, $datoPh){
		
		$datos = array(
			"idacuario"	=> $idacuario,
			"nivel"	=> $datoPh->phActual,
			"registro"	=> $this->fechayHoraActual()
		);		
		$this->db->insert('nivelpH', $datos);		
	}
	/****************************************************NIVEL DE PH*****************************************************************/
	/********************************************************************************************************************************/
















	/********************************************************************************************************************************/
	/*******************************************ACTUALIZACION DE PARAMETROS**********************************************************/
	


	public function ActualizarParametrosAlimentacion($parametros){
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($parametros->datosAPI);
		if( $infoAcuario ){
			$this->db->set('horario1', $parametros->horario1);
			$this->db->set('cantidad1', $parametros->cantidad1);
			$this->db->set('horario2', $parametros->horario2);
			$this->db->set('cantidad2', $parametros->cantidad2);
			$this->db->set('horario3', $parametros->horario3);
			$this->db->set('cantidad3', $parametros->cantidad3);
			$this->db->where('idacuario', $infoAcuario->idacuario);
			$this->db->update('acuario');
			return true;
		}else{
			return false;
		}
	}

	public function ActualizarParametrosTemperatura($parametros){
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($parametros->datosAPI);
		if( $infoAcuario ){
			$this->db->set('temperaturaMin', $parametros->temperaturaMin);			
			$this->db->set('temperaturaMax', $parametros->temperaturaMax);			
			$this->db->where('idacuario', $infoAcuario->idacuario);
			$this->db->update('acuario');
			return true;
		}else{
			return false;
		}
	}

	public function ActualizarParametrosIluminacion($parametros){
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($parametros->datosAPI);
		if( $infoAcuario ){
			$this->db->set('iluminacionOnTime', $parametros->iluminacionOnTime);			
			$this->db->set('iluminacionOffTime', $parametros->iluminacionOffTime);			
			$this->db->where('idacuario', $infoAcuario->idacuario);
			$this->db->update('acuario');
			return true;
		}else{
			return false;
		}
	}

	public function ActualizarParametrosPh($parametros){
		$infoAcuario = $this->comprorUsuarioAcuarioInformacion($parametros->datosAPI);
		if( $infoAcuario ){
			$this->db->set('phMin', $parametros->phMin);			
			$this->db->set('phMax', $parametros->phMax);			
			$this->db->where('idacuario', $infoAcuario->idacuario);
			$this->db->update('acuario');
			return true;
		}else{
			return false;
		}
	}

	/*******************************************ACTUALIZACION DE PARAMETROS**********************************************************/
	/********************************************************************************************************************************/
}
