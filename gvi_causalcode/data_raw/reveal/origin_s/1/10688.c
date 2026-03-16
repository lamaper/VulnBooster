static UConverter * _SCSUSafeClone ( const UConverter * cnv , void * stackBuffer , int32_t * pBufferSize , UErrorCode * status ) {
 struct cloneSCSUStruct * localClone ;
 int32_t bufferSizeNeeded = sizeof ( struct cloneSCSUStruct ) ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 if ( * pBufferSize == 0 ) {
 * pBufferSize = bufferSizeNeeded ;
 return 0 ;
 }
 localClone = ( struct cloneSCSUStruct * ) stackBuffer ;
 uprv_memcpy ( & localClone -> mydata , cnv -> extraInfo , sizeof ( SCSUData ) ) ;
 localClone -> cnv . extraInfo = & localClone -> mydata ;
 localClone -> cnv . isExtraLocal = TRUE ;
 return & localClone -> cnv ;
 }