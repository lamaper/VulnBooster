bool appendReloptionsArray ( PQExpBuffer buffer , const char * reloptions , const char * prefix , int encoding , bool std_strings ) {
 char * * options ;
 int noptions ;
 int i ;
 if ( ! parsePGArray ( reloptions , & options , & noptions ) ) {
 if ( options ) free ( options ) ;
 return false ;
 }
 for ( i = 0 ;
 i < noptions ;
 i ++ ) {
 char * option = options [ i ] ;
 char * name ;
 char * separator ;
 char * value ;
 name = option ;
 separator = strchr ( option , '=' ) ;
 if ( separator ) {
 * separator = '\0' ;
 value = separator + 1 ;
 }
 else value = "" ;
 if ( i > 0 ) appendPQExpBufferStr ( buffer , ", " ) ;
 appendPQExpBuffer ( buffer , "%s%s=" , prefix , fmtId ( name ) ) ;
 if ( strcmp ( fmtId ( value ) , value ) == 0 ) appendPQExpBufferStr ( buffer , value ) ;
 else appendStringLiteral ( buffer , value , encoding , std_strings ) ;
 }
 if ( options ) free ( options ) ;
 return true ;
 }