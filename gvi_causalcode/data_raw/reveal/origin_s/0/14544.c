static int32_t getPairIndex ( UChar32 ch ) {
 int32_t pairedCharCount = UPRV_LENGTHOF ( pairedChars ) ;
 int32_t pairedCharPower = 1 << highBit ( pairedCharCount ) ;
 int32_t pairedCharExtra = pairedCharCount - pairedCharPower ;
 int32_t probe = pairedCharPower ;
 int32_t pairIndex = 0 ;
 if ( ch >= pairedChars [ pairedCharExtra ] ) {
 pairIndex = pairedCharExtra ;
 }
 while ( probe > ( 1 << 0 ) ) {
 probe >>= 1 ;
 if ( ch >= pairedChars [ pairIndex + probe ] ) {
 pairIndex += probe ;
 }
 }
 if ( pairedChars [ pairIndex ] != ch ) {
 pairIndex = - 1 ;
 }
 return pairIndex ;
 }