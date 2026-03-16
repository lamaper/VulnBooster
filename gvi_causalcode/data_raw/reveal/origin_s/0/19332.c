static uint8_t checkBaseExtUnicode ( UCMStates * baseStates , UCMTable * base , UCMTable * ext , UBool moveToExt , UBool intersectBase ) {
 ( void ) baseStates ;
 UCMapping * mb , * me , * mbLimit , * meLimit ;
 int32_t cmp ;
 uint8_t result ;
 mb = base -> mappings ;
 mbLimit = mb + base -> mappingsLength ;
 me = ext -> mappings ;
 meLimit = me + ext -> mappingsLength ;
 result = 0 ;
 for ( ;
 ;
 ) {
 for ( ;
 ;
 ) {
 if ( mb == mbLimit ) {
 return result ;
 }
 if ( ( 0 <= mb -> f && mb -> f <= 2 ) || mb -> f == 4 ) {
 break ;
 }
 ++ mb ;
 }
 for ( ;
 ;
 ) {
 if ( me == meLimit ) {
 return result ;
 }
 if ( ( 0 <= me -> f && me -> f <= 2 ) || me -> f == 4 ) {
 break ;
 }
 ++ me ;
 }
 cmp = compareUnicode ( base , mb , ext , me ) ;
 if ( cmp < 0 ) {
 if ( intersectBase && ( intersectBase != 2 || mb -> bLen > 1 ) ) {
 mb -> moveFlag |= UCM_MOVE_TO_EXT ;
 result |= NEEDS_MOVE ;
 }
 else if ( mb -> uLen < me -> uLen && 0 == uprv_memcmp ( UCM_GET_CODE_POINTS ( base , mb ) , UCM_GET_CODE_POINTS ( ext , me ) , 4 * mb -> uLen ) ) {
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
 ++ mb ;
 }
 else if ( cmp == 0 ) {
 if ( mb -> f == me -> f && mb -> bLen == me -> bLen && 0 == uprv_memcmp ( UCM_GET_BYTES ( base , mb ) , UCM_GET_BYTES ( ext , me ) , mb -> bLen ) ) {
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
 ++ mb ;
 }
 else {
 ++ me ;
 }
 }
 }