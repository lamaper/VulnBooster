void TSHttpSsnReenable ( TSHttpSsn ssnp , TSEvent event ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 EThread * eth = this_ethread ( ) ;
 if ( eth -> tt != REGULAR ) {
 eventProcessor . schedule_imm ( new TSHttpSsnCallback ( cs , event ) , ET_NET ) ;
 }
 else {
 MUTEX_TRY_LOCK ( trylock , cs -> mutex , eth ) ;
 if ( ! trylock . is_locked ( ) ) {
 eventProcessor . schedule_imm ( new TSHttpSsnCallback ( cs , event ) , ET_NET ) ;
 }
 else {
 cs -> handleEvent ( ( int ) event , nullptr ) ;
 }
 }
 }