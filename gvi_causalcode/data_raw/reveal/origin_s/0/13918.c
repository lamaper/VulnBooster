static PyObject * authGSSServerStep ( PyObject * self , PyObject * args ) {
 gss_server_state * state ;
 PyObject * pystate ;
 char * challenge = NULL ;
 int result = 0 ;
 if ( ! PyArg_ParseTuple ( args , "Os" , & pystate , & challenge ) ) return NULL ;



 return NULL ;
 }



 result = authenticate_gss_server_step ( state , challenge ) ;
 if ( result == AUTH_GSS_ERROR ) return NULL ;
 return Py_BuildValue ( "i" , result ) ;
 }