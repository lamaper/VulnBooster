TSReturnCode sdk_sanity_check_hook_id ( TSHttpHookID id ) {
 return HttpAPIHooks : : is_valid ( id ) ? TS_SUCCESS : TS_ERROR ;
 }