static PyObject * string_partition ( PyStringObject * self , PyObject * sep_obj ) {
 const char * sep ;
 Py_ssize_t sep_len ;
 if ( PyString_Check ( sep_obj ) ) {
 sep = PyString_AS_STRING ( sep_obj ) ;
 sep_len = PyString_GET_SIZE ( sep_obj ) ;
 }


 return stringlib_partition ( ( PyObject * ) self , PyString_AS_STRING ( self ) , PyString_GET_SIZE ( self ) , sep_obj , sep , sep_len ) ;
 }