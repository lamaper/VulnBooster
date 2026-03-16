TEST_F ( FullscreenControllerStateUnitTest , DISABLED_DebugLogStateTables ) {
 std : : ostringstream output ;
 output << "\n\nTransition Table:" ;
 output << GetTransitionTableAsString ( ) ;
 output << "\n\nInitial transitions:" ;
 output << GetStateTransitionsAsString ( ) ;
 for ( int state1_int = 0 ;
 state1_int < NUM_STATES ;
 ++ state1_int ) {
 State state1 = static_cast < State > ( state1_int ) ;
 for ( int state2_int = 0 ;
 state2_int < NUM_STATES ;
 ++ state2_int ) {
 State state2 = static_cast < State > ( state2_int ) ;
 if ( ShouldSkipStateAndEventPair ( state1 , EVENT_INVALID ) || ShouldSkipStateAndEventPair ( state2 , EVENT_INVALID ) ) continue ;
 if ( NextTransitionInShortestPath ( state1 , state2 , NUM_STATES ) . state == STATE_INVALID ) {
 LOG ( ERROR ) << "Should be skipping state transitions for: " << GetStateString ( state1 ) << " " << GetStateString ( state2 ) ;
 }
 }
 }
 output << "\n\nAll transitions:" ;
 output << GetStateTransitionsAsString ( ) ;
 LOG ( INFO ) << output . str ( ) ;
 }