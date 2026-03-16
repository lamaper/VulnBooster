static int write_string ( buffer_t buffer , PyObject * py_string ) {
 Py_ssize_t string_length ;
 const char * string ;

 return write_unicode ( buffer , py_string ) ;
 }
 string = PyBytes_AsString ( py_string ) ;


 return 0 ;
 }



 return 0 ;
 }
 if ( ! buffer_write_bytes ( buffer , string , string_length ) ) {
 return 0 ;
 }
 return 1 ;
 }