static UChar GetUniFromLMBCSUni ( char const * * ppLMBCSin ) {
 uint8_t HighCh = * ( * ppLMBCSin ) ++ ;
 uint8_t LowCh = * ( * ppLMBCSin ) ++ ;
 if ( HighCh == ULMBCS_UNICOMPATZERO ) {
 HighCh = LowCh ;
 LowCh = 0 ;
 }
 return ( UChar ) ( ( HighCh << 8 ) | LowCh ) ;
 }