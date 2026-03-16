static PyObject * string_concat ( register PyStringObject * a , register PyObject * bb ) {
 register Py_ssize_t size ;
 register PyStringObject * op ;
 if ( ! PyString_Check ( bb ) ) {


 PyErr_Format ( PyExc_TypeError , "cannot concatenate 'str' and '%.200s' objects" , Py_TYPE ( bb ) -> tp_name ) ;
 return NULL ;
 }

 if ( Py_SIZE ( a ) == 0 ) {
 Py_INCREF ( bb ) ;
 return bb ;
 }
 Py_INCREF ( a ) ;
 return ( PyObject * ) a ;
 }
 if ( Py_SIZE ( a ) < 0 || Py_SIZE ( b ) < 0 || Py_SIZE ( a ) > PY_SSIZE_T_MAX - Py_SIZE ( b ) ) {
 PyErr_SetString ( PyExc_OverflowError , "strings are too large to concat" ) ;
 return NULL ;
 }
 size = Py_SIZE ( a ) + Py_SIZE ( b ) ;
 if ( size > PY_SSIZE_T_MAX - PyStringObject_SIZE ) {
 PyErr_SetString ( PyExc_OverflowError , "strings are too large to concat" ) ;
 return NULL ;
 }
 op = ( PyStringObject * ) PyObject_MALLOC ( PyStringObject_SIZE + size ) ;
 if ( op == NULL ) return PyErr_NoMemory ( ) ;
 ( void ) PyObject_INIT_VAR ( op , & PyString_Type , size ) ;
 op -> ob_shash = - 1 ;
 op -> ob_sstate = SSTATE_NOT_INTERNED ;
 Py_MEMCPY ( op -> ob_sval , a -> ob_sval , Py_SIZE ( a ) ) ;
 Py_MEMCPY ( op -> ob_sval + Py_SIZE ( a ) , b -> ob_sval , Py_SIZE ( b ) ) ;
 op -> ob_sval [ size ] = '\0' ;
 return ( PyObject * ) op ;
