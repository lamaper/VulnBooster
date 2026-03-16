static int mszipd_flush_window ( struct mszipd_stream * zip , unsigned int data_flushed ) {
 zip -> bytes_output += data_flushed ;
 if ( zip -> bytes_output > MSZIP_FRAME_SIZE ) {
 D ( ( "overflow: %u bytes flushed, total is now %u" , data_flushed , zip -> bytes_output ) ) return 1 ;
 }
 return 0 ;
 }