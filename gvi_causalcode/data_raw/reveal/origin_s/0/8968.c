static gcry_sexp_t normalize ( gcry_sexp_t list ) {
 unsigned char * p ;
 if ( ! list ) return NULL ;
 p = list -> d ;
 if ( * p == ST_STOP ) {
 gcry_sexp_release ( list ) ;
 return NULL ;
 }
 if ( * p == ST_OPEN && p [ 1 ] == ST_CLOSE ) {
 gcry_sexp_release ( list ) ;
 return NULL ;
 }
 return list ;
 }