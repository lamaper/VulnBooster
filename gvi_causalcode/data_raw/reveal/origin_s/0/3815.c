static int scannum ( struct vars * v ) {
 int n = 0 ;
 while ( SEE ( DIGIT ) && n < DUPMAX ) {
 n = n * 10 + v -> nextvalue ;
 NEXT ( ) ;
 }
 if ( SEE ( DIGIT ) || n > DUPMAX ) {
 ERR ( REG_BADBR ) ;
 return 0 ;
 }
 return n ;
 }