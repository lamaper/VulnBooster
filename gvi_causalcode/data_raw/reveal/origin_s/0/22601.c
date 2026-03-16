static int32_t getRunFromLogicalIndex ( UBiDi * pBiDi , int32_t logicalIndex , UErrorCode * pErrorCode ) {
 Run * runs = pBiDi -> runs ;
 int32_t runCount = pBiDi -> runCount , visualStart = 0 , i , length , logicalStart ;
 for ( i = 0 ;
 i < runCount ;
 i ++ ) {
 length = runs [ i ] . visualLimit - visualStart ;
 logicalStart = GET_INDEX ( runs [ i ] . logicalStart ) ;
 if ( ( logicalIndex >= logicalStart ) && ( logicalIndex < ( logicalStart + length ) ) ) {
 return i ;
 }
 visualStart += length ;
 }
 U_ASSERT ( FALSE ) ;
 * pErrorCode = U_INVALID_STATE_ERROR ;
 return 0 ;
 }