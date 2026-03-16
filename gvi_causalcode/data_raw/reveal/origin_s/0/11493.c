void TSHttpTxnReenable ( TSHttpTxn txnp , TSEvent event ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 EThread * eth = this_ethread ( ) ;
 if ( eth == nullptr || eth -> tt != REGULAR ) {
 eventProcessor . schedule_imm ( new TSHttpSMCallback ( sm , event ) , ET_NET ) ;
 }
 else {
 MUTEX_TRY_LOCK ( trylock , sm -> mutex , eth ) ;
 if ( ! trylock . is_locked ( ) ) {
 eventProcessor . schedule_imm ( new TSHttpSMCallback ( sm , event ) , ET_NET ) ;
 }
 else {
 sm -> state_api_callback ( ( int ) event , nullptr ) ;
 }
 }
 }