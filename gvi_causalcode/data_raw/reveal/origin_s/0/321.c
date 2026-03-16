TSReturnCode TSHttpTxnMilestoneGet ( TSHttpTxn txnp , TSMilestonesType milestone , ink_hrtime * time ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( time ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 TSReturnCode ret = TS_SUCCESS ;
 if ( ( milestone < TS_MILESTONE_UA_BEGIN ) || ( milestone >= TS_MILESTONE_LAST_ENTRY ) ) {
 * time = - 1 ;
 ret = TS_ERROR ;
 }
 else {
 * time = sm -> milestones [ milestone ] ;
 }
 return ret ;
 }