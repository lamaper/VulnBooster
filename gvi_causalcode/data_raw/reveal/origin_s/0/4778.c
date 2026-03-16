static size_t LMBCSConvertUni ( ulmbcs_byte_t * pLMBCS , UChar uniChar ) {
 uint8_t LowCh = ( uint8_t ) ( uniChar & 0x00FF ) ;
 uint8_t HighCh = ( uint8_t ) ( uniChar >> 8 ) ;
 * pLMBCS ++ = ULMBCS_GRP_UNICODE ;
 if ( LowCh == 0 ) {
 * pLMBCS ++ = ULMBCS_UNICOMPATZERO ;
 * pLMBCS ++ = HighCh ;
 }
 else {
 * pLMBCS ++ = HighCh ;
 * pLMBCS ++ = LowCh ;
 }
 return ULMBCS_UNICODE_SIZE ;
 }