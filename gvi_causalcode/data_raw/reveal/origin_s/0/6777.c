static int32_t ucnv_internalConvert ( UConverter * outConverter , UConverter * inConverter , char * target , int32_t targetCapacity , const char * source , int32_t sourceLength , UErrorCode * pErrorCode ) {
 UChar pivotBuffer [ CHUNK_SIZE ] ;
 UChar * pivot , * pivot2 ;
 char * myTarget ;
 const char * sourceLimit ;
 const char * targetLimit ;
 int32_t targetLength = 0 ;
 if ( sourceLength < 0 ) {
 sourceLimit = uprv_strchr ( source , 0 ) ;
 }
 else {
 sourceLimit = source + sourceLength ;
 }
 if ( source == sourceLimit ) {
 return u_terminateChars ( target , targetCapacity , 0 , pErrorCode ) ;
 }
 pivot = pivot2 = pivotBuffer ;
 myTarget = target ;
 targetLength = 0 ;
 if ( targetCapacity > 0 ) {
 targetLimit = target + targetCapacity ;
 ucnv_convertEx ( outConverter , inConverter , & myTarget , targetLimit , & source , sourceLimit , pivotBuffer , & pivot , & pivot2 , pivotBuffer + CHUNK_SIZE , FALSE , TRUE , pErrorCode ) ;
 targetLength = ( int32_t ) ( myTarget - target ) ;
 }
 if ( * pErrorCode == U_BUFFER_OVERFLOW_ERROR || targetCapacity == 0 ) {
 char targetBuffer [ CHUNK_SIZE ] ;
 targetLimit = targetBuffer + CHUNK_SIZE ;
 do {
 * pErrorCode = U_ZERO_ERROR ;
 myTarget = targetBuffer ;
 ucnv_convertEx ( outConverter , inConverter , & myTarget , targetLimit , & source , sourceLimit , pivotBuffer , & pivot , & pivot2 , pivotBuffer + CHUNK_SIZE , FALSE , TRUE , pErrorCode ) ;
 targetLength += ( int32_t ) ( myTarget - targetBuffer ) ;
 }
 while ( * pErrorCode == U_BUFFER_OVERFLOW_ERROR ) ;
 return u_terminateChars ( target , targetCapacity , targetLength , pErrorCode ) ;
 }
 return targetLength ;
 }