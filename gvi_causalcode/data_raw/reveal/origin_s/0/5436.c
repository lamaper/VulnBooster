static u_long getkeyid ( const char * keyprompt ) {
 int c ;
 FILE * fi ;
 char pbuf [ 20 ] ;
 size_t i ;
 size_t ilim ;

 else setbuf ( fi , ( char * ) NULL ) ;
 fprintf ( stderr , "%s" , keyprompt ) ;
 fflush ( stderr ) ;
 for ( i = 0 , ilim = COUNTOF ( pbuf ) - 1 ;
 i < ilim && ( c = getc ( fi ) ) != '\n' && c != EOF ;
 ) pbuf [ i ++ ] = ( char ) c ;
 pbuf [ i ] = '\0' ;
 if ( fi != stdin ) fclose ( fi ) ;
 return ( u_long ) atoi ( pbuf ) ;
 }