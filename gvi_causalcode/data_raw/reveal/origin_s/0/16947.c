static PyObject * authGSSClientWrap ( PyObject * self , PyObject * args ) {
 gss_client_state * state ;
 PyObject * pystate ;
 char * challenge = NULL ;
 char * user = NULL ;
 int protect = 0 ;
 int result = 0 ;
 if ( ! PyArg_ParseTuple ( args , "Os|zi" , & pystate , & challenge , & user , & protect ) ) return NULL ;



 return NULL ;
 }



 result = authenticate_gss_client_wrap ( state , challenge , user , protect ) ;
 if ( result == AUTH_GSS_ERROR ) return NULL ;
 return Py_BuildValue ( "i" , result ) ;
 }