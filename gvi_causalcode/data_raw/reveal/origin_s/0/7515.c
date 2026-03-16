static size_t LMBCSConversionWorker ( UConverterDataLMBCS * extraInfo , ulmbcs_byte_t group , ulmbcs_byte_t * pStartLMBCS , UChar * pUniChar , ulmbcs_byte_t * lastConverterIndex , UBool * groups_tried ) {
 ulmbcs_byte_t * pLMBCS = pStartLMBCS ;
 UConverterSharedData * xcnv = extraInfo -> OptGrpConverter [ group ] ;
 int bytesConverted ;
 uint32_t value ;
 ulmbcs_byte_t firstByte ;
 U_ASSERT ( xcnv ) ;
 U_ASSERT ( group < ULMBCS_GRP_UNICODE ) ;
 bytesConverted = ucnv_MBCSFromUChar32 ( xcnv , * pUniChar , & value , FALSE ) ;
 if ( bytesConverted > 0 ) {
 firstByte = ( ulmbcs_byte_t ) ( value >> ( ( bytesConverted - 1 ) * 8 ) ) ;
 }
 else {
 groups_tried [ group ] = TRUE ;
 return 0 ;
 }
 * lastConverterIndex = group ;
 U_ASSERT ( ( firstByte <= ULMBCS_C0END ) || ( firstByte >= ULMBCS_C1START ) || ( group == ULMBCS_GRP_EXCEPT ) ) ;
 if ( group != ULMBCS_GRP_EXCEPT && extraInfo -> OptGroup != group ) {
 * pLMBCS ++ = group ;
 if ( bytesConverted == 1 && group >= ULMBCS_DOUBLEOPTGROUP_START ) {
 * pLMBCS ++ = group ;
 }
 }
 if ( bytesConverted == 1 && firstByte < 0x20 ) return 0 ;
 switch ( bytesConverted ) {
 case 4 : * pLMBCS ++ = ( ulmbcs_byte_t ) ( value >> 24 ) ;
 U_FALLTHROUGH ;
 case 3 : * pLMBCS ++ = ( ulmbcs_byte_t ) ( value >> 16 ) ;
 U_FALLTHROUGH ;
 case 2 : * pLMBCS ++ = ( ulmbcs_byte_t ) ( value >> 8 ) ;
 U_FALLTHROUGH ;
 case 1 : * pLMBCS ++ = ( ulmbcs_byte_t ) value ;
 U_FALLTHROUGH ;
 default : break ;
 }
 return ( pLMBCS - pStartLMBCS ) ;
 }