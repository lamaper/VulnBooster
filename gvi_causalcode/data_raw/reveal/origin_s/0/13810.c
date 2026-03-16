static UBool isPNJConsonant ( UChar32 c ) {
 if ( c < 0xa00 || 0xa50 <= c ) {
 return FALSE ;
 }
 else {
 return ( UBool ) ( pnjMap [ c - 0xa00 ] & 1 ) ;
 }
 }