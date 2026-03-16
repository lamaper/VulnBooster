static UChar32 errorValue ( int32_t count , int8_t strict ) {
 if ( strict >= 0 ) {
 return utf8_errorValue [ count ] ;
 }
 else if ( strict == - 3 ) {
 return 0xfffd ;
 }
 else {
 return U_SENTINEL ;
 }
 }