static UConverter * U_CALLCONV _ISCII_SafeClone ( const UConverter * cnv , void * stackBuffer , int32_t * pBufferSize , UErrorCode * status ) {
 struct cloneISCIIStruct * localClone ;
 int32_t bufferSizeNeeded = sizeof ( struct cloneISCIIStruct ) ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 if ( * pBufferSize == 0 ) {
 * pBufferSize = bufferSizeNeeded ;
 return 0 ;
 }
 localClone = ( struct cloneISCIIStruct * ) stackBuffer ;
 uprv_memcpy ( & localClone -> mydata , cnv -> extraInfo , sizeof ( UConverterDataISCII ) ) ;
 localClone -> cnv . extraInfo = & localClone -> mydata ;
 localClone -> cnv . isExtraLocal = TRUE ;
 return & localClone -> cnv ;
 }