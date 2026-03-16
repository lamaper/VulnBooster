static bool fts_build_body_begin ( struct fts_mail_build_context * ctx , struct message_part * part , bool * binary_body_r ) {
 struct mail_storage * storage ;
 const char * content_type ;
 struct fts_backend_build_key key ;
 i_assert ( ctx -> body_parser == NULL ) ;
 * binary_body_r = FALSE ;
 i_zero ( & key ) ;
 key . uid = ctx -> mail -> uid ;
 key . part = part ;
 content_type = ctx -> content_type != NULL ? ctx -> content_type : "text/plain" ;
 if ( strncmp ( content_type , "multipart/" , 10 ) == 0 ) {
 return FALSE ;
 }
 storage = mailbox_get_storage ( ctx -> mail -> box ) ;
 if ( fts_parser_init ( mail_storage_get_user ( storage ) , content_type , ctx -> content_disposition , & ctx -> body_parser ) ) {
 * binary_body_r = TRUE ;
 key . type = FTS_BACKEND_BUILD_KEY_BODY_PART ;
 }
 else if ( strncmp ( content_type , "text/" , 5 ) == 0 || strncmp ( content_type , "message/" , 8 ) == 0 ) {
 key . type = FTS_BACKEND_BUILD_KEY_BODY_PART ;
 ctx -> body_parser = fts_parser_text_init ( ) ;
 }
 else {
 if ( ( ctx -> update_ctx -> backend -> flags & FTS_BACKEND_FLAG_BINARY_MIME_PARTS ) == 0 ) return FALSE ;
 * binary_body_r = TRUE ;
 key . type = FTS_BACKEND_BUILD_KEY_BODY_PART_BINARY ;
 }
 key . body_content_type = content_type ;
 key . body_content_disposition = ctx -> content_disposition ;
 ctx -> cur_user_lang = NULL ;
 if ( ! fts_backend_update_set_build_key ( ctx -> update_ctx , & key ) ) {
 if ( ctx -> body_parser != NULL ) ( void ) fts_parser_deinit ( & ctx -> body_parser ) ;
 return FALSE ;
 }
 return TRUE ;
 }