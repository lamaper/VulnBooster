static bool script_support_content ( struct mail_user * user , const char * * content_type , const char * filename ) {
 struct fts_parser_script_user * suser = SCRIPT_USER_CONTEXT ( user ) ;
 const struct content * content ;
 const char * extension ;
 if ( suser == NULL ) {
 suser = p_new ( user -> pool , struct fts_parser_script_user , 1 ) ;
 p_array_init ( & suser -> content , user -> pool , 32 ) ;
 MODULE_CONTEXT_SET ( user , fts_parser_script_user_module , suser ) ;
 }
 if ( array_count ( & suser -> content ) == 0 ) {
 if ( script_contents_read ( user ) < 0 ) return FALSE ;
 }
 if ( strcmp ( * content_type , "application/octet-stream" ) == 0 ) {
 if ( filename == NULL ) return FALSE ;
 extension = strrchr ( filename , '.' ) ;
 if ( extension == NULL ) return FALSE ;
 extension = filename + 1 ;
 array_foreach ( & suser -> content , content ) {
 if ( content -> extensions != NULL && str_array_icase_find ( content -> extensions , extension ) ) {
 * content_type = content -> content_type ;
 return TRUE ;
 }
 }
 }
 else {
 array_foreach ( & suser -> content , content ) {
 if ( strcmp ( content -> content_type , * content_type ) == 0 ) return TRUE ;
 }
 }
 return FALSE ;
 }