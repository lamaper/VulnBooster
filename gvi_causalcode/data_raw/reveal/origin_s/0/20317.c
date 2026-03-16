static int _ar_read_header ( struct archive_read * a , struct archive_entry * entry , struct ar * ar , const char * h , size_t * unconsumed ) {
 char filename [ AR_name_size + 1 ] ;
 uint64_t number ;
 size_t bsd_name_length , entry_size ;
 char * p , * st ;
 const void * b ;
 int r ;
 if ( strncmp ( h + AR_fmag_offset , "`\n" , 2 ) != 0 ) {
 archive_set_error ( & a -> archive , EINVAL , "Incorrect file header signature" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 strncpy ( filename , h + AR_name_offset , AR_name_size ) ;
 filename [ AR_name_size ] = '\0' ;
 if ( a -> archive . archive_format == ARCHIVE_FORMAT_AR ) {
 if ( strncmp ( filename , "#1/" , 3 ) == 0 ) a -> archive . archive_format = ARCHIVE_FORMAT_AR_BSD ;
 else if ( strchr ( filename , '/' ) != NULL ) a -> archive . archive_format = ARCHIVE_FORMAT_AR_GNU ;
 else if ( strncmp ( filename , "__.SYMDEF" , 9 ) == 0 ) a -> archive . archive_format = ARCHIVE_FORMAT_AR_BSD ;
 }
 if ( a -> archive . archive_format == ARCHIVE_FORMAT_AR_GNU ) a -> archive . archive_format_name = "ar (GNU/SVR4)" ;
 else if ( a -> archive . archive_format == ARCHIVE_FORMAT_AR_BSD ) a -> archive . archive_format_name = "ar (BSD)" ;
 else a -> archive . archive_format_name = "ar" ;
 p = filename + AR_name_size - 1 ;
 while ( p >= filename && * p == ' ' ) {
 * p = '\0' ;
 p -- ;
 }
 if ( filename [ 0 ] != '/' && p > filename && * p == '/' ) {
 * p = '\0' ;
 }
 if ( p < filename ) {
 archive_set_error ( & a -> archive , ARCHIVE_ERRNO_MISC , "Found entry with empty filename" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 if ( strcmp ( filename , "//" ) == 0 ) {
 ar_parse_common_header ( ar , entry , h ) ;
 archive_entry_copy_pathname ( entry , filename ) ;
 archive_entry_set_filetype ( entry , AE_IFREG ) ;
 number = ar_atol10 ( h + AR_size_offset , AR_size_size ) ;
 if ( number > SIZE_MAX ) {
 archive_set_error ( & a -> archive , ARCHIVE_ERRNO_MISC , "Filename table too large" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 entry_size = ( size_t ) number ;
 if ( entry_size == 0 ) {
 archive_set_error ( & a -> archive , EINVAL , "Invalid string table" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 if ( ar -> strtab != NULL ) {
 archive_set_error ( & a -> archive , EINVAL , "More than one string tables exist" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 st = malloc ( entry_size ) ;
 if ( st == NULL ) {
 archive_set_error ( & a -> archive , ENOMEM , "Can't allocate filename table buffer" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 ar -> strtab = st ;
 ar -> strtab_size = entry_size ;
 if ( * unconsumed ) {
 __archive_read_consume ( a , * unconsumed ) ;
 * unconsumed = 0 ;
 }
 if ( ( b = __archive_read_ahead ( a , entry_size , NULL ) ) == NULL ) return ( ARCHIVE_FATAL ) ;
 memcpy ( st , b , entry_size ) ;
 __archive_read_consume ( a , entry_size ) ;
 ar -> entry_bytes_remaining = 0 ;
 archive_entry_set_size ( entry , ar -> entry_bytes_remaining ) ;
 return ( ar_parse_gnu_filename_table ( a ) ) ;
 }
 if ( filename [ 0 ] == '/' && filename [ 1 ] >= '0' && filename [ 1 ] <= '9' ) {
 number = ar_atol10 ( h + AR_name_offset + 1 , AR_name_size - 1 ) ;
 if ( ar -> strtab == NULL || number > ar -> strtab_size ) {
 archive_set_error ( & a -> archive , EINVAL , "Can't find long filename for GNU/SVR4 archive entry" ) ;
 archive_entry_copy_pathname ( entry , filename ) ;
 ar_parse_common_header ( ar , entry , h ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 archive_entry_copy_pathname ( entry , & ar -> strtab [ ( size_t ) number ] ) ;
 return ( ar_parse_common_header ( ar , entry , h ) ) ;
 }
 if ( strncmp ( filename , "#1/" , 3 ) == 0 ) {
 ar_parse_common_header ( ar , entry , h ) ;
 number = ar_atol10 ( h + AR_name_offset + 3 , AR_name_size - 3 ) ;
 bsd_name_length = ( size_t ) number ;
 if ( number > ( uint64_t ) ( bsd_name_length + 1 ) || ( int64_t ) bsd_name_length > ar -> entry_bytes_remaining ) {
 archive_set_error ( & a -> archive , ARCHIVE_ERRNO_MISC , "Bad input file size" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 ar -> entry_bytes_remaining -= bsd_name_length ;
 archive_entry_set_size ( entry , ar -> entry_bytes_remaining ) ;
 if ( * unconsumed ) {
 __archive_read_consume ( a , * unconsumed ) ;
 * unconsumed = 0 ;
 }
 if ( ( b = __archive_read_ahead ( a , bsd_name_length , NULL ) ) == NULL ) {
 archive_set_error ( & a -> archive , ARCHIVE_ERRNO_MISC , "Truncated input file" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 p = ( char * ) malloc ( bsd_name_length + 1 ) ;
 if ( p == NULL ) {
 archive_set_error ( & a -> archive , ENOMEM , "Can't allocate fname buffer" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 strncpy ( p , b , bsd_name_length ) ;
 p [ bsd_name_length ] = '\0' ;
 __archive_read_consume ( a , bsd_name_length ) ;
 archive_entry_copy_pathname ( entry , p ) ;
 free ( p ) ;
 return ( ARCHIVE_OK ) ;
 }
 if ( strcmp ( filename , "/" ) == 0 ) {
 archive_entry_copy_pathname ( entry , "/" ) ;
 r = ar_parse_common_header ( ar , entry , h ) ;
 archive_entry_set_filetype ( entry , AE_IFREG ) ;
 return ( r ) ;
 }
 if ( strcmp ( filename , "__.SYMDEF" ) == 0 ) {
 archive_entry_copy_pathname ( entry , filename ) ;
 return ( ar_parse_common_header ( ar , entry , h ) ) ;
 }
 archive_entry_copy_pathname ( entry , filename ) ;
 return ( ar_parse_common_header ( ar , entry , h ) ) ;
 }