static int compress_bidder_free ( struct archive_read_filter_bidder * self ) {
 self -> data = NULL ;
 return ( ARCHIVE_OK ) ;
 }