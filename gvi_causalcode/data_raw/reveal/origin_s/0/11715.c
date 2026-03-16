static long string_hash ( PyStringObject * a ) {
 register Py_ssize_t len ;
 register unsigned char * p ;
 register long x ;


 len = Py_SIZE ( a ) ;
 if ( len == 0 ) {
 a -> ob_shash = 0 ;
 return 0 ;
 }
 p = ( unsigned char * ) a -> ob_sval ;
 x = _Py_HashSecret . prefix ;
 x ^= * p << 7 ;
 while ( -- len >= 0 ) x = ( 1000003 * x ) ^ * p ++ ;
 x ^= Py_SIZE ( a ) ;
 x ^= _Py_HashSecret . suffix ;
 if ( x == - 1 ) x = - 2 ;
 a -> ob_shash = x ;
 return x ;
 }