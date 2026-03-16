static uint32_t getToUnicodeValue ( CnvExtData * extData , UCMTable * table , UCMapping * m ) {
 UChar32 * u32 ;
 UChar * u ;
 uint32_t value ;
 int32_t u16Length , ratio ;
 UErrorCode errorCode ;
 if ( m -> uLen == 1 ) {
 u16Length = U16_LENGTH ( m -> u ) ;
 value = ( uint32_t ) ( UCNV_EXT_TO_U_MIN_CODE_POINT + m -> u ) ;
 }
 else {
 u32 = UCM_GET_CODE_POINTS ( table , m ) ;
 errorCode = U_ZERO_ERROR ;
 u_strFromUTF32 ( NULL , 0 , & u16Length , u32 , m -> uLen , & errorCode ) ;
 if ( U_FAILURE ( errorCode ) && errorCode != U_BUFFER_OVERFLOW_ERROR ) {
 exit ( errorCode ) ;
 }
 value = ( ( ( uint32_t ) u16Length + UCNV_EXT_TO_U_LENGTH_OFFSET ) << UCNV_EXT_TO_U_LENGTH_SHIFT ) | ( ( uint32_t ) utm_countItems ( extData -> toUUChars ) ) ;
 u = utm_allocN ( extData -> toUUChars , u16Length ) ;
 errorCode = U_ZERO_ERROR ;
 u_strFromUTF32 ( u , u16Length , NULL , u32 , m -> uLen , & errorCode ) ;
 if ( U_FAILURE ( errorCode ) && errorCode != U_BUFFER_OVERFLOW_ERROR ) {
 exit ( errorCode ) ;
 }
 }
 if ( m -> f == 0 ) {
 value |= UCNV_EXT_TO_U_ROUNDTRIP_FLAG ;
 }
 if ( m -> bLen > extData -> maxInBytes ) {
 extData -> maxInBytes = m -> bLen ;
 }
 if ( u16Length > extData -> maxOutUChars ) {
 extData -> maxOutUChars = u16Length ;
 }
 ratio = ( u16Length + ( m -> bLen - 1 ) ) / m -> bLen ;
 if ( ratio > extData -> maxUCharsPerByte ) {
 extData -> maxUCharsPerByte = ratio ;
 }
 return value ;
 }