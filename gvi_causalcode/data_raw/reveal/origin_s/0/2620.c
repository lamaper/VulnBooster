TSVConn TSVConnCreate ( TSEventFunc event_funcp , TSMutex mutexp ) {
 if ( mutexp == nullptr ) {
 mutexp = ( TSMutex ) new_ProxyMutex ( ) ;
 }
 sdk_assert ( sdk_sanity_check_mutex ( mutexp ) == TS_SUCCESS ) ;
 INKVConnInternal * i = INKVConnAllocator . alloc ( ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) i ) == TS_SUCCESS ) ;
 i -> init ( event_funcp , mutexp ) ;
 return reinterpret_cast < TSVConn > ( i ) ;
 }