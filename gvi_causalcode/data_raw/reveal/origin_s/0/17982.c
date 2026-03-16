static void main_get_appheader_params ( main_file * file , char * * parsed , int output , const char * type , main_file * other ) {
 if ( file -> filename == NULL && ! ( output && option_stdout ) && strcmp ( parsed [ 0 ] , "-" ) != 0 ) {
 file -> filename = parsed [ 0 ] ;
 if ( other -> filename != NULL ) {
 const char * last_slash = strrchr ( other -> filename , '/' ) ;
 if ( last_slash != NULL ) {
 usize_t dlen = ( usize_t ) ( last_slash - other -> filename ) ;
 XD3_ASSERT ( file -> filename_copy == NULL ) ;
 file -> filename_copy = ( char * ) main_malloc ( dlen + 2 + ( usize_t ) strlen ( file -> filename ) ) ;
 strncpy ( file -> filename_copy , other -> filename , dlen ) ;
 file -> filename_copy [ dlen ] = '/' ;
 strcpy ( file -> filename_copy + dlen + 1 , parsed [ 0 ] ) ;
 file -> filename = file -> filename_copy ;
 }
 }
 if ( ! option_quiet ) {
 XPR ( NT "using default %s filename: %s\n" , type , file -> filename ) ;
 }
 }
 if ( file -> compressor == NULL && * parsed [ 1 ] != 0 ) {
 file -> flags |= RD_DECOMPSET ;
 file -> compressor = main_get_compressor ( parsed [ 1 ] ) ;
 }
 }