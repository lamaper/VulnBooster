static PyObject * string_join ( PyStringObject * self , PyObject * orig ) {
 char * sep = PyString_AS_STRING ( self ) ;
 const Py_ssize_t seplen = PyString_GET_SIZE ( self ) ;
 PyObject * res = NULL ;
 char * p ;
 Py_ssize_t seqlen = 0 ;
 size_t sz = 0 ;
 Py_ssize_t i ;
 PyObject * seq , * item ;
 seq = PySequence_Fast ( orig , "can only join an iterable" ) ;
 if ( seq == NULL ) {
 return NULL ;
 }
 seqlen = PySequence_Size ( seq ) ;
 if ( seqlen == 0 ) {
 Py_DECREF ( seq ) ;
 return PyString_FromString ( "" ) ;
 }
 if ( seqlen == 1 ) {
 item = PySequence_Fast_GET_ITEM ( seq , 0 ) ;
 if ( PyString_CheckExact ( item ) || PyUnicode_CheckExact ( item ) ) {
 Py_INCREF ( item ) ;
 Py_DECREF ( seq ) ;
 return item ;
 }
 }
 for ( i = 0 ;
 i < seqlen ;
 i ++ ) {
 const size_t old_sz = sz ;
 item = PySequence_Fast_GET_ITEM ( seq , i ) ;
 if ( ! PyString_Check ( item ) ) {

 PyObject * result ;
 result = PyUnicode_Join ( ( PyObject * ) self , seq ) ;
 Py_DECREF ( seq ) ;
 return result ;
 }

 Py_DECREF ( seq ) ;
 return NULL ;
 }
 sz += PyString_GET_SIZE ( item ) ;
 if ( i != 0 ) sz += seplen ;
 if ( sz < old_sz || sz > PY_SSIZE_T_MAX ) {
 PyErr_SetString ( PyExc_OverflowError , "join() result is too long for a Python string" ) ;
 Py_DECREF ( seq ) ;
 return NULL ;
 }
 }
 res = PyString_FromStringAndSize ( ( char * ) NULL , sz ) ;
 if ( res == NULL ) {
 Py_DECREF ( seq ) ;
 return NULL ;
 }
 p = PyString_AS_STRING ( res ) ;
 for ( i = 0 ;
 i < seqlen ;
 ++ i ) {
 size_t n ;
 item = PySequence_Fast_GET_ITEM ( seq , i ) ;
 n = PyString_GET_SIZE ( item ) ;
 Py_MEMCPY ( p , PyString_AS_STRING ( item ) , n ) ;
 p += n ;
 if ( i < seqlen - 1 ) {
 Py_MEMCPY ( p , sep , seplen ) ;
 p += seplen ;
 }
 }
 Py_DECREF ( seq ) ;
 return res ;
 }