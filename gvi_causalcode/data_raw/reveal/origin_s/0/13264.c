static void U_CALLCONV _HZ_WriteSub ( UConverterFromUnicodeArgs * args , int32_t offsetIndex , UErrorCode * err ) {
 UConverter * cnv = args -> converter ;
 UConverterDataHZ * convData = ( UConverterDataHZ * ) cnv -> extraInfo ;
 char * p ;
 char buffer [ 4 ] ;
 p = buffer ;
 if ( convData -> isTargetUCharDBCS ) {
 * p ++ = UCNV_TILDE ;
 * p ++ = UCNV_CLOSE_BRACE ;
 convData -> isTargetUCharDBCS = FALSE ;
 }
 * p ++ = ( char ) cnv -> subChars [ 0 ] ;
 ucnv_cbFromUWriteBytes ( args , buffer , ( int32_t ) ( p - buffer ) , offsetIndex , err ) ;
 }