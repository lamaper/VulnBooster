TSReturnCode sdk_sanity_check_lifecycle_hook_id ( TSLifecycleHookID id ) {
 return LifecycleAPIHooks : : is_valid ( id ) ? TS_SUCCESS : TS_ERROR ;
 }