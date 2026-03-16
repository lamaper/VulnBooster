static int archive_read_format_ar_read_header ( struct archive_read * a , struct archive_entry * entry ) {
 struct ar * ar = ( struct ar * ) ( a -> format -> data ) ;
 size_t unconsumed ;
 const void * header_data ;
 int ret ;
 if ( ! ar -> read_global_header ) {
 __archive_read_consume ( a , 8 ) ;
 ar -> read_global_header = 1 ;
 a -> archive . archive_format = ARCHIVE_FORMAT_AR ;
 }
 if ( ( header_data = __archive_read_ahead ( a , 60 , NULL ) ) == NULL ) return ( ARCHIVE_EOF ) ;
 unconsumed = 60 ;
 ret = _ar_read_header ( a , entry , ar , ( const char * ) header_data , & unconsumed ) ;
 if ( unconsumed ) __archive_read_consume ( a , unconsumed ) ;
 return ret ;
 }