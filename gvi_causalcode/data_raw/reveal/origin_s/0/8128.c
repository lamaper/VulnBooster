static PyObject * string_islower ( PyStringObject * self ) {
 register const unsigned char * p = ( unsigned char * ) PyString_AS_STRING ( self ) ;
 register const unsigned char * e ;
 int cased ;
 if ( PyString_GET_SIZE ( self ) == 1 ) return PyBool_FromLong ( islower ( * p ) != 0 ) ;
 if ( PyString_GET_SIZE ( self ) == 0 ) return PyBool_FromLong ( 0 ) ;
 e = p + PyString_GET_SIZE ( self ) ;
 cased = 0 ;
 for ( ;
 p < e ;
 p ++ ) {
 if ( isupper ( * p ) ) return PyBool_FromLong ( 0 ) ;
 else if ( ! cased && islower ( * p ) ) cased = 1 ;
 }
 return PyBool_FromLong ( cased ) ;
 }