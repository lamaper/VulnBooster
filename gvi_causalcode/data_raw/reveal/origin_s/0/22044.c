const char * TSHttpHookNameLookup ( TSHttpHookID hook ) {
 return HttpDebugNames : : get_api_hook_name ( static_cast < TSHttpHookID > ( hook ) ) ;
 }