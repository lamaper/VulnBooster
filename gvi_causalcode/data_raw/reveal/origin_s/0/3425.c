static int32_t sumUpStates ( UCMStates * states ) {
 int32_t entry , sum , state , cell , count ;
 UBool allStatesReady ;
 allStatesReady = FALSE ;
 for ( count = states -> countStates ;
 ! allStatesReady && count >= 0 ;
 -- count ) {
 allStatesReady = TRUE ;
 for ( state = states -> countStates - 1 ;
 state >= 0 ;
 -- state ) {
 if ( ! ( states -> stateFlags [ state ] & MBCS_STATE_FLAG_READY ) ) {
 allStatesReady = FALSE ;
 sum = 0 ;
 for ( cell = 0 ;
 cell < 256 ;
 ++ cell ) {
 entry = states -> stateTable [ state ] [ cell ] ;
 if ( MBCS_ENTRY_IS_FINAL ( entry ) ) {
 switch ( MBCS_ENTRY_FINAL_ACTION ( entry ) ) {
 case MBCS_STATE_VALID_16 : states -> stateTable [ state ] [ cell ] = MBCS_ENTRY_FINAL_SET_VALUE ( entry , sum ) ;
 sum += 1 ;
 break ;
 case MBCS_STATE_VALID_16_PAIR : states -> stateTable [ state ] [ cell ] = MBCS_ENTRY_FINAL_SET_VALUE ( entry , sum ) ;
 sum += 2 ;
 break ;
 default : break ;
 }
 }
 }
 for ( cell = 0 ;
 cell < 256 ;
 ++ cell ) {
 entry = states -> stateTable [ state ] [ cell ] ;
 if ( MBCS_ENTRY_IS_TRANSITION ( entry ) ) {
 if ( states -> stateFlags [ MBCS_ENTRY_TRANSITION_STATE ( entry ) ] & MBCS_STATE_FLAG_READY ) {
 states -> stateTable [ state ] [ cell ] = MBCS_ENTRY_TRANSITION_SET_OFFSET ( entry , sum ) ;
 sum += states -> stateOffsetSum [ MBCS_ENTRY_TRANSITION_STATE ( entry ) ] ;
 }
 else {
 sum = - 1 ;
 break ;
 }
 }
 }
 if ( sum != - 1 ) {
 states -> stateOffsetSum [ state ] = sum ;
 states -> stateFlags [ state ] |= MBCS_STATE_FLAG_READY ;
 }
 }
 }
 }
 if ( ! allStatesReady ) {
 fprintf ( stderr , "ucm error: the state table contains loops\n" ) ;
 exit ( U_INVALID_TABLE_FORMAT ) ;
 }
 sum = states -> stateOffsetSum [ 0 ] ;
 for ( state = 1 ;
 state < states -> countStates ;
 ++ state ) {
 if ( ( states -> stateFlags [ state ] & 0xf ) == MBCS_STATE_FLAG_DIRECT ) {
 int32_t sum2 = sum ;
 sum += states -> stateOffsetSum [ state ] ;
 for ( cell = 0 ;
 cell < 256 ;
 ++ cell ) {
 entry = states -> stateTable [ state ] [ cell ] ;
 if ( MBCS_ENTRY_IS_TRANSITION ( entry ) ) {
 states -> stateTable [ state ] [ cell ] = MBCS_ENTRY_TRANSITION_ADD_OFFSET ( entry , sum2 ) ;
 }
 }
 }
 }
 return states -> countToUCodeUnits = ( sum + 1 ) & ~ 1 ;
 }