static inline realpath_cache_bucket * realpath_cache_find ( const char * path , int path_len , time_t t TSRMLS_DC ) {



 realpath_cache_bucket * * bucket = & CWDG ( realpath_cache ) [ n ] ;
 while ( * bucket != NULL ) {
 if ( CWDG ( realpath_cache_ttl ) && ( * bucket ) -> expires < t ) {
 realpath_cache_bucket * r = * bucket ;
 * bucket = ( * bucket ) -> next ;
 if ( r -> path == r -> realpath ) {
 CWDG ( realpath_cache_size ) -= sizeof ( realpath_cache_bucket ) + r -> path_len + 1 ;
 }
 else {
 CWDG ( realpath_cache_size ) -= sizeof ( realpath_cache_bucket ) + r -> path_len + 1 + r -> realpath_len + 1 ;
 }
 free ( r ) ;
 }
 else if ( key == ( * bucket ) -> key && path_len == ( * bucket ) -> path_len && memcmp ( path , ( * bucket ) -> path , path_len ) == 0 ) {
 return * bucket ;
 }
 else {
 bucket = & ( * bucket ) -> next ;
 }
 }
 return NULL ;
 }