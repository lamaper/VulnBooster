int write_dict ( PyObject * self , buffer_t buffer , PyObject * dict , unsigned char check_keys , unsigned char uuid_subtype , unsigned char top_level ) {
 PyObject * key ;
 PyObject * iter ;
 char zero = 0 ;
 int length ;
 int length_location ;
 if ( ! PyDict_Check ( dict ) ) {
 PyObject * repr = PyObject_Repr ( dict ) ;

 PyObject * error = PyUnicode_Concat ( errmsg , repr ) ;
 PyErr_SetObject ( PyExc_TypeError , error ) ;
 Py_DECREF ( error ) ;
 Py_DECREF ( repr ) ;

 PyString_ConcatAndDel ( & errmsg , repr ) ;
 PyErr_SetString ( PyExc_TypeError , PyString_AsString ( errmsg ) ) ;

 return 0 ;
 }
 length_location = buffer_save_space ( buffer , 4 ) ;
 if ( length_location == - 1 ) {
 PyErr_NoMemory ( ) ;
 return 0 ;
 }
 if ( top_level ) {
 PyObject * _id = PyDict_GetItemString ( dict , "_id" ) ;
 if ( _id ) {
 if ( ! write_pair ( self , buffer , "_id" , 3 , _id , 0 , uuid_subtype , 1 ) ) {
 return 0 ;
 }
 }
 }
 iter = PyObject_GetIter ( dict ) ;
 if ( iter == NULL ) {
 return 0 ;
 }
 while ( ( key = PyIter_Next ( iter ) ) != NULL ) {
 PyObject * value = PyDict_GetItem ( dict , key ) ;
 if ( ! value ) {
 PyErr_SetObject ( PyExc_KeyError , key ) ;
 Py_DECREF ( key ) ;
 Py_DECREF ( iter ) ;
 return 0 ;
 }
 if ( ! decode_and_write_pair ( self , buffer , key , value , check_keys , uuid_subtype , top_level ) ) {
 Py_DECREF ( key ) ;
 Py_DECREF ( iter ) ;
 return 0 ;
 }
 Py_DECREF ( key ) ;
 }
 Py_DECREF ( iter ) ;
 if ( ! buffer_write_bytes ( buffer , & zero , 1 ) ) {
 return 0 ;
 }
 length = buffer_get_position ( buffer ) - length_location ;
 memcpy ( buffer_get_buffer ( buffer ) + length_location , & length , 4 ) ;
 return 1 ;
 }