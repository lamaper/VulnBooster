TSReturnCode TSHttpTxnHookRegisteredFor ( TSHttpTxn txnp , TSHttpHookID id , TSEventFunc funcp ) {
 HttpSM * sm = ( HttpSM * ) txnp ;
 APIHook * hook = sm -> txn_hook_get ( id ) ;
 while ( hook != nullptr ) {
 if ( hook -> m_cont && hook -> m_cont -> m_event_func == funcp ) {
 return TS_SUCCESS ;
 }
 hook = hook -> m_link . next ;
 }
 return TS_ERROR ;
 }