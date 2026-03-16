static UBool isInOffsetWindowOrDirect ( uint32_t offset , uint32_t c ) {
 return ( UBool ) ( c <= offset + 0x7f && ( c >= offset || ( c <= 0x7f && ( c >= 0x20 || ( 1UL << c ) & 0x2601 ) ) ) ) ;
 }