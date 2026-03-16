void TSHttpTxnHookAdd ( TSHttpTxn txnp , TSHttpHookID id , TSCont contp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_hook_id ( id ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 APIHook * hook = sm -> txn_hook_get ( id ) ;
 while ( hook != nullptr ) {
 if ( hook -> m_cont == ( INKContInternal * ) contp ) {
 return ;
 }
 hook = hook -> m_link . next ;
 }
 sm -> txn_hook_append ( id , ( INKContInternal * ) contp ) ;
 }