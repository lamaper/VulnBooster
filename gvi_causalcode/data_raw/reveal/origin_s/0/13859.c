static PyObject * authGSSServerClean ( PyObject * self , PyObject * args ) {
 gss_server_state * state ;
 PyObject * pystate ;
 int result = 0 ;
 if ( ! PyArg_ParseTuple ( args , "O" , & pystate ) ) return NULL ;



 return NULL ;
 }



 result = authenticate_gss_server_clean ( state ) ;
 free ( state ) ;



 return Py_BuildValue ( "i" , result ) ;
 }