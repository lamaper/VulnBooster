static void printMapping ( UCMapping * m , UChar32 * codePoints , uint8_t * bytes , FILE * f ) {
 int32_t j ;
 for ( j = 0 ;
 j < m -> uLen ;
 ++ j ) {
 fprintf ( f , "<U%04lX>" , ( long ) codePoints [ j ] ) ;
 }
 fputc ( ' ' , f ) ;
 for ( j = 0 ;
 j < m -> bLen ;
 ++ j ) {
 fprintf ( f , "\\x%02X" , bytes [ j ] ) ;
 }
 if ( m -> f >= 0 ) {
 fprintf ( f , " |%u\n" , m -> f ) ;
 }
 else {
 fputs ( "\n" , f ) ;
 }
 }