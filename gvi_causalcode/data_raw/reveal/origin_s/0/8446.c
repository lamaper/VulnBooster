static COMPOUND_TEXT_CONVERTERS findStateFromEscSeq ( const char * source , const char * sourceLimit , const uint8_t * toUBytesBuffer , int32_t toUBytesBufferLength , UErrorCode * err ) {
 COMPOUND_TEXT_CONVERTERS state = INVALID ;
 UBool matchFound = FALSE ;
 int32_t i , n , offset = toUBytesBufferLength ;
 for ( i = 0 ;
 i < NUM_OF_CONVERTERS ;
 i ++ ) {
 matchFound = TRUE ;
 for ( n = 0 ;
 escSeqCompoundText [ i ] [ n ] != 0 ;
 n ++ ) {
 if ( n < toUBytesBufferLength ) {
 if ( toUBytesBuffer [ n ] != escSeqCompoundText [ i ] [ n ] ) {
 matchFound = FALSE ;
 break ;
 }
 }
 else if ( ( source + ( n - offset ) ) >= sourceLimit ) {
 * err = U_TRUNCATED_CHAR_FOUND ;
 matchFound = FALSE ;
 break ;
 }
 else if ( * ( source + ( n - offset ) ) != escSeqCompoundText [ i ] [ n ] ) {
 matchFound = FALSE ;
 break ;
 }
 }
 if ( matchFound ) {
 break ;
 }
 }
 if ( matchFound ) {
 state = ( COMPOUND_TEXT_CONVERTERS ) i ;
 }
 return state ;
 }