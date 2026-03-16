int decodets ( char * str , l_fp * lfp ) {
 char * cp ;
 char buf [ 30 ] ;
 size_t b ;
 if ( * str == '0' && ( * ( str + 1 ) == 'x' || * ( str + 1 ) == 'X' ) ) return hextolfp ( str + 2 , lfp ) ;
 if ( * str == '"' ) {
 cp = str + 1 ;
 b = 0 ;
 while ( '"' != * cp && '\0' != * cp && b < COUNTOF ( buf ) - 1 ) buf [ b ++ ] = * cp ++ ;
 buf [ b ] = '\0' ;
 return rtdatetolfp ( buf , lfp ) ;
 }
 if ( ( * str >= 'A' && * str <= 'F' ) || ( * str >= 'a' && * str <= 'f' ) ) return hextolfp ( str , lfp ) ;
 if ( atolfp ( str , lfp ) ) return 1 ;
 return rtdatetolfp ( str , lfp ) ;
 }