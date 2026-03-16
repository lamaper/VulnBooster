void send_protected_args ( int fd , char * args [ ] ) {
 int i ;

 xbuf outbuf , inbuf ;
 if ( convert ) alloc_xbuf ( & outbuf , 1024 ) ;

 args [ i ] ;
 i ++ ) {
 }
 args [ i ] = "rsync" ;
 if ( DEBUG_GTE ( CMD , 1 ) ) print_child_argv ( "protected args:" , args + i + 1 ) ;
 do {
 if ( ! args [ i ] [ 0 ] ) write_buf ( fd , "." , 2 ) ;

 INIT_XBUF_STRLEN ( inbuf , args [ i ] ) ;
 iconvbufs ( ic_send , & inbuf , & outbuf , ICB_EXPAND_OUT | ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE | ICB_INIT ) ;
 outbuf . buf [ outbuf . len ] = '\0' ;
 write_buf ( fd , outbuf . buf , outbuf . len + 1 ) ;
 outbuf . len = 0 ;
 }

 }
 while ( args [ ++ i ] ) ;
 write_byte ( fd , 0 ) ;

