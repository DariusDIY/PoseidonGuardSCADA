<?php
defined('BASEPATH') OR exit('No direct script access allowed');

require APPPATH.'libraries/RestController.php';

use chriskacerguis\RestServer\RestController;

class TankMasterController extends RestController{

  public function __construct(){
		parent::__construct();
		$this->load->database();
    $this->load->model('v1/TankMaster_model');
    date_default_timezone_set('America/La_Paz');
	}


	public function Reporte_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$reporte = $this->TankMaster_model->reportarAcuario($datosDispositivo);
		$this->response($reporte);	
	}
	public function ReporteAlimentacion_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$reporteAlimentacion = $this->TankMaster_model->ReporteAlimentacion($datosDispositivo);
		$this->response($reporteAlimentacion);	
	}
	public function ReportePh_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$reportepH = $this->TankMaster_model->reportepH($datosDispositivo);
		$this->response($reportepH);	
	}

	public function ModoActualizacion_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$actualizacion = $this->TankMaster_model->ModoActualizacionSet($datosDispositivo);
		$this->response($actualizacion);	
	}


	public function ActualizarParametrosAlimentacion_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$actualizacion = $this->TankMaster_model->ActualizarParametrosAlimentacion($datosDispositivo);
		$this->response($actualizacion);	
	}

	public function ActualizarParametrosTemperatura_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$actualizacion = $this->TankMaster_model->ActualizarParametrosTemperatura($datosDispositivo);
		$this->response($actualizacion);	
	}

	public function ActualizarParametrosIluminacion_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$actualizacion = $this->TankMaster_model->ActualizarParametrosIluminacion($datosDispositivo);
		$this->response($actualizacion);	
	}

	public function ActualizarParametrosPh_post(){
		$datosDispositivo = json_decode(file_get_contents("php://input"));
		$actualizacion = $this->TankMaster_model->ActualizarParametrosPh($datosDispositivo);
		$this->response($actualizacion);	
	}
















	

	













}
