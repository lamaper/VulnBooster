static int script_contents_read ( struct mail_user * user ) {
 struct fts_parser_script_user * suser = SCRIPT_USER_CONTEXT ( user ) ;
 const char * path , * cmd , * line ;
 char * * args ;
 struct istream * input ;
 struct content * content ;
 bool eof_seen = FALSE ;
 int fd , ret = 0 ;
 fd = script_connect ( user , & path ) ;
 if ( fd == - 1 ) return - 1 ;
 cmd = t_strdup_printf ( SCRIPT_HANDSHAKE "\n" ) ;
 if ( write_full ( fd , cmd , strlen ( cmd ) ) < 0 ) {
 i_error ( "write(%s) failed: %m" , path ) ;
 i_close_fd ( & fd ) ;
 return - 1 ;
 }
 input = i_stream_create_fd_autoclose ( & fd , 1024 ) ;
 while ( ( line = i_stream_read_next_line ( input ) ) != NULL ) {
 args = p_strsplit_spaces ( user -> pool , line , " " ) ;
 if ( args [ 0 ] == NULL ) {
 eof_seen = TRUE ;
 break ;
 }
 if ( args [ 0 ] [ 0 ] == '\0' || args [ 1 ] == NULL ) {
 i_error ( "parser script sent invalid input: %s" , line ) ;
 continue ;
 }
 content = array_append_space ( & suser -> content ) ;
 content -> content_type = args [ 0 ] ;
 content -> extensions = ( const void * ) ( args + 1 ) ;
 }
 if ( input -> stream_errno != 0 ) {
 i_error ( "parser script read(%s) failed: %s" , path , i_stream_get_error ( input ) ) ;
 ret = - 1 ;
 }
 else if ( ! eof_seen ) {
 if ( input -> v_offset == 0 ) i_error ( "parser script didn't send any data" ) ;
 else i_error ( "parser script didn't send empty EOF line" ) ;
 }
 i_stream_destroy ( & input ) ;
 return ret ;
 }