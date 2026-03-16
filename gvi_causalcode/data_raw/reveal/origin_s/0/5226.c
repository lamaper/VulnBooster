static void keyblock_cache_clear ( void ) {
 keyblock_cache . state = KEYBLOCK_CACHE_EMPTY ;
 xfree ( keyblock_cache . sigstatus ) ;
 keyblock_cache . sigstatus = NULL ;
 iobuf_close ( keyblock_cache . iobuf ) ;
 keyblock_cache . iobuf = NULL ;
 }