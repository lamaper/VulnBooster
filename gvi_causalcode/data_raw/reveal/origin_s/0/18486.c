TSReturnCode TSHttpTxnClientProtocolStackGet ( TSHttpTxn txnp , int n , const char * * result , int * actual ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( n == 0 || result != nullptr ) ;
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 int count = 0 ;
 if ( sm && n > 0 ) {
 auto mem = static_cast < ts : : StringView * > ( alloca ( sizeof ( ts : : StringView ) * n ) ) ;
 count = sm -> populate_client_protocol ( mem , n ) ;
 for ( int i = 0 ;
 i < count ;
 ++ i ) result [ i ] = mem [ i ] . ptr ( ) ;
 }
 if ( actual ) {
 * actual = count ;
 }
 return TS_SUCCESS ;
 }