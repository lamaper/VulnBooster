static PyObject * string_replace ( PyStringObject * self , PyObject * args ) {
 Py_ssize_t count = - 1 ;
 PyObject * from , * to ;
 const char * from_s , * to_s ;
 Py_ssize_t from_len , to_len ;
 if ( ! PyArg_ParseTuple ( args , "OO|n:replace" , & from , & to , & count ) ) return NULL ;
 if ( PyString_Check ( from ) ) {
 from_s = PyString_AS_STRING ( from ) ;
 from_len = PyString_GET_SIZE ( from ) ;
 }


 if ( PyString_Check ( to ) ) {
 to_s = PyString_AS_STRING ( to ) ;
 to_len = PyString_GET_SIZE ( to ) ;
 }


 return ( PyObject * ) replace ( ( PyStringObject * ) self , from_s , from_len , to_s , to_len , count ) ;
 }