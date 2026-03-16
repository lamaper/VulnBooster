void ufmt_64tou ( UChar * buffer , int32_t * len , uint64_t value , uint8_t radix , UBool uselower , int32_t minDigits ) {
 int32_t length = 0 ;
 uint32_t digit ;
 UChar * left , * right , temp ;
 do {
 digit = ( uint32_t ) ( value % radix ) ;
 value = value / radix ;
 buffer [ length ++ ] = ( UChar ) ( uselower ? TO_LC_DIGIT ( digit ) : TO_UC_DIGIT ( digit ) ) ;
 }
 while ( value ) ;
 if ( minDigits != - 1 && length < minDigits ) {
 while ( length < minDigits && length < * len ) buffer [ length ++ ] = DIGIT_0 ;
 }
 left = buffer ;
 right = buffer + length ;
 while ( left < -- right ) {
 temp = * left ;
 * left ++ = * right ;
 * right = temp ;
 }
 * len = length ;
 }