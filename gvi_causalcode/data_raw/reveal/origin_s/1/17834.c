static int compress_bidder_bid ( struct archive_read_filter_bidder * self , struct archive_read_filter * filter ) {
 const unsigned char * buffer ;
 ssize_t avail ;
 int bits_checked ;
 ( void ) self ;
 buffer = __archive_read_filter_ahead ( filter , 2 , & avail ) ;
 if ( buffer == NULL ) return ( 0 ) ;
 bits_checked = 0 ;
 if ( buffer [ 0 ] != 0x1F || buffer [ 1 ] != 0x9D ) return ( 0 ) ;
 bits_checked += 16 ;
 return ( bits_checked ) ;
 }