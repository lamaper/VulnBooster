int gcry_sexp_length ( const gcry_sexp_t list ) {
 const byte * p ;
 DATALEN n ;
 int type ;
 int length = 0 ;
 int level = 0 ;
 if ( ! list ) return 0 ;
 p = list -> d ;
 while ( ( type = * p ) != ST_STOP ) {
 p ++ ;
 if ( type == ST_DATA ) {
 memcpy ( & n , p , sizeof n ) ;
 p += sizeof n + n ;
 if ( level == 1 ) length ++ ;
 }
 else if ( type == ST_OPEN ) {
 if ( level == 1 ) length ++ ;
 level ++ ;
 }
 else if ( type == ST_CLOSE ) {
 level -- ;
 }
 }
 return length ;
 }