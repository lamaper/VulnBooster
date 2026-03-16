static void dumphex ( struct hexout * hexout , FILE * temp , int length ) {
 int i , ch , ch1 ;
 if ( length & 1 ) LogError ( _ ( "Table length should not be odd\n" ) ) ;
 while ( length > 65534 ) {
 dumphex ( hexout , temp , 65534 ) ;
 length -= 65534 ;
 }
 fprintf ( hexout -> type42 , " <\n " ) ;
 hexout -> bytesout = 0 ;
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 ch = getc ( temp ) ;
 if ( ch == EOF ) break ;
 if ( hexout -> bytesout >= 31 ) {
 fprintf ( hexout -> type42 , "\n " ) ;
 hexout -> bytesout = 0 ;
 }
 ch1 = ch >> 4 ;
 if ( ch1 >= 10 ) ch1 += 'A' - 10 ;
 else ch1 += '0' ;
 putc ( ch1 , hexout -> type42 ) ;
 ch1 = ch & 0xf ;
 if ( ch1 >= 10 ) ch1 += 'A' - 10 ;
 else ch1 += '0' ;
 putc ( ch1 , hexout -> type42 ) ;
 ++ hexout -> bytesout ;
 }
 fprintf ( hexout -> type42 , "\n 00\n >\n" ) ;
 }