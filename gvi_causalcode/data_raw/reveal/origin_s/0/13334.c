static void compactToUnicodeHelper ( UCMStates * states , uint16_t * unicodeCodeUnits , _MBCSToUFallback * toUFallbacks , int32_t countToUFallbacks ) {
 int32_t state , savings ;
 for ( state = 0 ;
 state < states -> countStates ;
 ++ state ) {
 if ( ( states -> stateFlags [ state ] & 0xf ) == MBCS_STATE_FLAG_DIRECT ) {
 savings = findUnassigned ( states , unicodeCodeUnits , toUFallbacks , countToUFallbacks , state , 0 , 0 ) ;
 if ( savings > 0 ) {
 printf ( " all-unassigned sequences from initial state %ld use %ld bytes\n" , ( long ) state , ( long ) savings ) ;
 }
 }
 }
 }