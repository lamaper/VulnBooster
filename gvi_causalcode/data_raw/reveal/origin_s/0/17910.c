static uint32_t write8 ( FileStream * out , uint8_t byte , uint32_t column ) {
 char s [ 4 ] ;
 int i = 0 ;
 if ( byte >= 100 ) {
 s [ i ++ ] = ( char ) ( '0' + byte / 100 ) ;
 byte %= 100 ;
 }
 if ( i > 0 || byte >= 10 ) {
 s [ i ++ ] = ( char ) ( '0' + byte / 10 ) ;
 byte %= 10 ;
 }
 s [ i ++ ] = ( char ) ( '0' + byte ) ;
 s [ i ] = 0 ;
 if ( column == MAX_COLUMN ) {
 column = 1 ;
 }
 else if ( column < 16 ) {
 T_FileStream_writeLine ( out , "," ) ;
 ++ column ;
 }
 else {
 T_FileStream_writeLine ( out , ",\n" ) ;
 column = 1 ;
 }
 T_FileStream_writeLine ( out , s ) ;
 return column ;
 }