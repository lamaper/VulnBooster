void keyring_release ( KEYRING_HANDLE hd ) {
 if ( ! hd ) return ;
 assert ( active_handles > 0 ) ;
 active_handles -- ;
 xfree ( hd -> word_match . name ) ;
 xfree ( hd -> word_match . pattern ) ;
 iobuf_close ( hd -> current . iobuf ) ;
 xfree ( hd ) ;
 }