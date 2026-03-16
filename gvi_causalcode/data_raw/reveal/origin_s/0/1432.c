static const char * sexp_nth_data ( const gcry_sexp_t list , int number , size_t * datalen ) {
 const byte * p ;
 DATALEN n ;
 int level = 0 ;
 * datalen = 0 ;
 if ( ! list ) return NULL ;
 p = list -> d ;
 if ( * p == ST_OPEN ) p ++ ;
 else if ( number ) return NULL ;
 while ( number > 0 ) {
 if ( * p == ST_DATA ) {
 memcpy ( & n , ++ p , sizeof n ) ;
 p += sizeof n + n ;
 p -- ;
 if ( ! level ) number -- ;
 }
 else if ( * p == ST_OPEN ) {
 level ++ ;
 }
 else if ( * p == ST_CLOSE ) {
 level -- ;
 if ( ! level ) number -- ;
 }
 else if ( * p == ST_STOP ) {
 return NULL ;
 }
 p ++ ;
 }
 if ( * p == ST_DATA ) {
 memcpy ( & n , ++ p , sizeof n ) ;
 * datalen = n ;
 return ( const char * ) p + sizeof n ;
 }
 return NULL ;
 }