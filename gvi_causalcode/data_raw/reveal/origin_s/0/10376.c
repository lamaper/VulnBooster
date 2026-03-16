static int32 getuint32 ( FILE * ttf ) {
 int ch1 = getc ( ttf ) ;
 int ch2 = getc ( ttf ) ;
 int ch3 = getc ( ttf ) ;
 int ch4 = getc ( ttf ) ;
 if ( ch4 == EOF ) return ( EOF ) ;
 return ( ( ch1 << 24 ) | ( ch2 << 16 ) | ( ch3 << 8 ) | ch4 ) ;
 }