bool parsePGArray ( const char * atext , char * * * itemarray , int * nitems ) {
 int inputlen ;
 char * * items ;
 char * strings ;
 int curitem ;
 * itemarray = NULL ;
 * nitems = 0 ;
 inputlen = strlen ( atext ) ;
 if ( inputlen < 2 || atext [ 0 ] != '{
' || atext [ inputlen - 1 ] != '}
' ) return false ;
 items = ( char * * ) malloc ( inputlen * ( sizeof ( char * ) + sizeof ( char ) ) ) ;
 if ( items == NULL ) return false ;
 * itemarray = items ;
 strings = ( char * ) ( items + inputlen ) ;
 atext ++ ;
 curitem = 0 ;
 while ( * atext != '}
' ) {
 if ( * atext == '\0' ) return false ;
 items [ curitem ] = strings ;
 while ( * atext != '}
' && * atext != ',' ) {
 if ( * atext == '\0' ) return false ;
 if ( * atext != '"' ) * strings ++ = * atext ++ ;
 else {
 atext ++ ;
 while ( * atext != '"' ) {
 if ( * atext == '\0' ) return false ;
 if ( * atext == '\\' ) {
 atext ++ ;
 if ( * atext == '\0' ) return false ;
 }
 * strings ++ = * atext ++ ;
 }
 atext ++ ;
 }
 }
 * strings ++ = '\0' ;
 if ( * atext == ',' ) atext ++ ;
 curitem ++ ;
 }
 if ( atext [ 1 ] != '\0' ) return false ;
 * nitems = curitem ;
 return true ;
 }