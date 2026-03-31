<?php
defined('BASEPATH') OR exit('No direct script access allowed');

require APPPATH.'libraries/RestController.php';

use chriskacerguis\RestServer\RestController;

class WebSiteController extends RestController{

  public function __construct(){
		parent::__construct();
		$this->load->database();
		$this->load->helper('url');
   		$this->load->model('v1/WebSite_model');
   		$this->load->model('v1/Error_model');
    	date_default_timezone_set('America/La_Paz');
	}

	


	public function ErrorReport_get(){
		$reporteError = $this->Error_model->ReporteDeErroresPorTelegram();
		$this->response($reporteError);			
	}
	

	public function ErrorLista_get(){
		$clave = $this->uri->segment(4);
		$reporteError = $this->WebSite_model->traerErroresPanel($clave);
		$this->response($reporteError);			
	}





	public function PanelControl_get(){
		$clave = $this->uri->segment(4);
		$acuarios = $this->WebSite_model->traerInfoAcuarios($clave, 0);
		$this->response($acuarios);	
	}
	public function ConfiguracionesAcuario_get(){
		$clave = $this->uri->segment(4);
		$idacuario = $this->uri->segment(5);
		$acuario = $this->WebSite_model->traerInfoAcuarios($clave, $idacuario);
		$this->response($acuario);	
	}

	public function ConfiguracionesGuardarCambios_post(){
		$datosAcuario = json_decode(file_get_contents("php://input"));
		$resultado = $this->WebSite_model->GuardarConfiguraciones($datosAcuario);
		$this->response($resultado);
	}
	public function ConfiguracionesAgregarPez_post(){
		$pezSeleccionado = json_decode(file_get_contents("php://input"));
		$resultado = $this->WebSite_model->agregarPezConfiguraciones($pezSeleccionado);
		$this->response($resultado);
	}
	public function ConfiguracionesQuitarPez_post(){
		$pezSeleccionado = json_decode(file_get_contents("php://input"));
		$resultado = $this->WebSite_model->quitarPezConfiguraciones($pezSeleccionado);
		$this->response($resultado);
	}




	public function HistorialAcuario_post(){
		$datosBusquedaHistorial = json_decode(file_get_contents("php://input"));
		$resultado = $this->WebSite_model->consultarHistorialAcuario($datosBusquedaHistorial);
		$this->response($resultado);
	}






	public function RecargarAlimentadorAl100_get(){
		$clave = $this->uri->segment(4);
		$idacuario = $this->uri->segment(5);
		$resultado = $this->WebSite_model->RecargarAlimentadorAl100($clave, $idacuario);
		$this->response($resultado);
	}







	public function AgregarAcuario_post(){
		$datosAcuarioNuevo = json_decode(file_get_contents("php://input"));
		$resultado = $this->WebSite_model->AgregarAcuarioNuevo($datosAcuarioNuevo);
		$this->response($resultado);
	}
	












	public function ListaPeces_get(){
		//https://www.pornhub.com/view_video.php?viewkey=6864bab556f65
		//https://www.pornhub.com/view_video.php?viewkey=ph5e67da569483f
		$resultado = $this->WebSite_model->traerListaCompletaPeces();
		$this->response($resultado);
	}



	
	public function ListaAgregarPez_post(){
		$datosPezNuevo = json_decode(file_get_contents("php://input"));
		if (empty($_FILES['foto']['name'])) {
            echo json_encode(['error' => 'No se envió ningún archivo.']);
            return;
        }

        $config['upload_path']   = '../assets/images/peces';
        $config['allowed_types'] = 'jpg|jpeg|png|gif';
        $config['max_size']      = 2048; // 2 MB
        $config['encrypt_name']  = TRUE;

        $this->load->library('upload', $config);

        if (!$this->upload->do_upload('foto')) {
			$mensaje = array(
				'error' => $this->upload->display_errors('', ''),
				'config' => $config
			);
            echo json_encode($mensaje);
        } else {
            $data = $this->upload->data();
            $image_url = base_url('uploads/' . $data['file_name']);

			$mensaje = array(
				'success' => true,
				'data'	=> $this->input->post('nombreCientifico'),
				'url' => $image_url
			);

            echo json_encode($mensaje);
        }

		//$resultado = $this->WebSite_model->traerListaCompletaPeces();
		//$this->response($datosPezNuevo);
	}






	







	public function Login_post(){
		$datosUsuarioLogin = json_decode(file_get_contents("php://input"));
		$resultadoLogin = $this->WebSite_model->RealizarLogin($datosUsuarioLogin);
		$this->response($resultadoLogin);	
	}
	public function LoginAuthGuard_get(){
		$clave = $this->uri->segment(4);
		$resultadoAutentificacion = $this->WebSite_model->RealizarAutenticacion($clave);
		$this->response($resultadoAutentificacion);	
	}


	













}
