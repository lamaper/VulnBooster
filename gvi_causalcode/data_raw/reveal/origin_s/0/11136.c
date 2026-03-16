static uint8_t checkBaseExtBytes ( UCMStates * baseStates , UCMTable * base , UCMTable * ext , UBool moveToExt , UBool intersectBase ) {
 UCMapping * mb , * me ;
 int32_t * baseMap , * extMap ;
 int32_t b , e , bLimit , eLimit , cmp ;
 uint8_t result ;
 UBool isSISO ;
 baseMap = base -> reverseMap ;
 extMap = ext -> reverseMap ;
 b = e = 0 ;
 bLimit = base -> mappingsLength ;
 eLimit = ext -> mappingsLength ;
 result = 0 ;
 isSISO = ( UBool ) ( baseStates -> outputType == MBCS_OUTPUT_2_SISO ) ;
 for ( ;
 ;
 ) {
 for ( ;
 ;
 ++ b ) {
 if ( b == bLimit ) {
 return result ;
 }
 mb = base -> mappings + baseMap [ b ] ;
 if ( intersectBase == 2 && mb -> bLen == 1 ) {
 continue ;
 }
 if ( mb -> f == 0 || mb -> f == 3 ) {
 break ;
 }
 }
 for ( ;
 ;
 ) {
 if ( e == eLimit ) {
 return result ;
 }
 me = ext -> mappings + extMap [ e ] ;
 if ( me -> f == 0 || me -> f == 3 ) {
 break ;
 }
 ++ e ;
 }
 cmp = compareBytes ( base , mb , ext , me , TRUE ) ;
 if ( cmp < 0 ) {
 if ( intersectBase ) {
 mb -> moveFlag |= UCM_MOVE_TO_EXT ;
 result |= NEEDS_MOVE ;
 }
 else if ( mb -> bLen < me -> bLen && ( ! isSISO || mb -> bLen > 1 ) && 0 == uprv_memcmp ( UCM_GET_BYTES ( base , mb ) , UCM_GET_BYTES ( ext , me ) , mb -> bLen ) ) {
 if ( moveToExt ) {
 mb -> moveFlag |= UCM_MOVE_TO_EXT ;
 result |= NEEDS_MOVE ;
 }
 else {
 fprintf ( stderr , "ucm error: the base table contains a mapping whose input sequence\n" " is a prefix of the input sequence of an extension mapping\n" ) ;
 ucm_printMapping ( base , mb , stderr ) ;
 ucm_printMapping ( ext , me , stderr ) ;
 result |= HAS_ERRORS ;
 }
 }
 ++ b ;
 }
 else if ( cmp == 0 ) {
 if ( mb -> f == me -> f && mb -> uLen == me -> uLen && 0 == uprv_memcmp ( UCM_GET_CODE_POINTS ( base , mb ) , UCM_GET_CODE_POINTS ( ext , me ) , 4 * mb -> uLen ) ) {
 me -> moveFlag |= UCM_REMOVE_MAPPING ;
 result |= NEEDS_MOVE ;
 }
 else if ( intersectBase ) {
 mb -> moveFlag |= UCM_MOVE_TO_EXT ;
 result |= NEEDS_MOVE ;
 }
 else {
 fprintf ( stderr , "ucm error: the base table contains a mapping whose input sequence\n" " is the same as the input sequence of an extension mapping\n" " but it maps differently\n" ) ;
 ucm_printMapping ( base , mb , stderr ) ;
 ucm_printMapping ( ext , me , stderr ) ;
 result |= HAS_ERRORS ;
 }
 ++ b ;
 }
 else {
 ++ e ;
 }
 }
 }