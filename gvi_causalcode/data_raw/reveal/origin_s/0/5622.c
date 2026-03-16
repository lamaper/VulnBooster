static int compress_filter_close ( struct archive_read_filter * self ) {
 struct private_data * state = ( struct private_data * ) self -> data ;
 free ( state -> out_block ) ;
 free ( state ) ;
 return ( ARCHIVE_OK ) ;
 }