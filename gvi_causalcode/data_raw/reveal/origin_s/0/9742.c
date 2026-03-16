static PyObject * authGSSClientInit ( PyObject * self , PyObject * args , PyObject * keywds ) {
 const char * service = NULL ;
 const char * principal = NULL ;
 gss_client_state * state ;
 PyObject * pystate ;
 static char * kwlist [ ] = {
 "service" , "principal" , "gssflags" , NULL }
 ;
 long int gss_flags = GSS_C_MUTUAL_FLAG | GSS_C_SEQUENCE_FLAG ;
 int result = 0 ;
 if ( ! PyArg_ParseTupleAndKeywords ( args , keywds , "s|zl" , kwlist , & service , & principal , & gss_flags ) ) return NULL ;
 state = ( gss_client_state * ) malloc ( sizeof ( gss_client_state ) ) ;



 if ( result == AUTH_GSS_ERROR ) return NULL ;
 return Py_BuildValue ( "(iO)" , result , pystate ) ;
 }