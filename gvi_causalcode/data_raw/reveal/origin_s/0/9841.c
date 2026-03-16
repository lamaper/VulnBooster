inline static HTTPHdr * find_appropriate_cached_resp ( HttpTransact : : State * s ) {
 HTTPHdr * c_resp = nullptr ;
 if ( s -> cache_info . object_store . valid ( ) ) {
 c_resp = s -> cache_info . object_store . response_get ( ) ;
 if ( c_resp != nullptr && c_resp -> valid ( ) ) {
 return c_resp ;
 }
 }
 ink_assert ( s -> cache_info . object_read != nullptr ) ;
 return s -> cache_info . object_read -> response_get ( ) ;
 }