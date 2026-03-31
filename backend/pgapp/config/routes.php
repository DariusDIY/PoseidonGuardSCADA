<?php
defined('BASEPATH') OR exit('No direct script access allowed');


$route['default_controller'] = 'welcome';
$route['404_override'] = '';
$route['translate_uri_dashes'] = FALSE;
/****************************************************************************************/
/***************************************TANKMASTER***************************************/
$route['v1/TankMaster/Reporte'] = 'v1/TankMasterController/Reporte';			 // POST
$route['v1/TankMaster/ReporteAlimentacion'] = 'v1/TankMasterController/ReporteAlimentacion'; // POST
$route['v1/TankMaster/ReportePh'] = 'v1/TankMasterController/ReportePh'; // POST
$route['v1/TankMaster/ModoActualizacion'] = 'v1/TankMasterController/ModoActualizacion'; // POST

$route['v1/TankMaster/ActualizarParametrosAlimentacion'] = 'v1/TankMasterController/ActualizarParametrosAlimentacion'; // POST
$route['v1/TankMaster/ActualizarParametrosTemperatura'] = 'v1/TankMasterController/ActualizarParametrosTemperatura'; // POST
$route['v1/TankMaster/ActualizarParametrosIluminacion'] = 'v1/TankMasterController/ActualizarParametrosIluminacion'; // POST
$route['v1/TankMaster/ActualizarParametrosPh'] = 'v1/TankMasterController/ActualizarParametrosPh'; // POST

/***************************************TANKMASTER***************************************/
/****************************************************************************************/


/****************************************************************************************/
/****************************************WEBSITE*****************************************/
$route['v1/WebSite/PanelControl/(:any)'] = 'v1/WebSiteController/PanelControl/$1'; // GET keypass
$route['v1/WebSite/Configuraciones/(:any)/(:any)'] = 'v1/WebSiteController/ConfiguracionesAcuario/$1/$2'; // GET keypass/idacuario
$route['v1/WebSite/Configuraciones/GuardarCambios'] = 'v1/WebSiteController/ConfiguracionesGuardarCambios'; // POST 
$route['v1/WebSite/Configuraciones/AgregarPez'] = 'v1/WebSiteController/ConfiguracionesAgregarPez'; // POST 
$route['v1/WebSite/Configuraciones/QuitarPez'] = 'v1/WebSiteController/ConfiguracionesQuitarPez'; // POST 

$route['v1/WebSite/Historial'] = 'v1/WebSiteController/HistorialAcuario'; // POST

$route['v1/WebSite/Pez/ListaPeces'] = 'v1/WebSiteController/ListaPeces'; // GET
$route['v1/WebSite/Pez/AgregarPez'] = 'v1/WebSiteController/ListaAgregarPez'; // POST


$route['v1/WebSite/Login'] = 'v1/WebSiteController/Login'; // POST
$route['v1/WebSite/LoginAuthGuard/(:any)'] = 'v1/WebSiteController/LoginAuthGuard/$1'; // GET

$route['v1/WebSite/RecargarAlimentadorAl100/(:any)/(:any)'] = 'v1/WebSiteController/RecargarAlimentadorAl100/$1/$2'; // GET keypass/idacuario


$route['v1/WebSite/ErrorReport'] = 'v1/WebSiteController/ErrorReport'; // GET Envio del reporte automatico de errores IMPORTANTE PARA LOS REPORTES DE TELEGRAM

$route['v1/WebSite/ErrorLista/(:any)'] = 'v1/WebSiteController/ErrorLista/$1'; // GET keypass Envio del reporte automatico de errores

$route['v1/WebSite/AgregarAcuario'] = 'v1/WebSiteController/AgregarAcuario'; // POST
/****************************************WEBSITE*****************************************/
/****************************************************************************************/
