static int storesid ( struct alltabs * at , const char * str ) {
 int i ;
 FILE * news ;
 const char * pt ;
 long pos ;
 if ( str != NULL ) {
 for ( i = 0 ;
 cffnames [ i ] != NULL ;
 ++ i ) {
 if ( strcmp ( cffnames [ i ] , str ) == 0 ) return ( i ) ;
 }
 }
 pos = ftell ( at -> sidf ) + 1 ;
 if ( pos >= 65536 && ! at -> sidlongoffset ) {
 at -> sidlongoffset = true ;
 news = tmpfile ( ) ;
 rewind ( at -> sidh ) ;
 for ( i = 0 ;
 i < at -> sidcnt ;
 ++ i ) putlong ( news , getushort ( at -> sidh ) ) ;
 fclose ( at -> sidh ) ;
 at -> sidh = news ;
 }
 if ( at -> sidlongoffset ) putlong ( at -> sidh , pos ) ;
 else putshort ( at -> sidh , pos ) ;
 if ( str != NULL ) {
 for ( pt = str ;
 * pt ;
 ++ pt ) putc ( * pt , at -> sidf ) ;
 }
 return ( at -> sidcnt ++ + nStdStrings ) ;
 }