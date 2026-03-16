TSAction TSHttpSchedule ( TSCont contp , TSHttpTxn txnp , ink_hrtime timeout ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 INKContInternal * i = ( INKContInternal * ) contp ;
 if ( ink_atomic_increment ( ( int * ) & i -> m_event_count , 1 ) < 0 ) {
 ink_assert ( ! "not reached" ) ;
 }
 TSAction action ;
 Continuation * cont = ( Continuation * ) contp ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> set_http_schedule ( cont ) ;
 if ( timeout == 0 ) {
 action = reinterpret_cast < TSAction > ( eventProcessor . schedule_imm ( sm , ET_NET ) ) ;
 }
 else {
 action = reinterpret_cast < TSAction > ( eventProcessor . schedule_in ( sm , HRTIME_MSECONDS ( timeout ) , ET_NET ) ) ;
 }
 action = ( TSAction ) ( ( uintptr_t ) action | 0x1 ) ;
 return action ;
 }