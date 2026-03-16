static PyObject * authGSSServerResponse ( PyObject * self , PyObject * args ) {
 gss_server_state * state ;
 PyObject * pystate ;
 if ( ! PyArg_ParseTuple ( args , "O" , & pystate ) ) return NULL ;



 return NULL ;
 }



 return Py_BuildValue ( "s" , state -> response ) ;
 }