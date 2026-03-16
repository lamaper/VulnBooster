const char * TSHttpServerStateNameLookup ( TSServerState state ) {
 return HttpDebugNames : : get_server_state_name ( static_cast < HttpTransact : : ServerState_t > ( state ) ) ;
 }