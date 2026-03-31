<?php

class Error_model extends CI_Model {


  private function fechayHoraActual(){
    $currentDateTimeBolivia = new DateTime('now', new DateTimeZone('America/La_Paz'));
    $currentDateTimeBoliviaFormato = $currentDateTimeBolivia->format('Y-m-d H:i:s');
    return $currentDateTimeBoliviaFormato;
  }

  public function pruebaModelo(){
	return "Funciona Error";
  }

  public function ReporteDeErroresPorTelegram(){	
 	$apiToken = "5699773502:AAFjxM9BESaNbvMvv2RxChWlXNoq1j4zVcA";

	$acuarios = $this->traerAcuarios();
	foreach ($acuarios as $acuario) {
		$this->verificarConexionDispositivo($acuario->idacuario);		
	}


	$erroresActivos = $this->traerErroresActivos();

	if($erroresActivos != ""){
		$data = [
			 'chat_id' => '-4603631389',
	         'text' => $erroresActivos
		];
		$response = file_get_contents("https://api.telegram.org/bot$apiToken/sendMessage?".http_build_query($data) );
	}
		

	return json_encode($erroresActivos);

  }


  private function traerAcuarios(){
	$this->db->select('idacuario');
	$this->db->from('acuario');
	$this->db->order_by('idacuario', 'ASC');
	$query = $this->db->get();
	$acuarios = $query->result();
	return $acuarios;
  }


  private function traerErroresActivos(){
	$this->db->select('*');
	$this->db->from('registroError');
	$this->db->join('acuario', 'acuario.idacuario = registroError.idacuario');
	$this->db->where('activo', 1);
	$this->db->order_by('registroError.idacuario', 'ASC');
	$this->db->order_by('registroError.codigo', 'ASC');
	$query = $this->db->get();
	$errores = $query->result();
	

	$mensaje = "";

	$reporteDispositivo = "";
	$dispositivos = array();

	if($errores){
		$dispositivo = "";
		foreach ($errores as $dispositivoAcuario) {
			
			if($dispositivo != $dispositivoAcuario->apiKeyAcuario){
				$dispositivo = $dispositivoAcuario->apiKeyAcuario;
				array_push($dispositivos, $dispositivo);			
			}
		}

		foreach ($dispositivos as $dispositivoSelect) {
			$reporteDispositivo = "";
			$reporteDispositivo .= "*************".$dispositivoSelect."*************"."\n";
			foreach ($errores as $error) {
				if($error->apiKeyAcuario == $dispositivoSelect){
					$reporteDispositivo .= $this->codigoError($error->registro, intval($error->codigo), $error->valorActual, $error->valorMinimo, $error->valorMaximo). "\n\n";
				}
			}
			$reporteDispositivo .= "********************************\n\n";
			$mensaje .= $reporteDispositivo;
		}
	}
	return $mensaje;
  }


  private function verificarConexionDispositivo($idacuario){
	
	$this->db->select('reporte');
	$this->db->from('acuario');
	$this->db->where('idacuario', $idacuario);
	$this->db->where('estado', 1);
	$query = $this->db->get();
	$reporteAcuario = $query->row();

	$tiempoActual = new DateTime($this->fechayHoraActual());
	$tiempoReporte = new DateTime($reporteAcuario->reporte);

	$diferencia = $tiempoReporte->diff($tiempoActual);

	$segundos = ($diferencia->days * 24 * 60 * 60) +
                ($diferencia->h * 60 * 60) +
                ($diferencia->i * 60) +
                $diferencia->s;

	if($segundos > 60){
		//Activar Error 101 Dispositivo desconectado
		//return "Activar Error 101 Dispositivo desconectado ". $segundos;
		$this->activaInactivaError($idacuario, 101, 1);
	}else{
		//Desactivar Error 101 Dispositivo desconectado
		//return "Desactivar Error 101 Dispositivo desconectado ". $segundos;
		$this->activaInactivaError($idacuario, 101, 0);
	}

  }





  public function crearActualizarError($idregistroError, $idacuario, $codigoError, $activo, $valorActual=NULL, $valorMinimo=NULL, $valorMaximo=NULL){
	$data = array(
		'idacuario'     => $idacuario,
		'codigo' 	    => $codigoError,
		"activo"		=> $activo,
		"valorActual"	=> $valorActual,
		"valorMinimo"	=> $valorMinimo,
		"valorMaximo"	=> $valorMaximo,
		"registro"		=> $this->fechayHoraActual()
	);
	if($idregistroError == -1){
		//crear registro	
		$this->db->insert('registroError', $data);
	}else{
		//Actualizar registro
		$this->db->where('idregistroError', $idregistroError);
		$this->db->update('registroError', $data);
	}
		
  }

  public function activaInactivaError($idacuario, $codigoError, $activo, $valorActual=NULL, $valorMinimo=NULL, $valorMaximo=NULL){
	$idregistroError = $this->verificaExistenciaError($idacuario, $codigoError);
	$this->crearActualizarError($idregistroError , $idacuario, $codigoError, $activo, $valorActual, $valorMinimo, $valorMaximo);
  }

  

  private function verificaExistenciaError($idacuario, $codigoError){
	$this->db->select('*');
	$this->db->from('registroError');
	$this->db->where('idacuario', $idacuario);
	$this->db->where('codigo', $codigoError);
	$query = $this->db->get();
	$errorExistente = $query->row();
	if($errorExistente){
		return intval($errorExistente->idregistroError);
	}else{
		return -1;
	}
  }






  private function codigoError($registro, $errorCode, $valorActual, $valorMinimo, $valorMaximo){
	/*
		101 Dispositivo desconectado
		-----------------------------------
		201 Error de Tempertarura Baja
		202 Error de Tempertarura Alta
		203 Error de Termometro 1
		204 Error de Termometro 2
		205 Error de calentador 1
		206 Error de calentador 2
		------------------------------------
		301 Advertencia de alimentador debajo del 50%
		302 Advertencia de alimentador debajo del 25%
		303 Advertencia de alimentador vacio
		------------------------------------
		401 Error de Iluminacion de encendido
		402 Error de Iluminacion de apagado
		------------------------------------
		501 Error de nivel de ph Bajo
		501 Error de nivel de ph Alto		
	*/

	$mensaje = "*".$registro . "> ";

	switch ($errorCode) {
		case '101':
			return $mensaje."Dispositivo desconectado.";
			break;

		case '201':
			return $mensaje."Error de tempertarura baja. / Actual:".$valorActual." Mínimo:".$valorMinimo;
			break;
		case '202':
			return $mensaje."Error de tempertarura alta. / Actual:".$valorActual." Máximo':".$valorMaximo;
			break;
		case '203':
			return $mensaje."Error de termometro 1.";
			break;
		case '204':
			return $mensaje."Error de termometro 2.";
			break;
		case '205':
			return $mensaje."Error de calentador 1.";
			break;
		case '206':
			return $mensaje."Error de calentador 2.";
			break;

		case '301':
			return $mensaje."Advertencia de alimentador debajo del 50%.";
			break;
		case '302':
			return $mensaje."Advertencia de alimentador debajo del 25%.";
			break;
		case '303':
			return $mensaje."Advertencia de alimentador vacio.";
			break;

		case '401':
			return $mensaje."Error de Iluminacion (Encendido).";
			break;
		case '402':
			return $mensaje."Error de Iluminacion (Apagado).";
			break;

		case '501':
			return $mensaje."Error de nivel de ph bajo. / Actual:".$valorActual." Mínimo:". $valorMinimo;
			break;
		case '502':
			return $mensaje."Error de nivel de ph alto. / Actual:".$valorActual." Máximo:". $valorMaximo;
			break;
			
		
		default:
			break;
	}
	
  }




  



}