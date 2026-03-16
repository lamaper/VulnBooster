PyObject * PyString_FromString ( const char * str ) {
 register size_t size ;
 register PyStringObject * op ;
 assert ( str != NULL ) ;
 size = strlen ( str ) ;
 if ( size > PY_SSIZE_T_MAX - PyStringObject_SIZE ) {
 PyErr_SetString ( PyExc_OverflowError , "string is too long for a Python string" ) ;
 return NULL ;
 }
 if ( size == 0 && ( op = nullstring ) != NULL ) {


 return ( PyObject * ) op ;
 }
 if ( size == 1 && ( op = characters [ * str & UCHAR_MAX ] ) != NULL ) {


 return ( PyObject * ) op ;
 }
 op = ( PyStringObject * ) PyObject_MALLOC ( PyStringObject_SIZE + size ) ;
 if ( op == NULL ) return PyErr_NoMemory ( ) ;
 ( void ) PyObject_INIT_VAR ( op , & PyString_Type , size ) ;
 op -> ob_shash = - 1 ;
 op -> ob_sstate = SSTATE_NOT_INTERNED ;
 Py_MEMCPY ( op -> ob_sval , str , size + 1 ) ;
 if ( size == 0 ) {
 PyObject * t = ( PyObject * ) op ;
 PyString_InternInPlace ( & t ) ;
 op = ( PyStringObject * ) t ;
 nullstring = op ;
 Py_INCREF ( op ) ;
 }
 else if ( size == 1 ) {
 PyObject * t = ( PyObject * ) op ;
 PyString_InternInPlace ( & t ) ;
 op = ( PyStringObject * ) t ;
 characters [ * str & UCHAR_MAX ] = op ;
 Py_INCREF ( op ) ;
 }
 return ( PyObject * ) op ;
 }