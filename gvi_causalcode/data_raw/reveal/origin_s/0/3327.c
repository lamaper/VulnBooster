static int read_and_execute ( bool interactive ) {

 String buffer ;

 char in_string = 0 ;
 ulong line_number = 0 ;
 bool ml_comment = 0 ;
 COMMANDS * com ;
 ulong line_length = 0 ;
 status . exit_status = 1 ;
 real_binary_mode = ! interactive && opt_binary_mode ;
 while ( ! aborted ) {
 if ( ! interactive ) {
 line = batch_readline ( status . line_buff , real_binary_mode ) ;
 if ( line ) {
 line_length = status . line_buff -> read_length ;
 if ( ! real_binary_mode && strlen ( line ) != line_length ) {
 status . exit_status = 1 ;
 String msg ;
 msg . append ( "ASCII '\\0' appeared in the statement, but this is not " "allowed unless option --binary-mode is enabled and mysql is " "run in non-interactive mode. Set --binary-mode to 1 if ASCII " "'\\0' is expected. Query: '" ) ;
 msg . append ( glob_buffer ) ;
 msg . append ( line ) ;
 msg . append ( "'." ) ;
 put_info ( msg . c_ptr ( ) , INFO_ERROR ) ;
 break ;
 }
 if ( ! line_number && ( uchar ) line [ 0 ] == 0xEF && ( uchar ) line [ 1 ] == 0xBB && ( uchar ) line [ 2 ] == 0xBF ) {
 line += 3 ;
 line_length -= 3 ;
 }
 }
 line_number ++ ;
 if ( ! glob_buffer . length ( ) ) status . query_start_line = line_number ;
 }
 else {
 char * prompt = ( char * ) ( ml_comment ? " /*> " : glob_buffer . is_empty ( ) ? construct_prompt ( ) : ! in_string ? " -> " : in_string == '\'' ? " '> " : ( in_string == '`' ? " `> " : " \"> " ) ) ;
 if ( opt_outfile && glob_buffer . is_empty ( ) ) fflush ( OUTFILE ) ;

 if ( ! tmpbuf . is_alloced ( ) ) tmpbuf . alloc ( 65535 ) ;
 tmpbuf . length ( 0 ) ;
 buffer . length ( 0 ) ;
 size_t clen ;
 do {
 line = my_cgets ( ( char * ) tmpbuf . ptr ( ) , tmpbuf . alloced_length ( ) - 1 , & clen ) ;
 buffer . append ( line , clen ) ;
 }
 while ( tmpbuf . alloced_length ( ) <= clen ) ;
 if ( line ) line = buffer . c_ptr ( ) ;

 if ( line ) free ( line ) ;
 line = readline ( prompt ) ;

 line_length = line ? strlen ( line ) : 0 ;
 }
 if ( ! line ) {
 if ( status . line_buff && status . line_buff -> error ) status . exit_status = 1 ;
 else status . exit_status = 0 ;
 break ;
 }
 if ( ( named_cmds || glob_buffer . is_empty ( ) ) && ! ml_comment && ! in_string && ( com = find_command ( line ) ) ) {
 if ( ( * com -> func ) ( & glob_buffer , line ) > 0 ) break ;
 if ( glob_buffer . is_empty ( ) ) in_string = 0 ;


 }
 if ( add_line ( glob_buffer , line , line_length , & in_string , & ml_comment , status . line_buff ? status . line_buff -> truncated : 0 ) ) break ;
 }
 if ( ! interactive && ! status . exit_status ) {
 remove_cntrl ( glob_buffer ) ;
 if ( ! glob_buffer . is_empty ( ) ) {
 status . exit_status = 1 ;
 if ( com_go ( & glob_buffer , line ) <= 0 ) status . exit_status = 0 ;
 }
 }

 tmpbuf . free ( ) ;


 return status . exit_status ;
 }