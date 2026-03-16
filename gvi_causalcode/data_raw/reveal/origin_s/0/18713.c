static int32_t findUnassigned ( UCMStates * states , uint16_t * unicodeCodeUnits , _MBCSToUFallback * toUFallbacks , int32_t countToUFallbacks , int32_t state , int32_t offset , uint32_t b ) {
 int32_t i , entry , savings , localSavings , belowSavings ;
 UBool haveAssigned ;
 localSavings = belowSavings = 0 ;
 haveAssigned = FALSE ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 entry = states -> stateTable [ state ] [ i ] ;
 if ( MBCS_ENTRY_IS_TRANSITION ( entry ) ) {
 savings = findUnassigned ( states , unicodeCodeUnits , toUFallbacks , countToUFallbacks , MBCS_ENTRY_TRANSITION_STATE ( entry ) , offset + MBCS_ENTRY_TRANSITION_OFFSET ( entry ) , ( b << 8 ) | ( uint32_t ) i ) ;
 if ( savings < 0 ) {
 haveAssigned = TRUE ;
 }
 else if ( savings > 0 ) {
 printf ( " all-unassigned sequences from prefix 0x%02lx state %ld use %ld bytes\n" , ( unsigned long ) ( ( b << 8 ) | i ) , ( long ) state , ( long ) savings ) ;
 belowSavings += savings ;
 }
 }
 else if ( ! haveAssigned ) {
 switch ( MBCS_ENTRY_FINAL_ACTION ( entry ) ) {
 case MBCS_STATE_VALID_16 : entry = offset + MBCS_ENTRY_FINAL_VALUE_16 ( entry ) ;
 if ( unicodeCodeUnits [ entry ] == 0xfffe && ucm_findFallback ( toUFallbacks , countToUFallbacks , entry ) < 0 ) {
 localSavings += 2 ;
 }
 else {
 haveAssigned = TRUE ;
 }
 break ;
 case MBCS_STATE_VALID_16_PAIR : entry = offset + MBCS_ENTRY_FINAL_VALUE_16 ( entry ) ;
 if ( unicodeCodeUnits [ entry ] == 0xfffe ) {
 localSavings += 4 ;
 }
 else {
 haveAssigned = TRUE ;
 }
 break ;
 default : break ;
 }
 }
 }
 if ( haveAssigned ) {
 return - 1 ;
 }
 else {
 return localSavings + belowSavings ;
 }
 }