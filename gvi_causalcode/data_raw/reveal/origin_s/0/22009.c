static PyObject * authGSSServerInit ( PyObject * self , PyObject * args ) {
 const char * service = NULL ;
 gss_server_state * state ;
 PyObject * pystate ;
 int result = 0 ;
 if ( ! PyArg_ParseTuple ( args , "s" , & service ) ) return NULL ;
 state = ( gss_server_state * ) malloc ( sizeof ( gss_server_state ) ) ;



 if ( result == AUTH_GSS_ERROR ) return NULL ;
 return Py_BuildValue ( "(iO)" , result , pystate ) ;
 }