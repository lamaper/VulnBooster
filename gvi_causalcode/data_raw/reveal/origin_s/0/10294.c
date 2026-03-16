const char * TSHttpEventNameLookup ( TSEvent event ) {
 return HttpDebugNames : : get_event_name ( static_cast < int > ( event ) ) ;
 }