static int archive_read_format_ar_skip ( struct archive_read * a ) {
 int64_t bytes_skipped ;
 struct ar * ar ;
 ar = ( struct ar * ) ( a -> format -> data ) ;
 bytes_skipped = __archive_read_consume ( a , ar -> entry_bytes_remaining + ar -> entry_padding + ar -> entry_bytes_unconsumed ) ;
 if ( bytes_skipped < 0 ) return ( ARCHIVE_FATAL ) ;
 ar -> entry_bytes_remaining = 0 ;
 ar -> entry_bytes_unconsumed = 0 ;
 ar -> entry_padding = 0 ;
 return ( ARCHIVE_OK ) ;
 }