static void indent ( int32_t count , FILE * f ) {
 char c [ BUF_SIZE ] ;
 if ( count <= 0 ) {
 return ;
 }
 if ( count < BUF_SIZE ) {
 memset ( c , ( int ) ' ' , count ) ;
 fwrite ( c , sizeof ( char ) , count , f ) ;
 }
 else {
 int32_t i ;
 for ( i = 0 ;
 i < count ;
 ++ i ) putc ( ' ' , f ) ;
 }
 }