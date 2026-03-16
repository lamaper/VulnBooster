static void fts_parser_script_more ( struct fts_parser * _parser , struct message_block * block ) {
 struct script_fts_parser * parser = ( struct script_fts_parser * ) _parser ;
 ssize_t ret ;
 if ( block -> size > 0 ) {
 if ( ! parser -> failed && write_full ( parser -> fd , block -> data , block -> size ) < 0 ) {
 i_error ( "write(%s) failed: %m" , parser -> path ) ;
 parser -> failed = TRUE ;
 }
 block -> size = 0 ;
 }
 else {
 if ( ! parser -> shutdown ) {
 if ( shutdown ( parser -> fd , SHUT_WR ) < 0 ) i_error ( "shutdown(%s) failed: %m" , parser -> path ) ;
 parser -> shutdown = TRUE ;
 }
 ret = read ( parser -> fd , parser -> outbuf , sizeof ( parser -> outbuf ) ) ;
 if ( ret < 0 ) i_error ( "read(%s) failed: %m" , parser -> path ) ;
 else {
 block -> data = parser -> outbuf ;
 block -> size = ret ;
 }
 }
 }