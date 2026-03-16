static PyObject * string_str ( PyObject * s ) {
 assert ( PyString_Check ( s ) ) ;
 if ( PyString_CheckExact ( s ) ) {
 Py_INCREF ( s ) ;
 return s ;
 }
 else {
 PyStringObject * t = ( PyStringObject * ) s ;
 return PyString_FromStringAndSize ( t -> ob_sval , Py_SIZE ( t ) ) ;
 }
 }