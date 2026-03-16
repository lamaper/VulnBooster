void gcry_sexp_dump ( const gcry_sexp_t a ) {
 const byte * p ;
 int indent = 0 ;
 int type ;
 if ( ! a ) {
 log_printf ( "[nil]\n" ) ;
 return ;
 }
 p = a -> d ;
 while ( ( type = * p ) != ST_STOP ) {
 p ++ ;
 switch ( type ) {
 case ST_OPEN : log_printf ( "%*s[open]\n" , 2 * indent , "" ) ;
 indent ++ ;
 break ;
 case ST_CLOSE : if ( indent ) indent -- ;
 log_printf ( "%*s[close]\n" , 2 * indent , "" ) ;
 break ;
 case ST_DATA : {
 DATALEN n ;
 memcpy ( & n , p , sizeof n ) ;
 p += sizeof n ;
 log_printf ( "%*s[data=\"" , 2 * indent , "" ) ;
 dump_string ( p , n , '\"' ) ;
 log_printf ( "\"]\n" ) ;
 p += n ;
 }
 break ;
 default : log_printf ( "%*s[unknown tag %d]\n" , 2 * indent , "" , type ) ;
 break ;
 }
 }
 }