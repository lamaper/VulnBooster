void TSLifecycleHookAdd ( TSLifecycleHookID id , TSCont contp ) {
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_lifecycle_hook_id ( id ) == TS_SUCCESS ) ;
 lifecycle_hooks -> append ( id , ( INKContInternal * ) contp ) ;
 }