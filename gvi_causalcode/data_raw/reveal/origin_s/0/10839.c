TSAction TSNetAccept ( TSCont contp , int port , int domain , int accept_threads ) {
 NetProcessor : : AcceptOptions opt ;
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( port > 0 ) ;
 sdk_assert ( accept_threads >= - 1 ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 opt = make_net_accept_options ( nullptr , accept_threads ) ;
 opt . ip_family = domain == AF_INET6 ? AF_INET6 : AF_INET ;
 opt . local_port = port ;
 opt . frequent_accept = false ;
 INKContInternal * i = reinterpret_cast < INKContInternal * > ( contp ) ;
 return reinterpret_cast < TSAction > ( netProcessor . accept ( i , opt ) ) ;
 }