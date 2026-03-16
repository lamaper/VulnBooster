static int load ( const char * append_string ) {
 TSIOBufferBlock blk ;
 char * p ;
 int64_t avail ;
 append_buffer = TSIOBufferCreate ( ) ;
 append_buffer_reader = TSIOBufferReaderAlloc ( append_buffer ) ;
 blk = TSIOBufferStart ( append_buffer ) ;
 p = TSIOBufferBlockWriteStart ( blk , & avail ) ;
 ink_strlcpy ( p , append_string , avail ) ;
 if ( append_string != nullptr ) {
 TSIOBufferProduce ( append_buffer , strlen ( append_string ) ) ;
 }
 append_buffer_length = TSIOBufferReaderAvail ( append_buffer_reader ) ;
 return 1 ;
 }