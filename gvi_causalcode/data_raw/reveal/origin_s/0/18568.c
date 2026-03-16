static uint32_t getFromUBytesValue ( CnvExtData * extData , UCMTable * table , UCMapping * m ) {
 uint8_t * bytes , * resultBytes ;
 uint32_t value ;
 int32_t u16Length , ratio ;
 if ( m -> f == 2 ) {
 return UCNV_EXT_FROM_U_SUBCHAR1 ;
 }
 bytes = UCM_GET_BYTES ( table , m ) ;
 value = 0 ;
 switch ( m -> bLen ) {
 case 3 : value = ( ( uint32_t ) * bytes ++ ) << 16 ;
 case 2 : value |= ( ( uint32_t ) * bytes ++ ) << 8 ;
 case 1 : value |= * bytes ;
 break ;
 default : value = ( uint32_t ) utm_countItems ( extData -> fromUBytes ) ;
 resultBytes = utm_allocN ( extData -> fromUBytes , m -> bLen ) ;
 uprv_memcpy ( resultBytes , bytes , m -> bLen ) ;
 break ;
 }
 value |= ( uint32_t ) m -> bLen << UCNV_EXT_FROM_U_LENGTH_SHIFT ;
 if ( m -> f == 0 ) {
 value |= UCNV_EXT_FROM_U_ROUNDTRIP_FLAG ;
 }
 else if ( m -> f == 4 ) {
 value |= UCNV_EXT_FROM_U_GOOD_ONE_WAY_FLAG ;
 }
 if ( m -> uLen == 1 ) {
 u16Length = U16_LENGTH ( m -> u ) ;
 }
 else {
 u16Length = U16_LENGTH ( UCM_GET_CODE_POINTS ( table , m ) [ 0 ] ) + ( m -> uLen - 2 ) ;
 }
 if ( u16Length > extData -> maxInUChars ) {
 extData -> maxInUChars = u16Length ;
 }
 if ( m -> bLen > extData -> maxOutBytes ) {
 extData -> maxOutBytes = m -> bLen ;
 }
 ratio = ( m -> bLen + ( u16Length - 1 ) ) / u16Length ;
 if ( ratio > extData -> maxBytesPerUChar ) {
 extData -> maxBytesPerUChar = ratio ;
 }
 return value ;
 }