static struct fts_parser * fts_parser_script_try_init ( struct mail_user * user , const char * content_type , const char * content_disposition ) {
 struct script_fts_parser * parser ;
 const char * filename , * path , * cmd ;
 int fd ;
 parse_content_disposition ( content_disposition , & filename ) ;
 if ( script_support_content ( user , & content_type , filename ) <= 0 ) return NULL ;
 fd = script_connect ( user , & path ) ;
 if ( fd == - 1 ) return NULL ;
 cmd = t_strdup_printf ( SCRIPT_HANDSHAKE "%s\n\n" , content_type ) ;
 if ( write_full ( fd , cmd , strlen ( cmd ) ) < 0 ) {
 i_error ( "write(%s) failed: %m" , path ) ;
 i_close_fd ( & fd ) ;
 return NULL ;
 }
 parser = i_new ( struct script_fts_parser , 1 ) ;
 parser -> parser . v = fts_parser_script ;
 parser -> path = i_strdup ( path ) ;
 parser -> fd = fd ;
 return & parser -> parser ;
 }