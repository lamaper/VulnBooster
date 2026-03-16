void gcry_sexp_release ( gcry_sexp_t sexp ) {
 if ( sexp ) {
 if ( gcry_is_secure ( sexp ) ) {
 const byte * p = sexp -> d ;
 int type ;
 while ( ( type = * p ) != ST_STOP ) {
 p ++ ;
 switch ( type ) {
 case ST_OPEN : break ;
 case ST_CLOSE : break ;
 case ST_DATA : {
 DATALEN n ;
 memcpy ( & n , p , sizeof n ) ;
 p += sizeof n ;
 p += n ;
 }
 break ;
 default : break ;
 }
 }
 wipememory ( sexp -> d , p - sexp -> d ) ;
 }
 gcry_free ( sexp ) ;
 }
 }