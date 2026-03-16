static PyObject * _cbson_bson_to_dict ( PyObject * self , PyObject * args ) {
 unsigned int size ;
 Py_ssize_t total_size ;
 const char * string ;
 PyObject * bson ;
 PyObject * as_class ;
 unsigned char tz_aware ;
 unsigned char uuid_subtype ;
 PyObject * dict ;
 PyObject * remainder ;
 PyObject * result ;
 if ( ! PyArg_ParseTuple ( args , "OObb" , & bson , & as_class , & tz_aware , & uuid_subtype ) ) {
 return NULL ;
 }

 PyErr_SetString ( PyExc_TypeError , "argument to _bson_to_dict must be a bytes object" ) ;

 PyErr_SetString ( PyExc_TypeError , "argument to _bson_to_dict must be a string" ) ;

 }



 PyObject * InvalidBSON = _error ( "InvalidBSON" ) ;
 PyErr_SetString ( InvalidBSON , "not enough data for a BSON document" ) ;
 Py_DECREF ( InvalidBSON ) ;
 return NULL ;
 }



 return NULL ;
 }
 memcpy ( & size , string , 4 ) ;
 if ( total_size < size ) {
 PyObject * InvalidBSON = _error ( "InvalidBSON" ) ;
 PyErr_SetString ( InvalidBSON , "objsize too large" ) ;
 Py_DECREF ( InvalidBSON ) ;
 return NULL ;
 }
 if ( size != total_size || string [ size - 1 ] ) {
 PyObject * InvalidBSON = _error ( "InvalidBSON" ) ;
 PyErr_SetString ( InvalidBSON , "bad eoo" ) ;
 Py_DECREF ( InvalidBSON ) ;
 return NULL ;
 }
 dict = elements_to_dict ( self , string + 4 , size - 5 , as_class , tz_aware , uuid_subtype ) ;
 if ( ! dict ) {
 return NULL ;
 }



 Py_DECREF ( dict ) ;
 return NULL ;
 }
 result = Py_BuildValue ( "OO" , dict , remainder ) ;
 Py_DECREF ( dict ) ;
 Py_DECREF ( remainder ) ;
 return result ;
 }