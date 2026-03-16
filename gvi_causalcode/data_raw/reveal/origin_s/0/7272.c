static void compactToUnicode2 ( UCMStates * states , uint16_t * * pUnicodeCodeUnits , _MBCSToUFallback * toUFallbacks , int32_t countToUFallbacks , UBool verbose ) {
 int32_t ( * oldStateTable ) [ 256 ] ;
 uint16_t count [ 256 ] ;
 uint16_t * oldUnicodeCodeUnits ;
 int32_t entry , offset , oldOffset , trailOffset , oldTrailOffset , savings , sum ;
 int32_t i , j , leadState , trailState , newState , fallback ;
 uint16_t unit ;
 if ( states -> outputType == MBCS_OUTPUT_2_SISO ) {
 leadState = 1 ;
 }
 else {
 leadState = 0 ;
 }
 uprv_memset ( count , 0 , sizeof ( count ) ) ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 entry = states -> stateTable [ leadState ] [ i ] ;
 if ( MBCS_ENTRY_IS_TRANSITION ( entry ) ) {
 ++ count [ MBCS_ENTRY_TRANSITION_STATE ( entry ) ] ;
 }
 }
 trailState = 0 ;
 for ( i = 1 ;
 i < states -> countStates ;
 ++ i ) {
 if ( count [ i ] > count [ trailState ] ) {
 trailState = i ;
 }
 }
 uprv_memset ( count , 0 , sizeof ( count ) ) ;
 savings = 0 ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 entry = states -> stateTable [ leadState ] [ i ] ;
 if ( MBCS_ENTRY_IS_TRANSITION ( entry ) && ( MBCS_ENTRY_TRANSITION_STATE ( entry ) ) == trailState ) {
 offset = MBCS_ENTRY_TRANSITION_OFFSET ( entry ) ;
 for ( j = 0 ;
 j < 256 ;
 ++ j ) {
 entry = states -> stateTable [ trailState ] [ j ] ;
 switch ( MBCS_ENTRY_FINAL_ACTION ( entry ) ) {
 case MBCS_STATE_VALID_16 : entry = offset + MBCS_ENTRY_FINAL_VALUE_16 ( entry ) ;
 if ( ( * pUnicodeCodeUnits ) [ entry ] == 0xfffe && ucm_findFallback ( toUFallbacks , countToUFallbacks , entry ) < 0 ) {
 ++ count [ i ] ;
 }
 else {
 j = 999 ;
 }
 break ;
 case MBCS_STATE_VALID_16_PAIR : entry = offset + MBCS_ENTRY_FINAL_VALUE_16 ( entry ) ;
 if ( ( * pUnicodeCodeUnits ) [ entry ] == 0xfffe ) {
 count [ i ] += 2 ;
 }
 else {
 j = 999 ;
 }
 break ;
 default : break ;
 }
 }
 if ( j == 256 ) {
 savings += count [ i ] ;
 }
 else {
 count [ i ] = 0 ;
 }
 }
 }
 savings = savings * 2 - 1024 ;
 if ( savings <= 0 ) {
 return ;
 }
 if ( verbose ) {
 printf ( "compacting toUnicode data saves %ld bytes\n" , ( long ) savings ) ;
 }
 if ( states -> countStates >= MBCS_MAX_STATE_COUNT ) {
 fprintf ( stderr , "cannot compact toUnicode because the maximum number of states is reached\n" ) ;
 return ;
 }
 oldStateTable = ( int32_t ( * ) [ 256 ] ) uprv_malloc ( states -> countStates * 1024 ) ;
 if ( oldStateTable == NULL ) {
 fprintf ( stderr , "cannot compact toUnicode: out of memory\n" ) ;
 return ;
 }
 uprv_memcpy ( oldStateTable , states -> stateTable , states -> countStates * 1024 ) ;
 newState = states -> countStates ++ ;
 states -> stateFlags [ newState ] = 0 ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 entry = states -> stateTable [ trailState ] [ i ] ;
 switch ( MBCS_ENTRY_FINAL_ACTION ( entry ) ) {
 case MBCS_STATE_VALID_16 : case MBCS_STATE_VALID_16_PAIR : states -> stateTable [ newState ] [ i ] = MBCS_ENTRY_FINAL_SET_ACTION_VALUE ( entry , MBCS_STATE_UNASSIGNED , 0xfffe ) ;
 break ;
 default : states -> stateTable [ newState ] [ i ] = entry ;
 break ;
 }
 }
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 if ( count [ i ] > 0 ) {
 states -> stateTable [ leadState ] [ i ] = MBCS_ENTRY_SET_STATE ( states -> stateTable [ leadState ] [ i ] , newState ) ;
 }
 }
 for ( i = 0 ;
 i < states -> countStates ;
 ++ i ) {
 states -> stateFlags [ i ] &= ~ MBCS_STATE_FLAG_READY ;
 }
 sum = sumUpStates ( states ) ;
 oldUnicodeCodeUnits = * pUnicodeCodeUnits ;
 if ( sum == 0 ) {
 * pUnicodeCodeUnits = NULL ;
 if ( oldUnicodeCodeUnits != NULL ) {
 uprv_free ( oldUnicodeCodeUnits ) ;
 }
 uprv_free ( oldStateTable ) ;
 return ;
 }
 * pUnicodeCodeUnits = ( uint16_t * ) uprv_malloc ( sum * sizeof ( uint16_t ) ) ;
 if ( * pUnicodeCodeUnits == NULL ) {
 fprintf ( stderr , "cannot compact toUnicode: out of memory allocating %ld 16-bit code units\n" , ( long ) sum ) ;
 * pUnicodeCodeUnits = oldUnicodeCodeUnits ;
 -- states -> countStates ;
 uprv_memcpy ( states -> stateTable , oldStateTable , states -> countStates * 1024 ) ;
 uprv_free ( oldStateTable ) ;
 return ;
 }
 for ( i = 0 ;
 i < sum ;
 ++ i ) {
 ( * pUnicodeCodeUnits ) [ i ] = 0xfffe ;
 }
 for ( leadState = 0 ;
 leadState < states -> countStates ;
 ++ leadState ) {
 if ( ( states -> stateFlags [ leadState ] & 0xf ) == MBCS_STATE_FLAG_DIRECT ) {
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 entry = states -> stateTable [ leadState ] [ i ] ;
 if ( MBCS_ENTRY_IS_TRANSITION ( entry ) ) {
 trailState = ( uint8_t ) MBCS_ENTRY_TRANSITION_STATE ( entry ) ;
 if ( trailState != newState ) {
 trailOffset = MBCS_ENTRY_TRANSITION_OFFSET ( entry ) ;
 oldTrailOffset = MBCS_ENTRY_TRANSITION_OFFSET ( oldStateTable [ leadState ] [ i ] ) ;
 for ( j = 0 ;
 j < 256 ;
 ++ j ) {
 entry = states -> stateTable [ trailState ] [ j ] ;
 switch ( MBCS_ENTRY_FINAL_ACTION ( entry ) ) {
 case MBCS_STATE_VALID_16 : offset = trailOffset + MBCS_ENTRY_FINAL_VALUE_16 ( entry ) ;
 oldOffset = oldTrailOffset + MBCS_ENTRY_FINAL_VALUE_16 ( oldStateTable [ trailState ] [ j ] ) ;
 unit = ( * pUnicodeCodeUnits ) [ offset ] = oldUnicodeCodeUnits [ oldOffset ] ;
 if ( unit == 0xfffe && ( fallback = ucm_findFallback ( toUFallbacks , countToUFallbacks , oldOffset ) ) >= 0 ) {
 toUFallbacks [ fallback ] . offset = 0x80000000 | offset ;
 }
 break ;
 case MBCS_STATE_VALID_16_PAIR : offset = trailOffset + MBCS_ENTRY_FINAL_VALUE_16 ( entry ) ;
 oldOffset = oldTrailOffset + MBCS_ENTRY_FINAL_VALUE_16 ( oldStateTable [ trailState ] [ j ] ) ;
 ( * pUnicodeCodeUnits ) [ offset ++ ] = oldUnicodeCodeUnits [ oldOffset ++ ] ;
 ( * pUnicodeCodeUnits ) [ offset ] = oldUnicodeCodeUnits [ oldOffset ] ;
 break ;
 default : break ;
 }
 }
 }
 }
 }
 }
 }
 for ( i = 0 ;
 i < countToUFallbacks ;
 ++ i ) {
 toUFallbacks [ i ] . offset &= 0x7fffffff ;
 }
 uprv_free ( oldUnicodeCodeUnits ) ;
 uprv_free ( oldStateTable ) ;
 }