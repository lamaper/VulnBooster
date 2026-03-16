static int archive_read_format_ar_read_data ( struct archive_read * a , const void * * buff , size_t * size , int64_t * offset ) {
 ssize_t bytes_read ;
 struct ar * ar ;
 ar = ( struct ar * ) ( a -> format -> data ) ;
 if ( ar -> entry_bytes_unconsumed ) {
 __archive_read_consume ( a , ar -> entry_bytes_unconsumed ) ;
 ar -> entry_bytes_unconsumed = 0 ;
 }
 if ( ar -> entry_bytes_remaining > 0 ) {
 * buff = __archive_read_ahead ( a , 1 , & bytes_read ) ;
 if ( bytes_read == 0 ) {
 archive_set_error ( & a -> archive , ARCHIVE_ERRNO_MISC , "Truncated ar archive" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 if ( bytes_read < 0 ) return ( ARCHIVE_FATAL ) ;
 if ( bytes_read > ar -> entry_bytes_remaining ) bytes_read = ( ssize_t ) ar -> entry_bytes_remaining ;
 * size = bytes_read ;
 ar -> entry_bytes_unconsumed = bytes_read ;
 * offset = ar -> entry_offset ;
 ar -> entry_offset += bytes_read ;
 ar -> entry_bytes_remaining -= bytes_read ;
 return ( ARCHIVE_OK ) ;
 }
 else {
 int64_t skipped = __archive_read_consume ( a , ar -> entry_padding ) ;
 if ( skipped >= 0 ) {
 ar -> entry_padding -= skipped ;
 }
 if ( ar -> entry_padding ) {
 if ( skipped >= 0 ) {
 archive_set_error ( & a -> archive , ARCHIVE_ERRNO_MISC , "Truncated ar archive- failed consuming padding" ) ;
 }
 return ( ARCHIVE_FATAL ) ;
 }
 * buff = NULL ;
 * size = 0 ;
 * offset = ar -> entry_offset ;
 return ( ARCHIVE_EOF ) ;
 }
 }