<?php
$config = array(
    'registroPiloto' => array(
        array('field' => 'idhub',           'label' => 'Hub',         'rules' => 'required|integer'),
        array('field' => 'idpais',          'label' => 'País',        'rules' => 'required|integer'),
        array('field' => 'ciudad',          'label' => 'Ciudad',      'rules' => 'required|min_length[3]|max_length[80]'),
        array('field' => 'nombre',          'label' => 'Nombre',      'rules' => 'required|min_length[3]|max_length[50]'),
        array('field' => 'apellido',        'label' => 'Apellido',    'rules' => 'required|min_length[3]|max_length[50]'),
        array('field' => 'email',           'label' => 'Email',       'rules' => 'required|valid_email|min_length[5]|max_length[120]'),
        array('field' => 'vid',             'label' => 'Vid',         'rules' => 'required|integer|min_length[6]|max_length[6]'),
        array('field' => 'nacimiento',      'label' => 'nacimiento',  'rules' => 'required'),
        array('field' => 'idioma',          'label' => 'Idioma',      'rules' => 'required|integer'),
        array('field' => 'password',        'label' => 'password',    'rules' => 'required|min_length[8]|max_length[15]'),
        array('field' => 'repeatPassword',  'label' => 'password',    'rules' => 'required|min_length[8]|max_length[15]|matches[password]'),
      ),
    'loginPiloto' => array(
        array('field' => 'email',           'label' => 'Email',       'rules' => 'required|valid_email|min_length[5]|max_length[120]'),
        array('field' => 'password',        'label' => 'password',    'rules' => 'required|min_length[8]|max_length[15]'),
      ),
);


?>
