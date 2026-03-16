static size_t get_internal_buffer ( const gcry_sexp_t list , size_t * r_off ) {
 const unsigned char * p ;
 DATALEN n ;
 int type ;
 int level = 0 ;
 * r_off = 0 ;
 if ( list ) {
 p = list -> d ;
 while ( ( type = * p ) != ST_STOP ) {
 p ++ ;
 if ( type == ST_DATA ) {
 memcpy ( & n , p , sizeof n ) ;
 p += sizeof n + n ;
 }
 else if ( type == ST_OPEN ) {
 if ( ! level ) * r_off = ( p - 1 ) - list -> d ;
 level ++ ;
 }
 else if ( type == ST_CLOSE ) {
 level -- ;
 if ( ! level ) return p - list -> d ;
 }
 }
 }
 return 0 ;
 }