TSCont TSContCreate ( TSEventFunc funcp , TSMutex mutexp ) {
 if ( mutexp != nullptr ) {
 sdk_assert ( sdk_sanity_check_mutex ( mutexp ) == TS_SUCCESS ) ;
 }
 INKContInternal * i = INKContAllocator . alloc ( ) ;
 i -> init ( funcp , mutexp ) ;
 return ( TSCont ) i ;
 }