size_t gcry_sexp_sprint ( const gcry_sexp_t list , int mode , void * buffer , size_t maxlength ) {
 static unsigned char empty [ 3 ] = {
 ST_OPEN , ST_CLOSE , ST_STOP }
 ;
 const unsigned char * s ;
 char * d ;
 DATALEN n ;
 char numbuf [ 20 ] ;
 size_t len = 0 ;
 int i , indent = 0 ;
 s = list ? list -> d : empty ;
 d = buffer ;
 while ( * s != ST_STOP ) {
 switch ( * s ) {
 case ST_OPEN : s ++ ;
 if ( mode != GCRYSEXP_FMT_CANON ) {
 if ( indent ) len ++ ;
 len += indent ;
 }
 len ++ ;
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 if ( mode != GCRYSEXP_FMT_CANON ) {
 if ( indent ) * d ++ = '\n' ;
 for ( i = 0 ;
 i < indent ;
 i ++ ) * d ++ = ' ' ;
 }
 * d ++ = '(' ;
 }
 indent ++ ;
 break ;
 case ST_CLOSE : s ++ ;
 len ++ ;
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 * d ++ = ')' ;
 }
 indent -- ;
 if ( * s != ST_OPEN && * s != ST_STOP && mode != GCRYSEXP_FMT_CANON ) {
 len ++ ;
 len += indent ;
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 * d ++ = '\n' ;
 for ( i = 0 ;
 i < indent ;
 i ++ ) * d ++ = ' ' ;
 }
 }
 break ;
 case ST_DATA : s ++ ;
 memcpy ( & n , s , sizeof n ) ;
 s += sizeof n ;
 if ( mode == GCRYSEXP_FMT_ADVANCED ) {
 int type ;
 size_t nn ;
 switch ( ( type = suitable_encoding ( s , n ) ) ) {
 case 1 : nn = convert_to_string ( s , n , NULL ) ;
 break ;
 case 2 : nn = convert_to_token ( s , n , NULL ) ;
 break ;
 default : nn = convert_to_hex ( s , n , NULL ) ;
 break ;
 }
 len += nn ;
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 switch ( type ) {
 case 1 : convert_to_string ( s , n , d ) ;
 break ;
 case 2 : convert_to_token ( s , n , d ) ;
 break ;
 default : convert_to_hex ( s , n , d ) ;
 break ;
 }
 d += nn ;
 }
 if ( s [ n ] != ST_CLOSE ) {
 len ++ ;
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 * d ++ = ' ' ;
 }
 }
 }
 else {
 sprintf ( numbuf , "%u:" , ( unsigned int ) n ) ;
 len += strlen ( numbuf ) + n ;
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 d = stpcpy ( d , numbuf ) ;
 memcpy ( d , s , n ) ;
 d += n ;
 }
 }
 s += n ;
 break ;
 default : BUG ( ) ;
 }
 }
 if ( mode != GCRYSEXP_FMT_CANON ) {
 len ++ ;
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 * d ++ = '\n' ;
 }
 }
 if ( buffer ) {
 if ( len >= maxlength ) return 0 ;
 * d ++ = 0 ;
 }
 else len ++ ;
 return len ;
 }