static PyObject * string_expandtabs ( PyStringObject * self , PyObject * args ) {
 const char * e , * p , * qe ;
 char * q ;
 Py_ssize_t i , j , incr ;
 PyObject * u ;
 int tabsize = 8 ;
 if ( ! PyArg_ParseTuple ( args , "|i:expandtabs" , & tabsize ) ) return NULL ;
 i = 0 ;
 j = 0 ;
 e = PyString_AS_STRING ( self ) + PyString_GET_SIZE ( self ) ;
 for ( p = PyString_AS_STRING ( self ) ;
 p < e ;
 p ++ ) {
 if ( * p == '\t' ) {
 if ( tabsize > 0 ) {
 incr = tabsize - ( j % tabsize ) ;
 if ( j > PY_SSIZE_T_MAX - incr ) goto overflow1 ;
 j += incr ;
 }
 }
 else {
 if ( j > PY_SSIZE_T_MAX - 1 ) goto overflow1 ;
 j ++ ;
 if ( * p == '\n' || * p == '\r' ) {
 if ( i > PY_SSIZE_T_MAX - j ) goto overflow1 ;
 i += j ;
 j = 0 ;
 }
 }
 }
 if ( i > PY_SSIZE_T_MAX - j ) goto overflow1 ;
 u = PyString_FromStringAndSize ( NULL , i + j ) ;
 if ( ! u ) return NULL ;
 j = 0 ;
 q = PyString_AS_STRING ( u ) ;
 qe = PyString_AS_STRING ( u ) + PyString_GET_SIZE ( u ) ;
 for ( p = PyString_AS_STRING ( self ) ;
 p < e ;
 p ++ ) {
 if ( * p == '\t' ) {
 if ( tabsize > 0 ) {
 i = tabsize - ( j % tabsize ) ;
 j += i ;
 while ( i -- ) {
 if ( q >= qe ) goto overflow2 ;
 * q ++ = ' ' ;
 }
 }
 }
 else {
 if ( q >= qe ) goto overflow2 ;
 * q ++ = * p ;
 j ++ ;
 if ( * p == '\n' || * p == '\r' ) j = 0 ;
 }
 }
 return u ;
 overflow2 : Py_DECREF ( u ) ;
 overflow1 : PyErr_SetString ( PyExc_OverflowError , "new string is too long" ) ;
 return NULL ;
 }