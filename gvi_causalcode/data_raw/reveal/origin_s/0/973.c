static char * new_command_generator ( const char * text , int state ) {
 static int textlen ;
 char * ptr ;
 static Bucket * b ;
 static entry * e ;
 static uint i ;
 if ( ! state ) textlen = ( uint ) strlen ( text ) ;
 if ( textlen > 0 ) {
 if ( ! state ) {
 uint len ;
 b = find_all_matches ( & ht , text , ( uint ) strlen ( text ) , & len ) ;
 if ( ! b ) return NullS ;
 e = b -> pData ;
 }
 if ( e ) {
 ptr = strdup ( e -> str ) ;
 e = e -> pNext ;
 return ptr ;
 }
 }
 else {
 if ( ! state ) {
 for ( i = 0 ;
 i < ht . nTableSize ;
 i ++ ) {
 if ( ht . arBuckets [ i ] ) {
 b = ht . arBuckets [ i ] ;
 e = b -> pData ;
 break ;
 }
 }
 }
 ptr = NullS ;
 while ( e && ! ptr ) {
 if ( ( uint ) strlen ( e -> str ) == b -> nKeyLength ) ptr = strdup ( e -> str ) ;
 e = e -> pNext ;
 if ( ! e ) {
 b = b -> pNext ;
 if ( ! b ) {
 for ( i ++ ;
 i < ht . nTableSize ;
 i ++ ) {
 if ( ht . arBuckets [ i ] ) {
 b = ht . arBuckets [ i ] ;
 e = b -> pData ;
 break ;
 }
 }
 }
 else e = b -> pData ;
 }
 }
 if ( ptr ) return ptr ;
 }
 return NullS ;
 }