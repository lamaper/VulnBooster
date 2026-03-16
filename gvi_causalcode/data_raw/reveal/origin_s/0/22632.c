PyObject * PyString_AsEncodedObject ( PyObject * str , const char * encoding , const char * errors ) {
 PyObject * v ;
 if ( ! PyString_Check ( str ) ) {
 PyErr_BadArgument ( ) ;
 goto onError ;
 }
 if ( encoding == NULL ) {


 goto onError ;

 v = _PyCodec_EncodeText ( str , encoding , errors ) ;
 if ( v == NULL ) goto onError ;
 return v ;
 onError : return NULL ;
 }