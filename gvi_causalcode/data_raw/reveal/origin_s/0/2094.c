static UConverter * U_CALLCONV _LMBCSSafeClone ( const UConverter * cnv , void * stackBuffer , int32_t * pBufferSize , UErrorCode * status ) {
 ( void ) status ;
 LMBCSClone * newLMBCS ;
 UConverterDataLMBCS * extraInfo ;
 int32_t i ;
 if ( * pBufferSize <= 0 ) {
 * pBufferSize = ( int32_t ) sizeof ( LMBCSClone ) ;
 return NULL ;
 }
 extraInfo = ( UConverterDataLMBCS * ) cnv -> extraInfo ;
 newLMBCS = ( LMBCSClone * ) stackBuffer ;
 uprv_memcpy ( & newLMBCS -> lmbcs , extraInfo , sizeof ( UConverterDataLMBCS ) ) ;
 for ( i = 0 ;
 i <= ULMBCS_GRP_LAST ;
 ++ i ) {
 if ( extraInfo -> OptGrpConverter [ i ] != NULL ) {
 ucnv_incrementRefCount ( extraInfo -> OptGrpConverter [ i ] ) ;
 }
 }
 newLMBCS -> cnv . extraInfo = & newLMBCS -> lmbcs ;
 newLMBCS -> cnv . isExtraLocal = TRUE ;
 return & newLMBCS -> cnv ;
 }