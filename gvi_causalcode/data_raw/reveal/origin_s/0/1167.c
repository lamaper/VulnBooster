int ufmt_digitvalue ( UChar c ) {
 if ( ( ( c >= DIGIT_0 ) && ( c <= DIGIT_9 ) ) || ( ( c >= LOWERCASE_A ) && ( c <= LOWERCASE_Z ) ) || ( ( c >= UPPERCASE_A ) && ( c <= UPPERCASE_Z ) ) ) {
 return c - DIGIT_0 - ( c >= 0x0041 ? ( c >= 0x0061 ? 39 : 7 ) : 0 ) ;
 }
 else {
 return - 1 ;
 }
 }