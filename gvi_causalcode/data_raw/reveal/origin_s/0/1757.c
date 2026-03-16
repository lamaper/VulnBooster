void appendStringLiteral ( PQExpBuffer buf , const char * str , int encoding , bool std_strings ) {
 size_t length = strlen ( str ) ;
 const char * source = str ;
 char * target ;
 if ( ! enlargePQExpBuffer ( buf , 2 * length + 2 ) ) return ;
 target = buf -> data + buf -> len ;
 * target ++ = '\'' ;
 while ( * source != '\0' ) {
 char c = * source ;
 int len ;
 int i ;
 if ( ! IS_HIGHBIT_SET ( c ) ) {
 if ( SQL_STR_DOUBLE ( c , ! std_strings ) ) * target ++ = c ;
 * target ++ = c ;
 source ++ ;
 continue ;
 }
 len = PQmblen ( source , encoding ) ;
 for ( i = 0 ;
 i < len ;
 i ++ ) {
 if ( * source == '\0' ) break ;
 * target ++ = * source ++ ;
 }
 if ( i < len ) {
 char * stop = buf -> data + buf -> maxlen - 2 ;
 for ( ;
 i < len ;
 i ++ ) {
 if ( target >= stop ) break ;
 * target ++ = ' ' ;
 }
 break ;
 }
 }
 * target ++ = '\'' ;
 * target = '\0' ;
 buf -> len = target - buf -> data ;
 }