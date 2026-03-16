UBool ufmt_isdigit ( UChar c , int32_t radix ) {
 int digitVal = ufmt_digitvalue ( c ) ;
 return ( UBool ) ( digitVal < radix && digitVal >= 0 ) ;
 }