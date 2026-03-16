PyMODINIT_FUNC init_cbson ( void ) # endif {
 PyObject * m ;
 PyObject * c_api_object ;
 static void * _cbson_API [ _cbson_API_POINTER_COUNT ] ;



 INITERROR ;
 }
 PyDateTime_IMPORT ;
 if ( PyDateTimeAPI == NULL ) {
 Py_DECREF ( m ) ;
 INITERROR ;
 }
 if ( _reload_python_objects ( m ) ) {
 Py_DECREF ( m ) ;
 INITERROR ;
 }
 _cbson_API [ _cbson_buffer_write_bytes_INDEX ] = ( void * ) buffer_write_bytes ;
 _cbson_API [ _cbson_write_dict_INDEX ] = ( void * ) write_dict ;
 _cbson_API [ _cbson_write_pair_INDEX ] = ( void * ) write_pair ;
 _cbson_API [ _cbson_decode_and_write_pair_INDEX ] = ( void * ) decode_and_write_pair ;



 PyModule_AddObject ( m , "_C_API" , c_api_object ) ;
 }

