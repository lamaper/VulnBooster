void server_free_command ( struct iovec * * command ) {
 struct iovec * * arg ;
 for ( arg = command ;
 * arg != NULL ;
 arg ++ ) {
 if ( ( * arg ) -> iov_base != NULL ) free ( ( * arg ) -> iov_base ) ;
 free ( * arg ) ;
 }
 free ( command ) ;
 }